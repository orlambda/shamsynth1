/*
  ==============================================================================

    Wavefolder.cpp
    Created: 13 Mar 2026 9:30:19pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Wavefolder.h"

void Wavefolder::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float framesPerBlock = buffer.getNumSamples();
    for (auto frame = 0; frame < framesPerBlock; ++frame)
    {
        for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            float currentValue = (buffer.getSample(channel, frame));
            if (currentValue > threshold)
            {
                float difference = currentValue - threshold;
                buffer.setSample(channel, frame, currentValue - (difference * amount));
            }
            else if (currentValue < -threshold)
            {
                float difference = threshold - currentValue;
                buffer.setSample(channel, frame, currentValue + (difference * amount));
            }
        }
    }
}
