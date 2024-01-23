/**
 * except.cpp - Throwable input exception.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#include "except.hpp"

bmx::InputError::InputError(const char* message, int code): std::runtime_error(message) {
    m_code = code;
}

int bmx::InputError::getCode() {
    return m_code;
}
