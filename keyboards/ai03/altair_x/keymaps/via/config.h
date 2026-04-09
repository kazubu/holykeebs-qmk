/* Copyright 2024 ai03 Design Studio */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define SK8707_RESET_PIN GP4

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 7
#define HOLD_ON_OTHER_KEY_PRESS

#ifdef PS2_MOUSE_INVERT_X
#undef PS2_MOUSE_INVERT_X
#endif

#ifdef PS2_MOUSE_INVERT_Y
#undef PS2_MOUSE_INVERT_Y
#endif
