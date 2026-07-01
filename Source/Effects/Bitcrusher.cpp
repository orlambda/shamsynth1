/*
  ==============================================================================

    Bitcrusher.cpp
    Created: 15 Dec 2025 3:15:46pm
    Author:  Orlando Shamlou

  ==============================================================================
*/


/*
 Tested Logic Pro Bitcrusher, using s(M)exoscope to look at waveform
 Bitcrusher settings:
    Mode: Fold
    Drive: 0.0 dB
    Downsampling: 1x
    Mix: 100%
    Clip Level: 0.0 dB
 
 Always allows output sample value of 0.0 and both negative and positive values
 1 bit = 3 available values
 2 bit = 5 available values, etc.
 
 Often results in silence if signal is too low.
 If signal is very high, bitcrusher acts as a limiter. Values do not go out of range (presumably [-1,1])
 */

/*
 This bitcrusher currently works the same as logic pro outlined above, but without limiting values
 
 TODO: design decision - limit output values to [-1,1]?
 
 Currently input values are not bounded with range [-1,1] as sin/tri/square waves are added together
 This will change with waveshaping, but unsure yet if modulation will affect this (undecided if modulatable values will be bounded)
 If I want to bound the Voice or Oscillator's output to [-1,1], I may do that elsewhere
*/

#include "Bitcrusher.h"

void Bitcrusher::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    int totalNumSamples = buffer.getNumSamples();
    for (auto sample = 0; sample < totalNumSamples; ++sample)
    {
        auto currentBitDepth = bitDepth->getModulatedValue(sample);
        
        // Actual number of available values is 1 higher than this, e.g. 2^1 == 2, but gives us 3 values. This allows silence to remain silent, and is consistent with Logic Pro bitcrusher (see above)
        // Could rename to sampleDepth or resolution?
        auto availableValues = powf(2.0f, currentBitDepth);
        
        for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            // TODO: refactor into this function for unit testing
            // float finalValue = bitcrush(currentValue, currentBitDepth);
            // float bitcrush(float sampleValue, float bitDepth);
            
            float currentValue = (buffer.getSample(channel, sample));
            
            // Change range from [-1,1] to [0,1]
            currentValue = (currentValue + 1.0f) * 0.5f;
            
            // Prevent overflow - unnecessary if effect is not applied above a certain resolution
            long long int currentValueRounded = round(currentValue * availableValues);
            currentValue = currentValueRounded / availableValues;
            
            // Change range from [0,1] to [-1,1]
            currentValue = (currentValue * 2.0f) - 1.0f;
            
            buffer.setSample(channel, sample, currentValue);
        }
    }
}

void Bitcrusher::clearModulationSignalBlocks()
{
    bitDepth->clearAllModulation();
}
