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
#include "sprite_material.hpp"

namespace bmx {

class Renderer {

private: /* ===-=== Private Members ===-=== */
    int m_width;
    int m_height;

    SDL_Window*     m_window = nullptr;
    SDL_Renderer*   m_renderer = nullptr;

public:
    Renderer(const std::string&, int, int);

    ~Renderer();

    bmx::SpriteMaterial* loadSprite(const std::string&);

    void draw(bmx::SpriteMaterial*);

    void clear();

    void begin();

    void commit();
};

} // namespcae bmx

#endif // BMX_UI_MAIN_WINDOW_H