/**
 * logger.cpp - Custom logging utility implementation.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#include "logger.hpp"

bool bmx::Logger::s_verbose = true;

void bmx::Logger::verboseOn() {
    s_verbose = true;
}

void bmx::Logger::verboseOff() {
    s_verbose = false;
}
