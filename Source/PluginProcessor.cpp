/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "Modulation/ModulationIOList.h"
#include "Oscillators/Waveforms.h"
#include "Parameters.h"

using namespace ParameterValues;

//==============================================================================
Shamsynth1AudioProcessor::Shamsynth1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
     #if ! JucePlugin_IsMidiEffect
      #if ! JucePlugin_IsSynth
       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
      #endif
       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
     #endif
       ),
    parameters(*this, nullptr, juce::Identifier{JucePlugin_Name},
   {
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1LevelValues.ID, 1), osc1LevelValues.name, juce::NormalisableRange<float>(osc1LevelValues.minValue, osc1LevelValues.maxValue), osc1LevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1SineLevelValues.ID, 1), osc1SineLevelValues.name, juce::NormalisableRange<float>(osc1SineLevelValues.minValue, osc1SineLevelValues.maxValue), osc1SineLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1TriangleLevelValues.ID, 1), osc1TriangleLevelValues.name, juce::NormalisableRange<float>(osc1TriangleLevelValues.minValue, osc1TriangleLevelValues.maxValue), osc1TriangleLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1SquareLevelValues.ID, 1), osc1SquareLevelValues.name, juce::NormalisableRange<float>(osc1SquareLevelValues.minValue, osc1SquareLevelValues.maxValue), osc1SquareLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1TuneValues.ID, 1), osc1TuneValues.name, osc1TuneValues.minValue, osc1TuneValues.maxValue, osc1TuneValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(noiseLevelValues.ID, 1), noiseLevelValues.name, juce::NormalisableRange<float>(noiseLevelValues.minValue, noiseLevelValues.maxValue), noiseLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bitcrusherBitDepthValues.ID, 1), bitcrusherBitDepthValues.name, bitcrusherBitDepthValues.minValue, bitcrusherBitDepthValues.maxValue, bitcrusherBitDepthValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1WavefolderThresholdValues.ID, 1), osc1WavefolderThresholdValues.name, osc1WavefolderThresholdValues.minValue, osc1WavefolderThresholdValues.maxValue, osc1WavefolderThresholdValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1WavefolderAmountValues.ID, 1), osc1WavefolderAmountValues.name, osc1WavefolderAmountValues.minValue, osc1WavefolderAmountValues.maxValue, osc1WavefolderAmountValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(env1AttackTimeValues.ID, 1), env1AttackTimeValues.name, juce::NormalisableRange<float>(env1AttackTimeValues.minValue, env1AttackTimeValues.maxValue), env1AttackTimeValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(env1DecayTimeValues.ID, 1), env1DecayTimeValues.name, juce::NormalisableRange<float>(env1DecayTimeValues.minValue, env1DecayTimeValues.maxValue), env1DecayTimeValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(env1SustainLevelValues.ID, 1), env1SustainLevelValues.name, juce::NormalisableRange<float>(env1SustainLevelValues.minValue, env1SustainLevelValues.maxValue), env1SustainLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(env1ReleaseTimeValues.ID, 1), env1ReleaseTimeValues.name, juce::NormalisableRange<float>(env1ReleaseTimeValues.minValue, env1ReleaseTimeValues.maxValue), env1ReleaseTimeValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(lfo1FrequencyValues.ID, 1), lfo1FrequencyValues.name, juce::NormalisableRange<float>(lfo1FrequencyValues.minValue, lfo1FrequencyValues.maxValue), lfo1FrequencyValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(lfo1DepthValues.ID, 1), lfo1DepthValues.name, juce::NormalisableRange<float>(lfo1DepthValues.minValue, lfo1DepthValues.maxValue), lfo1DepthValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(lfo2FrequencyValues.ID, 1), lfo2FrequencyValues.name, juce::NormalisableRange<float>(lfo2FrequencyValues.minValue, lfo2FrequencyValues.maxValue), lfo2FrequencyValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(lfo2DepthValues.ID, 1), lfo2DepthValues.name, juce::NormalisableRange<float>(lfo2DepthValues.minValue, lfo2DepthValues.maxValue), lfo2DepthValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(outputVolumeValues.ID, 1), outputVolumeValues.name, juce::NormalisableRange<float>(outputVolumeValues.minValue, outputVolumeValues.maxValue), outputVolumeValues.defaultValue),
        std::make_unique<juce::AudioParameterBool>(juce::ParameterID(powerOnValues.ID, 1), powerOnValues.name, powerOnValues.defaultValue),
        // Routings
        std::make_unique<juce::AudioParameterBool>(juce::ParameterID("adsrToTune", 1), "LFO1 to Tune", false),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("osc1EnvToTuneScaling", 1), "Osc 1 Env To Tune Scaling", scalingMin, scalingMax, scalingDefault)
    })
