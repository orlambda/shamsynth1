/*
  ==============================================================================

    Waveforms.cpp
    Created: 26 Feb 2026 11:04:59pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Waveforms.h"

// All Waveform functions interpret an angle in radians and return values of range [1, -1]

void Waveforms::testWavetables()
{
    for (float i = 0.0f; i < juce::MathConstants<double>::pi; i = i + (0.01f * juce::MathConstants<double>::pi))
    {
        auto a = Waveforms::sin(i);
        auto b = std::sin(i);
        auto difference = a - b;
        if (difference > 0.001f)
        {
            int c = a;
        }
    }
}

void Waveforms::testTriangleWave()
{
    for (float i = 0.0f; i <= 2.0f * juce::MathConstants<double>::pi; i = i+(0.1f * juce::MathConstants<double>::halfPi))
    {
        float a = Waveforms::triangle(i);
        float b = a;
    }
}

void Waveforms::populateWavetables()
{
    // Populate sin table
    sinQuarterTable.setSize(1, sinQuarterTableSize);
    for (int i = 0; i < sinQuarterTableSize; ++i)
    {
        auto value = std::sin(juce::MathConstants<double>::halfPi * ((i * 1.0f) / sinQuarterTableSize));
        sinQuarterTable.setSample(0, i, value);
    }
}

float Waveforms::sin(float angle)
{
    auto angleWithinQuarter = fmod(angle, juce::MathConstants<double>::halfPi);
    angle = fmod(angle, 2.0f * juce::MathConstants<double>::pi);
    
    // TODO: Interpolation
    int sampleIndex = std::round((angleWithinQuarter / juce::MathConstants<double>::halfPi) * sinQuarterTableSize);
    // for 2nd and 4th quarter
    if ((angle >= juce::MathConstants<double>::halfPi && angle < juce::MathConstants<double>::pi) || angle >= 1.5f * juce::MathConstants<double>::pi)
    {
        sampleIndex = sinQuarterTableSize - (sampleIndex + 1);
    }
    // Temporary range checking (does not correctly deal with wrapping)
    if (sampleIndex < 0 || sampleIndex >= sinQuarterTableSize)
    {
        // TODO: delete - this is for testing
        // This should never happen (how to handle if it does?)
        sampleIndex = 0;
    }
    auto valueWithinQuarter = sinQuarterTable.getSample(0, sampleIndex);
    if (angle >= juce::MathConstants<double>::pi)
    {
        return -valueWithinQuarter;
    }
    else
    {
        return valueWithinQuarter;
    }
}

float Waveforms::triangle(float angle)
{
    // TODO: avoid using mod both here and in WaveOscillator
    auto normalisedAngle = fmod(angle, 2.0f * juce::MathConstants<double>::pi);
    auto angleWithinQuarter = fmod(angle, juce::MathConstants<double>::halfPi);
    // Triangle wave is symmetrical - calculate value within quarter
    // Angle within quarter is in range [0, 0.5 * pi)
    // Value within quarter is in range [0, 1)
    auto valueWithinQuarter = angleWithinQuarter / juce::MathConstants<double>::halfPi;
    if (normalisedAngle >= 1.5f * juce::MathConstants<double>::pi)
    {
        return -1.0f + valueWithinQuarter;
    }
    else if (normalisedAngle >= juce::MathConstants<double>::pi)
    {
        return -valueWithinQuarter;
    }
    else if (normalisedAngle >= juce::MathConstants<double>::halfPi)
    {
        return 1.0f - valueWithinQuarter;
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
    auto normalisedAngle = fmod(angle, 2.0f * juce::MathConstants<double>::pi);
    // [0, pi) = 1, [pi, 2*pi) = -1
    if (normalisedAngle >= juce::MathConstants<double>::pi)
    {
        return 1.0f;
    }
    else
    {
        return -1.0f;
    }
}
