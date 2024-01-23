/**
 * except.hpp - Throwable input exception.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_INPUT_EXCEPT_H
#define BMX_INPUT_EXCEPT_H

#include <stdexcept>

namespace bmx {

/**
 * @brief Defines a throwable error for the input module.
 *
 * All sub-modules in the input module must throw an
 * instance of this class if an exception occurs.
 */
class InputError: public std::runtime_error  {

private:
    int m_code;

public:
    enum ErrorKind: int {
        E_TYPE_GENERAL = 411
    };

    InputError(const char*, int);

    int getCode();
};

} // namespace bmx

#endif // BMX_INPUT_EXCEPT_H