#endif
{
    osc1LevelParameter = parameters.getRawParameterValue("osc1Level");
    osc1SineLevelParameter = parameters.getRawParameterValue("osc1SineLevel");
    osc1TriangleLevelParameter = parameters.getRawParameterValue("osc1TriangleLevel");
    osc1SquareLevelParameter = parameters.getRawParameterValue("osc1SquareLevel");
    osc1TuneParameter = parameters.getRawParameterValue("osc1Tune");
    noiseLevelParameter = parameters.getRawParameterValue("noiseLevel");
    bitcrusherBitDepthParameter = parameters.getRawParameterValue("bitcrusherBitDepth");
    osc1WavefolderThresholdParameter = parameters.getRawParameterValue("osc1WavefolderThreshold");
    osc1WavefolderAmountParameter = parameters.getRawParameterValue("osc1WavefolderAmount");
    env1AttackTimeParameter = parameters.getRawParameterValue("env1AttackTime");
    env1DecayTimeParameter = parameters.getRawParameterValue("env1DecayTime");
    env1SustainLevelParameter = parameters.getRawParameterValue("env1SustainLevel");
    env1ReleaseTimeParameter = parameters.getRawParameterValue("env1ReleaseTime");
    lfo1FrequencyParameter = parameters.getRawParameterValue("lfo1Frequency");
    lfo1DepthParameter = parameters.getRawParameterValue("lfo1Depth");
    lfo2FrequencyParameter = parameters.getRawParameterValue("lfo2Frequency");
    lfo2DepthParameter = parameters.getRawParameterValue("lfo2Depth");
    outputVolumeParameter = parameters.getRawParameterValue("outputVolume");
    powerOnParameter = parameters.getRawParameterValue("powerOn");
    // Routings
    adsrToTuneParameter = parameters.getRawParameterValue("adsrToTune");
    osc1EnvToTuneScalingParameter = parameters.getRawParameterValue("osc1EnvToTuneScaling");
    
    for (int i = 0; i < numberOfVoices; ++i)
    {
        voices.push_back(std::make_unique<Voice>());
    }
    populateModMatrix();
}

Shamsynth1AudioProcessor::~Shamsynth1AudioProcessor()
{
}

//==============================================================================
const juce::String Shamsynth1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Shamsynth1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Shamsynth1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Shamsynth1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Shamsynth1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Shamsynth1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Shamsynth1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Shamsynth1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Shamsynth1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Shamsynth1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Shamsynth1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // TODO: check that activating/deactivating buses calls prepareToPlay() (i.e. that num of channels will always be correct)
    int totalNumChannels = getTotalNumOutputChannels();
    if (getTotalNumInputChannels() > totalNumChannels)
    {
        int totalNumChannels = getTotalNumInputChannels();
    }
    
    expectedSamplesPerBlock = samplesPerBlock;
        
    reserveSignalBlockSpace(samplesPerBlock, totalNumChannels);
    updateSampleRate(sampleRate);
    
    lfo1.startOsc(*lfo1FrequencyParameter);
    lfo2.startOsc(*lfo2FrequencyParameter);
    
    Waveforms::populateWavetables();

    currentlyPowerOn = powerOnParameter.isTrue();
}

