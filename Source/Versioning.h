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
    // Increment on every major new feature
    constexpr static int minor = 0;
    // Increment on every commit that adds a feature or fixes a bug
    constexpr static int patch = 7;
    // Increment before compilation regardless of added features to ensure correct build is running
    constexpr static int build = 5;

    const static std::string currentVersion = to_string(major) + "." + to_string(minor) + "." + to_string(patch) + "+" + to_string(build);
};
