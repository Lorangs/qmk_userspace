#!/usr/bin/env python3
"""Convert an image to a QMK OLED raw bitmap (128x32, SSD1306 page format).

Output is a C array for oled_write_raw_P(): 4 pages x 128 columns, one byte
per 8 vertical pixels, least significant bit at the top. 512 bytes of flash.

Examples:
  png2oled.py logo.png > logo.h
  png2oled.py photo.jpg --fit --dither --name cat > cat.h
  png2oled.py art.png --invert --preview check.png   # dark art on white bg
  png2oled.py tall.png --rotate 90                   # 32x128 portrait art
  png2oled.py drawing.pixil --alpha --rotate 90      # Pixilart file, drawn pixels lit

Portrait art for the Sofle Choc's right half: --rotate 90 matches QMK's
OLED_ROTATION_90 (use 270 if it shows upside down on your build).

Inputs: anything Pillow opens (PNG, BMP, JPG, GIF, ...) and Pixilart .pixil
files (first frame, all layers; --frame N picks another frame).

Requires Pillow (pip install pillow / apt install python3-pil).
"""
import argparse
import base64
import io
import json
import sys

from PIL import Image

W, H = 128, 32


def open_pixil(path, frame):
    """Pixilart .pixil = JSON; each layer is a data:...base64,<PNG> string."""
    with open(path) as f:
        doc = json.load(f)
    frames = doc["frames"]
    if not 0 <= frame < len(frames):
        sys.exit(f"{path} has {len(frames)} frame(s); --frame must be 0-{len(frames) - 1}")
    out = Image.new("RGBA", (doc["width"], doc["height"]), (0, 0, 0, 0))
    for layer in frames[frame]["layers"]:
        png = base64.b64decode(layer["src"].split(",", 1)[1])
        im = Image.open(io.BytesIO(png)).convert("RGBA")
        opacity = float(layer.get("opacity", 1))
        if opacity < 1:
            im.putalpha(im.getchannel("A").point(lambda a: int(a * opacity)))
        out = Image.alpha_composite(out, im)
    return out


def to_bitmap(img, threshold, dither, invert):
    img = img.convert("L")
    if invert:
        img = img.point(lambda p: 255 - p)
    if dither:
        return img.convert("1")                       # Floyd-Steinberg
    return img.point(lambda p: 255 if p >= threshold else 0, mode="1")


def pack_pages(bw):
    px = bw.load()
    out = bytearray()
    for page in range(H // 8):
        for x in range(W):
            b = 0
            for bit in range(8):
                if px[x, page * 8 + bit]:
                    b |= 1 << bit
            out.append(b)
    return out


def unpack_pages(data):
    img = Image.new("1", (W, H))
    px = img.load()
    for i, b in enumerate(data):
        page, x = divmod(i, W)
        for bit in range(8):
            px[x, page * 8 + bit] = 255 if b >> bit & 1 else 0
    return img


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("image")
    ap.add_argument("--name", default="oled_image", help="C array name (default: oled_image)")
    ap.add_argument("--fit", action="store_true", help="scale to fit 128x32, keeping aspect ratio")
    ap.add_argument("--rotate", type=int, choices=(0, 90, 180, 270), default=0,
                    help="rotate counter-clockwise first (90/270 for 32x128 portrait art)")
    ap.add_argument("--threshold", type=int, default=128, help="0-255, pixels >= this are lit")
    ap.add_argument("--dither", action="store_true", help="dither instead of threshold (photos)")
    ap.add_argument("--invert", action="store_true", help="light <-> dark (for dark art on white)")
    ap.add_argument("--alpha", action="store_true",
                    help="light every non-transparent pixel, whatever its colour (drawings on transparent bg)")
    ap.add_argument("--frame", type=int, default=0, help=".pixil only: frame number (default 0)")
    ap.add_argument("--preview", metavar="PNG", help="also write a 4x-scaled preview of the result")
    a = ap.parse_args()

    img = open_pixil(a.image, a.frame) if a.image.lower().endswith(".pixil") else Image.open(a.image)
    if a.alpha:                                        # drawn = lit, transparent = unlit
        img = img.convert("RGBA").getchannel("A").point(lambda v: 255 if v >= 128 else 0)
    elif img.mode in ("RGBA", "LA", "P"):              # transparent areas -> black (unlit)
        img = img.convert("RGBA")
        bg = Image.new("RGBA", img.size, (0, 0, 0, 255))
        img = Image.alpha_composite(bg, img)
    if a.rotate:
        img = img.rotate(a.rotate, expand=True)
    if a.fit:
        canvas = Image.new("RGB", (W, H))
        img = img.convert("RGB")
        img.thumbnail((W, H), Image.LANCZOS)
        canvas.paste(img, ((W - img.width) // 2, (H - img.height) // 2))
        img = canvas
    if img.size != (W, H):
        sys.exit(f"Image is {img.width}x{img.height}, need {W}x{H}. Use --fit (or --rotate for portrait).")

    data = pack_pages(to_bitmap(img, a.threshold, a.dither, a.invert))

    if a.preview:
        unpack_pages(data).resize((W * 4, H * 4), Image.NEAREST).save(a.preview)

    lit = sum(bin(b).count("1") for b in data)
    print(f"// {a.image}: {W}x{H}, {lit} of {W * H} pixels lit, {len(data)} bytes")
    print(f"static const char PROGMEM {a.name}[{len(data)}] = {{")
    for i in range(0, len(data), 16):
        print("    " + ", ".join(f"0x{b:02X}" for b in data[i:i + 16]) + ",")
    print("};")


if __name__ == "__main__":
    main()