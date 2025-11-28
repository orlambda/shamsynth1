/*
  ==============================================================================

    Voice.h
    Created: 6 Oct 2025 11:37:50pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "../Noise/NoiseGenerator.h"
#include "../Oscillators/WaveOscillator.h"

#include <JuceHeader.h>

#include <vector>

/*
 Voice could possibly inherit from juce::AudioProcessor
 I am writing my own class for the following reasons:
    - It will likely be simpler so may be quicker to construct/destruct and may use less memory
    - I may change how I process audio as I go
    - Reading the full class implementation takes time and I'd prefer to start working as this is a learning project
    - I do not know if this would be appropriate without further research
 Benefits to inheriting from juce::AudioProcessor could be:
    - Multiple versions of processBlock()
    - Details such as ProcessingPrecision and Realtime already built in
*/

class Voice
{
public:
    // Check state
    bool isActive() {return active;}
    bool getFundamental(){return fundamental;}
    
    // Change state
    bool trigger(float p_fundamental);
    bool silence();
    
    // Check input/output channels, are they combined, etc.
        // Could see if I can change both manually, and print number of channels in buffer, etc.
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    
    // Temporary
    float sampleRate;
    
private:
    // State
    bool active = false;
    float fundamental = 0.0;
    
    // White Noise Generator
    NoiseGenerator whiteNoise;
    
    // osc1
    WaveOscillator sine;
};
