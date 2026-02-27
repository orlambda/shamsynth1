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
#include "../Oscillators/LowFreqOsc.h"
#include "../Effects/Bitcrusher.h"

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
    Voice();
    
    // Check state
    bool isActive() {return active;}
    int getMidiNoteNumber(){return midiNoteNumber;}
    float getFundamental(){return juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);}
    
    // Change state
    void trigger(int p_midiNoteNumber);
    void silence();
    
    // Check input/output channels, are they combined, etc.
        // Could see if I can change both manually, and print number of channels in buffer, etc.
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    
    // Temporary
    // TODO: make static - sampleRate the same for every Voice
    float sampleRate;
    void updateOsc1Level(float level) {waveOsc.updateLevel(level);}
    void updateOsc1SineLevel(float level) {waveOsc.updateSineLevel(level);}
    void updateOsc1TriangleLevel(float level) {waveOsc.updateTriangleLevel(level);}
    void updateOsc1SquareLevel(float level) {waveOsc.updateSquareLevel(level);}
    void updateOsc1Tune(float tune) {waveOsc.updateTune(tune);}
    void updateNoiseLevel(float level) {whiteNoise.currentLevel = level;}
    void updateBitcrusherBitDepth(float depth) {bitcrusher.bitDepth = depth;}
    
    // However a modulation matrix will probably change implementation, wait till then before refactoring
    // Rename modifiers: modulation, lfos, signals..
    void addNoiseLevelModifier(std::shared_ptr<LowFreqOsc> modifier);
    void addOscTuneModifier(std::shared_ptr<LowFreqOsc> modifier);
    
private:
    // State
    bool active = false;
    // TODO: how to initialise?
    int midiNoteNumber = 0;
    // float fundamental = 0.0;
    
    // White Noise Generator
    NoiseGenerator whiteNoise;
    
    // osc1
    WaveOscillator waveOsc;
    
    // effects
    Bitcrusher bitcrusher;
};
