/**
 * display-context.cpp - Global display context.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */
#include <SDL2/SDL.h>
#include "assert.hpp"
#include "logger.hpp"
#include "display_context.hpp"

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
#include "platform/logger.hpp"
#endif

bool bmx::DisplayContext::s_isInitialised = false;

void bmx::DisplayContext::initialise() {
    if (s_isInitialised) {
        return void();
    }

    int result = SDL_Init(SDL_INIT_VIDEO);
    BMX_ASSERT_SDL_RESULT(result);

    s_isInitialised = true;
}


void bmx::DisplayContext::shutdown() {
    if (s_isInitialised == false) {
        bmx::Logger::warn("Attempting to shutdown display context without initialising.");
        return void();
    }

    SDL_VideoQuit();
    SDL_Quit();
}

bool bmx::DisplayContext::isInitialised() {
    return s_isInitialised;
}

bmx::DisplayContext::UIEvent bmx::DisplayContext::pollEvent() {
    SDL_Event sdl_event {};
    bmx::DisplayContext::UIEvent bmx_event {bmx::DisplayContext::UIEvent::UNKNOWN};

    SDL_PollEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) {
        bmx_event.kind = bmx::DisplayContext::UIEvent::PROCESS_QUIT;
        return bmx_event;
    }

    if (sdl_event.type == SDL_KEYDOWN) {
        switch(sdl_event.key.keysym.scancode) {
            case SDL_SCANCODE_Q:
                bmx_event.kind = bmx::DisplayContext::UIEvent::KEY_PRESS_Q;
                break;

            default:
                break;;
        }
    }

    return bmx_event;
}
