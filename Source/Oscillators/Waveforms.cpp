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

void Waveforms::testWavetables()
{
    for (float i = 0.0; i < juce::MathConstants<double>::pi; i = i + (0.01 * juce::MathConstants<double>::pi))
    {
        auto a = Waveforms::sin(i);
        auto b = std::sin(i);
        auto difference = a - b;
        if (difference > 0.001)
        {
            int c = a;
        }
    }
}

void Waveforms::populateWavetables()
{

    // Populate sin table
    sinQuarterTable.setSize(1, sinQuarterTableSize);
    for (int i = 0; i < sinQuarterTableSize; ++i)
    {
        auto value = std::sin(juce::MathConstants<double>::halfPi * ((i * 1.0) / sinQuarterTableSize));
        sinQuarterTable.setSample(0, i, value);
        int a = 0;
    }
    for (int i = 0; i < sinQuarterTableSize; ++i)
    {
        float a = sinQuarterTable.getSample(0, i);
        float b = 0;
    }
}

float Waveforms::sin(float angle)
{
    auto normalisedAngle = fmod(angle, 2.0 * juce::MathConstants<double>::pi);
    auto angleWithinQuarter = fmod(angle, juce::MathConstants<double>::halfPi);
    // TODO: Interpolation
    int sampleIndex = ceil((angleWithinQuarter / juce::MathConstants<double>::halfPi) * sinQuarterTableSize);
    // Temporary range checking (does not correctly deal with wrapping)
    if (sampleIndex < 0)
    {
        // TODO: delete - this is for testing
        // This should never happen (how to handle if it does?)
        sampleIndex = 0;
    }
    if (sampleIndex >= sinQuarterTableSize)
    {
        sampleIndex = sinQuarterTableSize-1;
    }
    auto valueWithinQuarter = sinQuarterTable.getSample(0, sampleIndex);
    if (normalisedAngle >= 1.5 * juce::MathConstants<double>::pi)
    {
        return -1 + valueWithinQuarter;
    }
    else if (normalisedAngle >= juce::MathConstants<double>::pi)
    {
        return -valueWithinQuarter;
    }
    else if (normalisedAngle >= juce::MathConstants<double>::halfPi)
    {
        return 1 - valueWithinQuarter;
    }
    else
    {
        return valueWithinQuarter;
    }
}

float Waveforms::triangle(float angle)
{
    // TODO: avoid using mod both here and in WaveOscillator
    auto normalisedAngle = fmod(angle, 2.0 * juce::MathConstants<double>::pi);
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
    else if (normalisedAngle >= juce::MathConstants<double>::halfPi)
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
