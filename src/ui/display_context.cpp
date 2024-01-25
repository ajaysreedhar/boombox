/**
 * display_context.cpp - Global display context.
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
#include "platform/logger.hpp"
#include "except.hpp"
#include "assert.hpp"
#include "display_context.hpp"

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
#include "platform/logger.hpp"
#endif

bool bmx::DisplayContext::s_isInitialised = false;
std::vector<bmx::Renderer*> bmx::DisplayContext::s_renderers {};

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

    for (auto renderer : s_renderers) {
        delete renderer;
    }

    s_renderers.clear();

    SDL_VideoQuit();
    SDL_Quit();
}

bool bmx::DisplayContext::isInitialised() {
    return s_isInitialised;
}

bmx::Renderer* bmx::DisplayContext::createRenderer() {
    if (s_isInitialised == false) {
        throw bmx::UIError("Attempt to create a renderer without initialising the context.", bmx::UIError::E_TYPE_GENERAL);
    }

    auto renderer = new bmx::Renderer("Boombox", 950, 550);
    s_renderers.push_back(renderer);

    return renderer;
}

bmx::DisplayContext::UIEvent bmx::DisplayContext::pollEvent() {
    SDL_Event sdl_event {};
    bmx::DisplayContext::UIEvent bmx_event {bmx::DisplayContext::UIEvent::UNKNOWN};

    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) {
        bmx_event.kind = bmx::DisplayContext::UIEvent::PROCESS_QUIT;
        return bmx_event;
    }

    if (sdl_event.type == SDL_KEYDOWN) {
        switch(sdl_event.key.keysym.scancode) {
            case SDL_SCANCODE_Q:
                bmx_event.kind = bmx::DisplayContext::UIEvent::KEY_PRESS_Q;
                break;

            case SDL_SCANCODE_W:
                bmx_event.kind = bmx::DisplayContext::UIEvent::KEY_PRESS_W;
                break;

            case SDL_SCANCODE_S:
                bmx_event.kind = bmx::DisplayContext::UIEvent::KEY_PRESS_S;
                break;

            default:
                break;;
        }
    }

    return bmx_event;
}
