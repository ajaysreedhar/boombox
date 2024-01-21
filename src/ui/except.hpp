/**
 * except.hpp - Throwable user interface exception.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_UI_EXCEPT_H
#define BMX_UI_EXCEPT_H

#include <stdexcept>

namespace bmx {

/**
 * @brief Defines a throwable error for the engine module.
 *
 * All sub-modules in the engine module must throw an
 * instance of this class if an exception occurs.
 */
class UIError: public std::runtime_error  {

private:
    int m_code;

public:
    enum ErrorKind: int {
        E_TYPE_GENERAL = 311,
        E_TYPE_SDL_RESULT,
        E_TYPE_MIX_RESULT
    };

    UIError(const char*, int);

    int getCode();
};

} // namespace bmx

#endif // BMX_UI_EXCEPT_H