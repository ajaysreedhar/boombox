/**
 * display-context.hpp - Global display context.
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

namespace bmx {

/**
 * @brief Defines an event polled from the display context.
 */
struct display_event {
    int kind = 404;

    enum EventKind: int {
        UNKNOWN = 404,
        PROCESS_QUIT = 500,
        WINDOW_CLOSE
    };
};

}

#endif // BMX_UI_DISPLAY_CONTEXT_H