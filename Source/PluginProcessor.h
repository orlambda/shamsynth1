/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "Voice/Voice.h"
#include "Effects/Bitcrusher.h"
#include "Oscillators/LowFreqOsc.h"

#include <JuceHeader.h>

#include <memory>

//==============================================================================
/**
*/
class Shamsynth1AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Shamsynth1AudioProcessor();
    ~Shamsynth1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // State
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* osc1LevelParameter = nullptr;
    std::atomic<float>* noiseLevelParameter = nullptr;
    std::atomic<float>* bitcrusherBitDepthParameter = nullptr;
    std::atomic<float>* lfo1FrequencyParameter = nullptr;
    std::atomic<float>* lfo1DepthParameter = nullptr;
    std::atomic<float>* lfo2FrequencyParameter = nullptr;
    std::atomic<float>* lfo2DepthParameter = nullptr;
    std::atomic<float>* outputVolumeParameter = nullptr;
    
    juce::MidiKeyboardState keyboardState;
    // temp for processing noteUp in monosynth
    int currentMidiNote = 0;
    
    LowFreqOsc lfo1;
    std::shared_ptr<LowFreqOsc> lfo2 = std::make_shared<LowFreqOsc>();

private:
    //==============================================================================
    std::vector<std::shared_ptr<Voice>> voices;
    
    // Input
    void processMidi(juce::MidiBuffer& midiBuffer);
    
    // Effects
    
    // Volume
    float outputVolumeScale = 0.5;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Shamsynth1AudioProcessor)
};
