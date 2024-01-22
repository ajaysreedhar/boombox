/**
 * sprite_material.hpp - Sprites for the Boombox.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_UI_SPRITE_MATERIAL_H
#define BMX_UI_SPRITE_MATERIAL_H

#include <string>
#include <SDL2/SDL.h>

namespace bmx {

class SpriteMaterial {

private: /* ===-=== Private members ===-=== */
    static unsigned int s_counter;

    bool m_isCloned = false;

    SDL_Texture* m_texture = nullptr;

    SDL_Rect m_scissor {0, 0, 0, 0};

    SDL_Rect m_attachment {0, 0, 0, 0};

    explicit SpriteMaterial(SDL_Renderer*, SDL_Surface*);

    explicit SpriteMaterial(SDL_Texture*, const SDL_Rect&, const SDL_Rect&);

public: /* ===-=== Public members ===-=== */
    static SpriteMaterial* factory(SDL_Renderer*, const std::string&);

    ~SpriteMaterial();

    SpriteMaterial* clone();

    void setAttachment(int, int, int, int);

    void setAttachment(int, int);

    void setScissor(int, int, int, int);

    void setScissor(int, int);

    [[nodiscard]] SDL_Texture* getTexture() const;

    [[nodiscard]] const SDL_Rect* getProperties() const;

    [[nodiscard]] const SDL_Rect* getAttachment() const;

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getPositionX() const;

    [[nodiscard]] int getPositionY() const;

    [[nodiscard]] int getScissorX() const;

    [[nodiscard]] int getScissorY() const;
};

} // namespace bmx

#endif // BMX_UI_SPRITE_MATERIAL_H