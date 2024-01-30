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

template<typename T>
class EventPayload {

private:
    T m_payload;

public: 
    EventPayload(T payload);
    T getPayload();
};

template<typename T>
class EventObserver {

private:
    bmx::EventPayload<T>* m_payload;
    void(*)(T) m_callback;

public:
    explicit EventObserver(void(*)(T), bmx::EventPayload<T>);
};

template <template<auto> typename T>
class EventManager {

private:
    static std::unordered_map<std::string, bmx::EventObserver<T>> s_observers;
    static void dispatch(bmx::EventObserver<T>*);

public:
    template<typename T> static void observe(std::string&, EventObserver<T>*);
    static void notify(std::string&);
};

}

#endif // BMX_LIB_EVENT_MANAGER_H