/*
  ==============================================================================

    Waveforms.cpp
    Created: 26 Feb 2026 11:04:59pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Waveforms.h"

// All Waveform functions interpret an angle in turns and return values of range [1, -1]

// The last value in sinQuarterTable overlaps with the first (calculated) value of the next quarter
// Values in table should be in range [0,1], covering angles [0.0,0.25] to allow rounding/interpolation to angle 0.25 tr (pi*0.5 rad)
void Waveforms::populateWavetables()
{
    // Populate sin table
    sinQuarterTable.setSize(1, sinQuarterTableSize);
    for (int i = 0; i < sinQuarterTableSize; ++i)
    {
        auto angle = juce::MathConstants<double>::halfPi * (float(i) / (sinQuarterTableSize - 1));
        auto value = std::sin(angle);
        sinQuarterTable.setSample(0, i, value);
    }
}

float Waveforms::sin(float angle)
{
    angle = fmod(angle, 1.0f);
    auto angleWithinQuarter = fmod(angle, 0.25f);
    
    // TODO: Interpolation
    
    int sampleIndex = std::round((angleWithinQuarter / 0.25f) * (sinQuarterTableSize - 1));
    
    // for 2nd and 4th quarters
    if ((angle >= 0.25f && angle < 0.5f) || angle >= 0.75f)
    {
        sampleIndex = sinQuarterTableSize - (sampleIndex + 1);
    }
    
    auto valueWithinQuarter = sinQuarterTable.getSample(0, sampleIndex);
    
    if (angle >= 0.5f)
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
    auto normalisedAngle = fmod(angle, 1.0f);
    auto angleWithinQuarter = fmod(angle, 0.25f);
    // Triangle wave is symmetrical - calculate value within quarter
    // Angle within quarter is in range [0.0f, 0.25f)
    // Value within quarter is in range [0.0f, 1.0f)
    auto valueWithinQuarter = angleWithinQuarter / 0.25f;
    if (normalisedAngle >= 0.75f)
    {
        return -1.0f + valueWithinQuarter;
    }
    else if (normalisedAngle >= 0.5f)
    {
        return -valueWithinQuarter;
    }
    else if (normalisedAngle >= 0.25f)
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
    auto normalisedAngle = fmod(angle, 1.0f);
    // [0, 0.5f) = 1.0f, [0.5f, 1.0f) = -1.0f
    if (normalisedAngle >= 0.5f)
    {
        return -1.0f;
    }
    else
    {
        return 1.0f;
    }
}


// TODO: move to unit test
void Waveforms::testWavetables()
{
    for (float i = 0.0f; i <= 1.0f; i = i + 0.01f)
    {
        auto sin1 = Waveforms::sin(i);
        auto sin2 = std::sin(i * juce::MathConstants<double>::twoPi);
        auto difference = abs(sin1 - sin2);
        if (difference > 0.001f)
        {
            int c = sin1;
        }
    }
    testTriangleWave();
}

// TODO: move to unit test
void Waveforms::testTriangleWave()
{
    for (float i = 0.0f; i <= 1.0f; i = i + 0.01f)
    {
        float a = Waveforms::triangle(i);
    }
}
