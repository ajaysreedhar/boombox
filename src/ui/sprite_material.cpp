/**
 * sprite_material.cpp - Sprites for the Boombox.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#include <SDL2/SDL_image.h>
#include "assert.hpp"
#include "sprite_material.hpp"

#if defined(BMX_MODE_DEBUG) && BMX_MODE_DEBUG == 1
#include "platform/logger.hpp"
#endif // BMX_MODE_DEBUG

unsigned int bmx::SpriteMaterial::s_counter = 0;

bmx::SpriteMaterial::SpriteMaterial(SDL_Renderer* renderer, SDL_Surface* surface) {
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    BMX_ASSERT_SDL_HANDLE(m_texture, bmx::UIError::E_TYPE_SDL_RESULT);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &(m_scissor.w), &(m_scissor.h));

    m_attachment.w = m_scissor.w;
    m_attachment.h = m_scissor.h;

    s_counter = s_counter + 1;
}

bmx::SpriteMaterial::SpriteMaterial(SDL_Texture* texture, const SDL_Rect& properties, const SDL_Rect& attachment) {
    m_texture = texture;
    m_scissor.w = properties.w;
    m_scissor.h = properties.h;
    m_scissor.x = properties.x;
    m_scissor.y = properties.y;
    m_attachment.w = attachment.w;
    m_attachment.h = attachment.h;
    m_attachment.x = attachment.x;
    m_attachment.y = attachment.y;

    m_isCloned = true;
}

bmx::SpriteMaterial* bmx::SpriteMaterial::factory(SDL_Renderer* renderer, const std::string& file_path) {
    SDL_Surface* surface = IMG_Load(file_path.c_str());
    BMX_ASSERT_SDL_HANDLE(surface, bmx::UIError::E_TYPE_SDL_RESULT);

    auto material = new bmx::SpriteMaterial(renderer, surface);
    
    SDL_FreeSurface(surface);
    return material;
}

bmx::SpriteMaterial::~SpriteMaterial() {
    if (!m_isCloned && m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        s_counter = s_counter - 1;

#if defined(BMX_MODE_DEBUG) && BMX_MODE_DEBUG == 1
    bmx::Logger::debug("Sprite material destroyed.", s_counter, "remaining.");
#endif // BMX_MODE_DEBUG
    }
}

bmx::SpriteMaterial* bmx::SpriteMaterial::clone() {
    return new bmx::SpriteMaterial(m_texture, m_scissor, m_attachment);
}

void bmx::SpriteMaterial::setAttachment(int pos_x, int pos_y, int width, int height) {
    m_attachment.x = pos_x;
    m_attachment.y = pos_y;
    m_attachment.w = width;
    m_attachment.h = height;
}

void bmx::SpriteMaterial::setAttachment(int pos_x, int pos_y) {
    m_attachment.x = pos_x;
    m_attachment.y = pos_y;
}

void bmx::SpriteMaterial::setScissor(int pos_x, int pos_y, int width, int height) {
    m_scissor.x = pos_x;
    m_scissor.y = pos_y;
    m_scissor.w = width;
    m_scissor.h = height;
}

void bmx::SpriteMaterial::setScissor(int pos_x, int pox_y) {
    m_scissor.x = pos_x;
    m_scissor.y = pox_y;
}

SDL_Texture* bmx::SpriteMaterial::getTexture() const {
    return m_texture;
}

const SDL_Rect* bmx::SpriteMaterial::getProperties() const {
    return &m_scissor;
}

const SDL_Rect* bmx::SpriteMaterial::getAttachment() const {
    return &m_attachment;
}

int bmx::SpriteMaterial::getWidth() const {
    return m_scissor.w;
}

int bmx::SpriteMaterial::getHeight() const {
    return m_scissor.h;
}

int bmx::SpriteMaterial::getPositionX() const {
    return m_attachment.x;
}

int bmx::SpriteMaterial::getPositionY() const {
    return m_attachment.y;
}

int bmx::SpriteMaterial::getScissorX() const {
    return m_scissor.x;
}

int bmx::SpriteMaterial::getScissorY() const {
    return m_scissor.y;
}
