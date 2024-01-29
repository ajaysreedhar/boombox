/**
 * event_manager.hpp - Event manager utility.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_LIB_EVENT_MANAGER_H
#define BMX_LIB_EVENT_MANAGER_H

#include <string>
#include <unordered_map>

namespace bmx {

class EventObserver {

};

class EventManager {

private:
    static std::unordered_map<std::string, bmx::EventObserver> s_observers;

};

}

#endif // BMX_LIB_EVENT_MANAGER_H