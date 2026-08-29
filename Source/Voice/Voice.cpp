/*
  ==============================================================================

    Voice.cpp
    Created: 6 Oct 2025 11:37:50pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Voice.h"

Voice::Voice()
{
}

void Voice::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    if (isActive())
    {
        float totalNumChannels = buffer.getNumChannels();
        float totalNumFrames = buffer.getNumSamples();
        if (totalNumFrames != voiceBuffer.getNumSamples() || totalNumChannels != voiceBuffer.getNumChannels())
        {
            reserveSpace(totalNumFrames, totalNumChannels);
        }
        voiceBuffer.clear();
        waveOsc.processBlock(voiceBuffer, totalNumOutputChannels);
        whiteNoise.processBlock(voiceBuffer, totalNumOutputChannels);
        bitcrusher.processBlock(voiceBuffer, totalNumOutputChannels);
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            for (int frame = 0; frame < buffer.getNumSamples(); ++frame)
            {
                buffer.addSample(channel, frame, voiceBuffer.getSample(channel, frame));
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

void Voice::reserveSpace(int framesPerBlock, int totalNumChannels)
{
    waveOsc.reserveSpace(framesPerBlock);
    envelope.reserveSpace(framesPerBlock);
    whiteNoise.reserveSpace(framesPerBlock);
    bitcrusher.reserveSpace(framesPerBlock);
    voiceBuffer.setSize(totalNumChannels, framesPerBlock);
}

void Voice::clearModulationBlocks()
{
    waveOsc.clearModulationSignalBlocks();
    // TODO: envelope? is this cleared somewhere else?
    whiteNoise.clearModulationSignalBlocks();
    bitcrusher.clearModulationSignalBlocks();
    voiceBuffer.clear();
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

void Voice::reset()
{
    waveOsc.reset();
    envelope.reset();
}

std::shared_ptr<ModulationOutput> Voice::getEnvelopeOutput()
{
    return envelope.output;
}

std::shared_ptr<ModulatableFloat> Voice::getLevelInput()
{
    return waveOsc.currentLevel;
}

std::shared_ptr<ModulatableFloat> Voice::getNoiseLevelInput()
{
    return whiteNoise.level;
}

std::shared_ptr<ModulatableFloat> Voice::getTuneInput()
{
    return waveOsc.currentTune;
}


std::shared_ptr<ModulatableFloat> Voice::getBitDepthInput()
{
    return bitcrusher.getBitDepthInput();
}
