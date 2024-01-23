/**
 * display_context.hpp - Global display context.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_UI_DISPLAY_CONTEXT_H
#define BMX_UI_DISPLAY_CONTEXT_H

#include <vector>
#include "renderer.hpp"

namespace bmx {

/**
 * @brief Defines an event polled from the display context.
 */
struct ui_event {
    int kind = 404;

    enum EventKind: int {
        UNKNOWN = 404,
        PROCESS_QUIT = 500,
        WINDOW_CLOSE,
        KEY_PRESS_Q,
        KEY_PRESS_S,
        KEY_PRESS_W
    };
};

class DisplayContext {

private: /* ===-=== Private Members ===-=== */
    static bool s_isInitialised;

    static std::vector<bmx::Renderer*> s_renderers;

public:
    typedef struct ui_event UIEvent;

    static void initialise();

    static void shutdown();

    static bool isInitialised();

    static Renderer* createRenderer();

    static DisplayContext::UIEvent pollEvent();
};

} // namespace bmx

#endif // BMX_UI_DISPLAY_CONTEXT_H