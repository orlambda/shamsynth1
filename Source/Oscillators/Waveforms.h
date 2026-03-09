/*
  ==============================================================================

    Waveforms.h
    Created: 26 Feb 2026 11:04:59pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

static juce::AudioSampleBuffer sinQuarterTable;

namespace Waveforms
{
    void populateWavetables();
    float sin(float angle);
    float triangle(float angle);
    float square(float angle);
    constexpr static int sinQuarterTableSize = 2048;

    void testWavetables();
    void testTriangleWave();
}
