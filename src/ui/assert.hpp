/**
 * assert.hpp - Various macros for assertion.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_UI_ASSERT_H
#define BMX_UI_ASSERT_H

#include <SDL2/SDL_error.h>
#include "except.hpp"

#define BMX_ASSERT_SDL_HANDLE(handle, code) \
if (handle == nullptr) {                    \
    const char* message = SDL_GetError();   \
    throw bmx::UIError(message, code);      \
}


#define BMX_ASSERT_SDL_RESULT(result)       \
if (result <= -1) {                         \
    const char* message = SDL_GetError();   \
    throw bmx::UIError(message, result);    \
}

#endif // BMX_UI_ASSERT_H