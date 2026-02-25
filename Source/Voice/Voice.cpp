/*
  ==============================================================================

    Voice.cpp
    Created: 6 Oct 2025 11:37:50pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Voice.h"

#include <iostream>

Voice::Voice(){
}

void Voice::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    if (isActive())
    {
        // float totalNumSamples = buffer.getNumSamples();
        
        // Each oscillator/generator
        // Starting with a white noise generator
        waveOsc.processBlock(buffer, totalNumOutputChannels);
        whiteNoise.processBlock(buffer, totalNumOutputChannels);
        bitcrusher.processBlock(buffer, totalNumOutputChannels);
    }
}

void Voice::trigger(int p_midiNoteNumber) {
    active = true;
    midiNoteNumber = p_midiNoteNumber;
    // TODO: check, waveOsc should already know its sampleRate?
    waveOsc.sampleRate = sampleRate;
    waveOsc.startNote(getFundamental());
}

void Voice::silence() {
    active = false;
}

void Voice::addNoiseLevelModifier(std::shared_ptr<LowFreqOsc> modifier)
{
    whiteNoise.levelModifiers.push_back(modifier);
}

void Voice::addOscTuneModifier(std::shared_ptr<LowFreqOsc> modifier)
{
    waveOsc.tuneModifiers.push_back(modifier);
}
