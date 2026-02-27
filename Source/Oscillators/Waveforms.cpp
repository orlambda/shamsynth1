/*
  ==============================================================================

    Waveforms.cpp
    Created: 26 Feb 2026 11:04:59pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Waveforms.h"

// May not need this when using lookup table
#include <cmath>

// All Waveform functions interpret an angle in radians and return values of range [1, -1]

float Waveforms::sin(float angle)
{
    // TODO: use lookup table
    return std::sin(angle);
}
float Waveforms::triangle(float angle)
{
    // TODO: avoid using mod both here and in WaveOscillator
    // TODO: use lookup table?
    auto normalisedAngle = fmod(angle, 2.0 * juce::MathConstants<double>::pi);
    auto halfPi = 0.5 * juce::MathConstants<double>::pi;
    auto angleWithinQuarter = fmod(angle, juce::MathConstants<double>::halfPi);
    // Triangle wave is symmetrical - calculate value within quarter
    // Angle within quarter is in range [0, 0.5 * pi)
    // Value within quarter is in range [0, 1)
    auto valueWithinQuarter = angleWithinQuarter / juce::MathConstants<double>::halfPi;
    if (normalisedAngle >= 1.5 * juce::MathConstants<double>::pi)
    {
        return -1 + valueWithinQuarter;
    }
    else if (normalisedAngle >= juce::MathConstants<double>::pi)
    {
        return -valueWithinQuarter;
    }
    else if (normalisedAngle >= halfPi)
    {
        return 1 - valueWithinQuarter;
    }
    else
    {
        return valueWithinQuarter;
    }
}

float Waveforms::square(float angle)
{
    // TODO: avoid using mod both here and in WaveOscillator?
    // TODO: use lookup table?
    auto normalisedAngle = fmod(angle, 2.0 * juce::MathConstants<double>::pi);
    // [0, pi) = 1, [pi, 2*pi) = -1
    if (normalisedAngle >= juce::MathConstants<double>::pi)
    {
        return 1.0;
    }
    else
    {
        return -1.0;
    }
}
