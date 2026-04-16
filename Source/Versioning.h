/*
  ==============================================================================

    Versioning.h
    Created: 29 Nov 2025 2:06:33pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <string>

#include <JuceHeader.h>

using std::to_string;

namespace Versioning {
    // Increment before compilation regardless of added features to ensure correct build is running
    constexpr static int build = 4;

    juce::String version(ProjectInfo::versionString);
    const static juce::String currentVersion = version + "+" + to_string(build);
};