void Shamsynth1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Shamsynth1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Shamsynth1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto totalNumSamples = buffer.getNumSamples();
    if (totalNumSamples != expectedSamplesPerBlock)
    {
        reserveSignalBlockSpace(totalNumSamples, buffer.getNumChannels());
    }
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    //    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //        {buffer.clear (i, 0, buffer.getNumSamples());}
    // I am doing the above but for all channels - I need to check if this is correct
    for (auto i = 0; i < totalNumOutputChannels; ++i)
        {buffer.clear(i, 0, totalNumSamples);}

    if (!checkOnOffState())
    {
        return;
    }
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    // Parameter buffers
    float currentOsc1Level = *osc1LevelParameter;
    float currentOsc1SineLevel = *osc1SineLevelParameter;
    float currentOsc1TriangleLevel = *osc1TriangleLevelParameter;
    float currentOsc1SquareLevel = *osc1SquareLevelParameter;
    float currentOsc1Tune = *osc1TuneParameter;
    float currentBitcrusherBitDepth = *bitcrusherBitDepthParameter;
    float currentOsc1WavefolderThreshold = *osc1WavefolderThresholdParameter;
    float currentOsc1WavefolderAmount = *osc1WavefolderAmountParameter;
    float currentNoiseLevel = *noiseLevelParameter;
    float currentEnv1AttackTime = *env1AttackTimeParameter;
    float currentEnv1DecayTime = *env1DecayTimeParameter;
    float currentEnv1SustainLevel = *env1SustainLevelParameter;
    float currentEnv1ReleaseTime = *env1ReleaseTimeParameter;
    float currentLfo1Frequency = *lfo1FrequencyParameter;
    float currentLfo1Depth = *lfo1DepthParameter;
    float currentLfo2Frequency = *lfo2FrequencyParameter;
    float currentLfo2Depth = *lfo2DepthParameter;
    float currentOutputVolume = *outputVolumeParameter;
    bool currentlyRoutingADSRToTune = adsrToTuneParameter.isTrue();
    float currentosc1EnvToTuneScaling = *osc1EnvToTuneScalingParameter;
    
    // MIDI
    // processAllMidi();
    
    // Avoid changing midiMessages
    // TODO: Optimisation - should midiBuffer have space allocated in prepareToPlay()?
        // check the size of midibuffer - is it per message or per sample
    juce::MidiBuffer midiBuffer = midiMessages;
    // Add messages from plugin window keyboard component
    keyboardState.processNextMidiBuffer(midiBuffer, 0, totalNumSamples, true);
    // Trigger or silence voices
    // TODO: consider if silencing voices here affects modulation i/o
    processMidi(midiBuffer);
    
    // TEMPORARY
    // move to function e.g. clearAllModulationBlocks();
    for (auto voice : voices)
    {
        voice->clearModulationBlocks();
    }
    // TODO: make e.g. lfo->clearModulationBlock();
    lfo2.output->block->resetValues();
    
    // LFOs etc
    lfo1.setFrequency(currentLfo1Frequency);
    lfo1.setDepth(currentLfo1Depth);
    lfo1.calculateNextBlock(totalNumSamples);
    lfo2.setFrequency(currentLfo2Frequency);
    lfo2.setDepth(currentLfo2Depth);
    lfo2.calculateNextBlock(totalNumSamples);
    
    osc1EnvOutputManager->reserveSpace(totalNumSamples);
    osc1TuneInputManager->reserveSpace(totalNumSamples);
    
    // Synthesis & routing
    for (auto& voice : voices)
    {
        voice->updateOsc1Level(currentOsc1Level);
        voice->updateOsc1SineLevel(currentOsc1SineLevel);
        voice->updateOsc1TriangleLevel(currentOsc1TriangleLevel);
        voice->updateOsc1SquareLevel(currentOsc1SquareLevel);
        voice->updateOsc1Tune(currentOsc1Tune);
        voice->updateNoiseLevel(currentNoiseLevel);
        voice->updateBitcrusherBitDepth(currentBitcrusherBitDepth);
        voice->updateWavefolderThreshold(currentOsc1WavefolderThreshold);
        voice->updateWavefolderAmount(currentOsc1WavefolderAmount);
        voice->updateADSRSettings(currentEnv1AttackTime, currentEnv1DecayTime, currentEnv1SustainLevel, currentEnv1ReleaseTime);
        
        voice->envelope.calculateNextBlock(totalNumSamples);
    }
    if (currentlyRoutingADSRToTune)
    {
        modMatrix.sendModulation(ModulationSourceID::adsrEnv, ModulationDestinationID::osc1Tune, currentosc1EnvToTuneScaling);
    }
    // TODO: magic number
    modMatrix.sendModulation(ModulationSourceID::lfo1, ModulationDestinationID::osc1Level, 1.0f);
    modMatrix.sendModulation(ModulationSourceID::lfo2, ModulationDestinationID::osc1NoiseLevel, 1.0f);
    modMatrix.sendModulation(ModulationSourceID::lfo2, ModulationDestinationID::osc1Tune, 1.0f);
    for (auto& voice : voices)
    {
        voice->processBlock(buffer, totalNumOutputChannels);
    }
    
    // Effects
    // for (auto& effect : effects)
    // {effect->processBlock(buffer);}
    
    // Final volume
    // Scale down volume to prevent clipping
    float scaledOutputVolume = currentOutputVolume * outputVolumeScale;
    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        for (int sample = 0; sample < totalNumSamples; ++sample)
        {
            float finalValue = buffer.getSample(channel, sample) * scaledOutputVolume;
            buffer.setSample(channel, sample, finalValue);
        }
    }
}

//==============================================================================
bool Shamsynth1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Shamsynth1AudioProcessor::createEditor()
{
    return new Shamsynth1AudioProcessorEditor (*this);
}

//==============================================================================
void Shamsynth1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Shamsynth1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
        {
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Shamsynth1AudioProcessor();
}

// Check for noteOn and noteOff messages
// Currently only affects the first Voice, doesn't check that voices isn't empty, etc.
void Shamsynth1AudioProcessor::processMidi(juce::MidiBuffer& midiBuffer)
{
    for (const auto metadata : midiBuffer)
    {
        auto message = metadata.getMessage();
        if (message.isNoteOn())
        {
            int midiNoteNumber = message.getNoteNumber();
            triggerVoice(midiNoteNumber);
        }
        else if (message.isNoteOff())
        {
            int midiNoteNumber = message.getNoteNumber();
            silenceVoice(midiNoteNumber);
        }
    }
}

