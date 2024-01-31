/**
 * renderer.cpp - Primary graphics renderer.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */
#include "platform/logger.hpp"
#include "assert.hpp"
#include "renderer.hpp"

bmx::Renderer::Renderer(const std::string& title, int width, int height) {
    m_width = width;
    m_height = height;

    m_window = SDL_CreateWindow(title.c_str(), 0, 0, m_width, m_height, SDL_WINDOW_OPENGL);
    BMX_ASSERT_SDL_HANDLE(m_window, bmx::UIError::E_TYPE_SDL_RESULT);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    BMX_ASSERT_SDL_HANDLE(m_window, bmx::UIError::E_TYPE_SDL_RESULT);
}

bmx::Renderer::~Renderer() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

#if defined(BMX_MODE_DEBUG) && BMX_MODE_DEBUG == 1
    bmx::Logger::debug("Renderer instance destroyed!");
#endif // BMX_MODE_DEBUG
}

bmx::SpriteMaterial* bmx::Renderer::loadSprite(const std::string& image_file) {
    return bmx::SpriteMaterial::factory(m_renderer, image_file);
}

void bmx::Renderer::draw(bmx::SpriteMaterial* material) {
    const SDL_Rect* srcrect = material->getScissor();
    const SDL_Rect* dstrect = material->getAttachment();

    int result = SDL_RenderCopy(m_renderer, material->getTexture(), srcrect, dstrect);
    BMX_ASSERT_SDL_RESULT(result)
}

void bmx::Renderer::clear() {
    SDL_SetRenderDrawColor(m_renderer, 0x5E, 0x82, 0xAC, 0xff);
    int result = SDL_RenderClear(m_renderer);
    BMX_ASSERT_SDL_RESULT(result)
}

void bmx::Renderer::begin() {
    this->clear();
}

void bmx::Renderer::commit() {
    SDL_RenderPresent(m_renderer);
}
