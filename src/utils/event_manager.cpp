/**
 * event_manager.cpp - Event manager utility.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#include "event_manager.hpp"

template<typename T> bmx::EventPayload<T>::EventPayload(T payload): m_payload{payload} {}

template<typename T> T bmx::EventPayload<T>::getPayload() {
    return m_payload;
}
