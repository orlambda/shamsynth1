/*
  ==============================================================================

    Voice.cpp
    Created: 6 Oct 2025 11:37:50pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Voice.h"

#include <iostream>

Voice::Voice() {
}

void Voice::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    if (isActive())
    {
        float totalNumChannels = buffer.getNumChannels();
        float totalNumSamples = buffer.getNumSamples();
        if (totalNumSamples != voiceBuffer.getNumSamples() || totalNumChannels != voiceBuffer.getNumChannels())
        {
            reserveSpace(totalNumSamples, totalNumChannels);
        }
        voiceBuffer.clear();
        envelope.calculateNextBlock(totalNumSamples);
        waveOsc.processBlock(voiceBuffer, totalNumOutputChannels, envelope);
        whiteNoise.processBlock(voiceBuffer, totalNumOutputChannels);
        bitcrusher.processBlock(voiceBuffer, totalNumOutputChannels);
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            // TODO: check and use this instead
//            buffer.addFrom(i, 0, voiceBuffer, i, 0, totalNumSamples);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                buffer.addSample(channel, sample, voiceBuffer.getSample(channel, sample));
            }
        }
    }
}

void Voice::setSampleRate(float rate)
{
    sampleRate = rate;
    waveOsc.sampleRate = sampleRate;
    envelope.setSampleRate(rate);
}

void Voice::reserveSpace(int samplesPerBlock, int totalNumChannels)
{
    envelope.reserveSpace(samplesPerBlock);
    voiceBuffer.setSize(totalNumChannels, samplesPerBlock);
}

void Voice::updateADSRSettings(float a, float d, float s, float r)
{
    envelope.setAttackTime(a);
    envelope.setDecayTime(d);
    envelope.setSustainLevel(s);
    envelope.setReleaseTime(r);
}

void Voice::trigger(int p_midiNoteNumber) {
    envelope.trigger();
    midiNoteNumber = p_midiNoteNumber;
    waveOsc.startNote(getFundamental());
}

void Voice::release() {
//    envelope.immediatelySilence();
    envelope.release();
}

void Voice::queueNote(int p_midiNoteNumber)
{
    envelope.queueTrigger();
    // TODO: envelope trigger is queued but pitch change is not
    // This is not yet a problem as only repeated notes are currently queued
    midiNoteNumber = p_midiNoteNumber;
    waveOsc.startNote(getFundamental());
}

void Voice::addNoiseLevelModifier(std::shared_ptr<LowFreqOsc> modifier)
{
    whiteNoise.levelModifiers.push_back(modifier);
}

void Voice::addOscTuneModifier(std::shared_ptr<ModifierBlock> modifier)
{
    waveOsc.tuneModifiers.push_back(modifier);
}

void Voice::reset()
{
    waveOsc.reset();
    envelope.reset();
}