void Shamsynth1AudioProcessor::triggerVoice(int p_midiNoteNumber)
{
    
    if (voiceWithNoteDown(p_midiNoteNumber))
    {
        // TODO: optimise as function called twice
        voices[voiceWithNoteDown(p_midiNoteNumber).value()]->queueNote(p_midiNoteNumber);
    }
    else
    {
        // Find available Voice and trigger
        std::optional<int> voiceToUse = availableVoice();
        if (voiceToUse)
        {
            // Trigger it
            int index = voiceToUse.value();
            voices[index]->trigger(p_midiNoteNumber);
        }
    }
}

void Shamsynth1AudioProcessor::silenceVoice(int p_midiNoteNumber)
{
    std::optional<int> voiceToSilence = voiceWithNoteDown(p_midiNoteNumber);
    if (voiceToSilence)
    {
        int index = voiceToSilence.value();
        voices[index]->release();
    }
}

std::optional<int> Shamsynth1AudioProcessor::voiceWithNoteDown(int p_midiNoteNumber)
{
    for (int i = 0; i < voices.size(); ++i)
    {
        if (voices[i]->isActive())
        {
            if (voices[i]->getMidiNoteNumber() == p_midiNoteNumber)
            {
                return i;
            }
        }
    }
    return {};
}

std::optional<int> Shamsynth1AudioProcessor::availableVoice()
{
    for (int i = 0; i < voices.size(); ++i)
    {
        if (!voices[i]->isActive())
        {
            return i;
        }
    }
    return {};
}

bool Shamsynth1AudioProcessor::checkOnOffState()
{
    if (currentlyPowerOn)
    {
        // Just been told to switch off
        if (!powerOnParameter.isTrue())
        {
            resetState();
            currentlyPowerOn = false;
            return false;
        }
        else
        {
            return true;
        }
    }
    // Currently off
    else
    {
        // Just been told to turn on
        if (powerOnParameter.isTrue())
        {
            currentlyPowerOn = true;
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Shamsynth1AudioProcessor::resetState()
{
    // Reset Oscs
    for (auto voice : voices)
    {
        voice->reset();
    }
    // Reset LFOs
    lfo1.resetLFO();
    lfo2.resetLFO();
}

void Shamsynth1AudioProcessor::reserveSignalBlockSpace(int samplesPerBlock, int totalNumChannels)
{
    for (auto voice : voices)
    {
        voice->reserveSpace(samplesPerBlock, totalNumChannels);
    }
    lfo1.reserveSpace(samplesPerBlock);
    lfo2.reserveSpace(samplesPerBlock);
}

void Shamsynth1AudioProcessor::updateSampleRate(double sampleRate)
{
    for (auto voice : voices)
    {
        voice->setSampleRate(sampleRate);
    }
    lfo1.setSampleRate(sampleRate);
    lfo2.setSampleRate(sampleRate);
}

void Shamsynth1AudioProcessor::populateModMatrix()
{    
    // Assign outputs to all OutputManagers
        // Poly OutputManagers
    for (auto voice : voices)
    {
        osc1EnvOutputManager->addOutput(voice->getEnvelopeOutput());
    }
    // Mono/global OutputManagers
    lfo1OutputManager->addOutput(lfo1.output);
    lfo2OutputManager->addOutput(lfo2.output);
    // Assign inputs to all InputManagers
        // Poly InputManagers
    for (auto voice : voices)
    {
        osc1LevelInputManager->addTargetModulationFloat(voice->getLevelInput());
        osc1NoiseLevelInputManager->addTargetModulationFloat(voice->getNoiseLevelInput());
        osc1TuneInputManager->addTargetModulationFloat(voice->getTuneInput());
    }
    // Mono/global InputManagers
    
    // Add all OutputManagers to modMatrix
    modMatrix.addSource(ModulationSourceID::adsrEnv, osc1EnvOutputManager);
    modMatrix.addSource(ModulationSourceID::lfo1, lfo1OutputManager);
    modMatrix.addSource(ModulationSourceID::lfo2, lfo2OutputManager);
    
    // For each OutputManager
        // Add all InputManagers
    modMatrix.addRouting(ModulationSourceID::adsrEnv, ModulationDestinationID::osc1Tune, osc1TuneInputManager);
    modMatrix.addRouting(ModulationSourceID::lfo1, ModulationDestinationID::osc1Level, osc1LevelInputManager);
    modMatrix.addRouting(ModulationSourceID::lfo2, ModulationDestinationID::osc1NoiseLevel, osc1NoiseLevelInputManager);
    modMatrix.addRouting(ModulationSourceID::lfo2, ModulationDestinationID::osc1Tune, osc1TuneInputManager);
}
