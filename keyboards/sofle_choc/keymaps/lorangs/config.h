// Copyright 2026 Lorang
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// --- From the stock sofle_choc default keymap ----------------------------
// Half with active USB becomes master. Helps some Pro Micros where the
// slave half doesn't boot.
#define SPLIT_USB_DETECT

#define RGB_MATRIX_SLEEP                  // LEDs off when host suspends
#define SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // (0..255) Should be kept at moderate levels, not to consume too much current over usb-C

// --- Additions -------------------------------------------------------------
// Sync active layer + caps lock to the slave half, so the per-layer key
// highlighting works on both halves.
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

// Tri-layer: TL_LOWR -> layer 1, TL_UPPR -> layer 2, both -> layer 3
#define TRI_LAYER_LOWER_LAYER  1
#define TRI_LAYER_UPPER_LAYER  2
#define TRI_LAYER_ADJUST_LAYER 3

// One wheel "notch" per encoder detent. Raise for faster scrolling.
#define MOUSEKEY_WHEEL_DELTA 1

// --- Flash headroom ----------------------------------------------------------
// The 32U4 only has 28 KB for firmware and the stock build enables 29 RGB
// effects. Dropping a few rarely-used ones leaves room for future changes.
// Remove a line here to bring that effect back (if it still fits).
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
