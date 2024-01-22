/**
 * renderer.hpp - Primary graphics renderer.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_UI_MAIN_WINDOW_H
#define BMX_UI_MAIN_WINDOW_H

#include <string>
#include <SDL2/SDL.h>

namespace bmx {

class Renderer {

private: /* ===-=== Private Members ===-=== */
    int m_width;
    int m_height;

    SDL_Window* m_window = nullptr;

public:
    Renderer(const std::string& title, int width, int height);

    ~Renderer();
};

} // namespcae bmx

#endif // BMX_UI_MAIN_WINDOW_H