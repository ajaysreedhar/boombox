/**
 * filesystem.hpp - Filesystem utilities.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#ifndef BMX_PLATFORM_FILESYSTEM_H
#define BMX_PLATFORM_FILESYSTEM_H

#include <string>

namespace bmx {

class Filesystem {

private:
    static std::string s_dirname;

public:

    static std::string dirname();

    static std::string resource(const std::string&, const std::string&);
};

} // namespace bmx

#endif // BMX_PLATFORM_FILESYSTEM_H