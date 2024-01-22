/**
 * filesystem.cpp - Filesystem utilities.
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2024-present Ajay Sreedhar
 * 
 * Licensed under the MIT License.
 * Please see the LICENSE file located in the root directory.
 *
 * ========================================================================
 */

#include <filesystem>
#include "filesystem.hpp"

std::string bmx::Filesystem::s_dirname {};

std::string bmx::Filesystem::dirname() {
    if (s_dirname.length() >= 2) {
        return s_dirname;
    }

    auto path = std::filesystem::canonical("/proc/self/exe");
    s_dirname = path.remove_filename().string();

    return s_dirname;
}

std::string bmx::Filesystem::resource(const std::string& directory, const std::string& file) {
    auto root_dir = dirname();
    return root_dir.append(directory).append("/").append(file);
}
