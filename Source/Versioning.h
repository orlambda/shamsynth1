/*
  ==============================================================================

    Versioning.h
    Created: 29 Nov 2025 2:06:33pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <string>

using std::to_string;

namespace Versioning {
    constexpr static int major = 1;
    constexpr static int minor = 0;
    // Increment on every commit
    constexpr static int patch = 1;
    // Increment before compilation regardless of added features to ensure correct build is running
    constexpr static int build = 3;

    static std::string currentVersion = to_string(major) + "." + to_string(minor) + "." + to_string(patch) + "+" + to_string(build);

//    std::string currentVersion() {
//        return to_string(major) + "." + to_string(minor) + "." + to_string(patch) + "+" + to_string(build);
//    }
};
