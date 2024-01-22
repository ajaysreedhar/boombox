/**
 * logger.hpp - Custom logging utility declarations.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_PLATFORM_LOGGER_H
#define BMX_PLATFORM_LOGGER_H

#include <iostream>
#include <string>
#include <initializer_list>

namespace bmx {

class Logger {

private:/* ===-=== Private Members ===-=== */
    static bool s_verbose;

    template<typename T>
    static void printUnpacked_(int level, T&& message) {
        switch (level) {
            case FATAL:
            case ERROR:
            case WARN:
                std::cerr << message << " ";
                break;

            default:
                std::cout << message << " ";
                break;
        }
    }

    public: /* ===-=== Public Members ===-=== */
    enum LogLevel : int {
        FATAL = 0,
        ERROR,
        WARN,
        INFO,
        DEBUG,
        TRACE
    };

    static void verboseOn();

    static void verboseOff();

    template<typename... T> static void fatal(T&& ...messages) {
        std::cerr << "[FATAL] ";
        (printUnpacked_(FATAL, messages), ...);
        std::cerr << std::endl;
    }

    template<typename... T> static void error(T&& ...messages) {
        std::cerr << "[ERROR] ";
        (printUnpacked_(ERROR, messages), ...);
        std::cerr << std::endl;
    }

    template<typename... T> static void warn(T&& ...messages) {
        std::cerr << "[WARN ] ";
        (printUnpacked_(WARN, messages), ...);
        std::cerr << std::endl;
    }

    template<typename... T> static void info(T&& ...messages) {
        std::cout << "[INFO ] ";
        (printUnpacked_(INFO, messages), ...);
        std::cout << std::endl;
    }

    template<typename... T> static void debug(T&& ...messages) {
        std::cout << "[DEBUG] ";
        (printUnpacked_(DEBUG, messages), ...);
        std::cout << std::endl;
    }

    template<typename... T> static void trace(T&& ...messages) {
        std::cout << "[TRACE] ";
        (printUnpacked_(TRACE, messages), ...);
        std::cout << std::endl;
    }

    template<typename... T> static void print(T&& ...messages) {
        (printUnpacked_(INFO, messages), ...);
        std::cout << std::endl;
    }
};

} // namespace bmx

#endif // BMX_PLATFORM_LOGGER_H