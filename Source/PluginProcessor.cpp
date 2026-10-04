/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "Modulation/ModulationIOList.h"
#include "Oscillators/Waveforms.h"

#include <algorithm>

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
    parameters(*this, nullptr, juce::Identifier{JucePlugin_Name}, makeParameterLayout())
#endif
{
    assignParameters();
    addVoices();
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
void Shamsynth1AudioProcessor::prepareToPlay (double sampleRate, int p_expectedMaxFramesPerBlock)
{
    // TODO: check that activating/deactivating buses calls prepareToPlay() (i.e. that num of channels will always be correct)
    int totalNumChannels = getTotalNumOutputChannels();
    if (getTotalNumInputChannels() > totalNumChannels)
    {
        int totalNumChannels = getTotalNumInputChannels();
    }
    
    // TODO: remove member from class, make local to this function?
    expectedMaxFramesPerBlock = p_expectedMaxFramesPerBlock;
    
    maxFramesPerSubblock = calculateMaxFramesPerSubblock(expectedMaxFramesPerBlock);

    // TODO: rename or refactor this function. Voice's AudioBuffer is not a ModulationSignalBlock
    reserveSignalBlockSpace(maxFramesPerSubblock, totalNumChannels);
    updateSampleRate(sampleRate);
    
    lfo1.startOsc(*lfo1FrequencyParameter);
    lfo2.startOsc(*lfo2FrequencyParameter);
    
    Waveforms::populateWavetables();

    currentlyPowerOn = powerOnParameter.isTrue();
}

void Shamsynth1AudioProcessor::releaseResources()
{
    for (auto voice : voices)
    {
        voice->releaseResources();
    }
    lfo1.releaseResources();
    lfo2.releaseResources();
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
    auto totalFrames = buffer.getNumSamples();
    
    // TODO: refactor to function
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
    {
        buffer.clear(i, 0, totalFrames);
    }

    // MIDI
    // processAllMidi();?
    
    // TODO: I currently ignore sample position of midi messages
    // Allocate space for midiBuffer in prepareToPlay()
    // Should midi processing be incorporated into processSubblock()?
    
    // Avoid changing midiMessages
    juce::MidiBuffer midiBuffer = midiMessages;
    // Add messages from plugin window keyboard component
    // TODO: process in subblocks
    keyboardState.processNextMidiBuffer(midiBuffer, 0, totalFrames, true);
    // Trigger or silence voices
    // TODO: consider if silencing voices here affects modulation i/o
    processMidi(midiBuffer);
    
    // TODO:
    // Process all audio in subblocks
    // Index of first frame of the subblock
    int subblockIndex = 0;
    while (subblockIndex < totalFrames)
    {
        // TODO: compare std::min() vs conditional operator for performance
        int subblockFrameSize = std::min(totalFrames - subblockIndex, maxFramesPerSubblock);
        processSubblock(buffer, subblockIndex, subblockFrameSize);
        subblockIndex += subblockFrameSize;
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

// TODO: rename or refactor - this does more than checking the state
// updateAndReturnOnOffState()?
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
        // Just been told to switch on
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
    for (auto voice : voices)
    {
        voice->reset();
    }
    lfo1.resetLFO();
    lfo2.resetLFO();
}

void Shamsynth1AudioProcessor::reserveSignalBlockSpace(int framesPerBlock, int totalNumChannels)
{
    for (auto voice : voices)
    {
        voice->reserveSpace(framesPerBlock, totalNumChannels);
    }
    lfo1.reserveSpace(framesPerBlock);
    lfo2.reserveSpace(framesPerBlock);
}

int Shamsynth1AudioProcessor::calculateMaxFramesPerSubblock(int expectedMaxFramesPerBlock)
{
    return std::min(maxFramesPerAudioBuffer, expectedMaxFramesPerBlock);
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
    /*
     std::vector<std::pair<ParameterNames, ModulationSourceID>> outputInfoList = {
         {osc1EnvOutputSubstrings, ModulationSourceID::adsrEnv},
         {lfo1OutputSubstrings, ModulationSourceID::lfo1},
         {lfo2OutputSubstrings, ModulationSourceID::lfo2}
     };
     
     std::vector<std::pair<ParameterFloatInfo, ModulationDestinationID>> inputInfoList = {
         {osc1LevelValues, ModulationDestinationID::osc1Level},
         {noiseLevelValues, ModulationDestinationID::osc1NoiseLevel},
         {osc1TuneValues, ModulationDestinationID::osc1Tune},
         {bitcrusherBitDepthValues, ModulationDestinationID::osc1BitDepth}
     };
     */
    
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
        osc1BitDepthManager->addTargetModulationFloat(voice->getBitDepthInput());
    }
    
    // Mono/global InputManagers
    
    // Add all OutputManagers to modMatrix
    modMatrix.addSource(ModulationSourceID::adsrEnv, osc1EnvOutputManager);
    modMatrix.addSource(ModulationSourceID::lfo1, lfo1OutputManager);
    modMatrix.addSource(ModulationSourceID::lfo2, lfo2OutputManager);
    
    // TODO: move this info somewhere else e.g. an abstraction - wait till I know if I ever need it elsewhere before refactoring
    std::map<ModulationDestinationID, std::shared_ptr<ModulationInputManager>> destinationsInfo;
    destinationsInfo.insert({ModulationDestinationID::osc1Level, osc1LevelInputManager});
    destinationsInfo.insert({ModulationDestinationID::osc1NoiseLevel, osc1NoiseLevelInputManager});
    destinationsInfo.insert({ModulationDestinationID::osc1Tune, osc1TuneInputManager});
    destinationsInfo.insert({ModulationDestinationID::osc1BitDepth, osc1BitDepthManager});

    for (auto routingInfo : modulationRoutingInfoList)
    {
        modMatrix.addRouting(routingInfo.sourceID, routingInfo.destinationID, destinationsInfo[routingInfo.destinationID]);
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout Shamsynth1AudioProcessor::makeParameterLayout() {
    
    constexpr int versionHint = 1;
    
    juce::AudioProcessorValueTreeState::ParameterLayout layout {
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1LevelValues.ID(), versionHint), osc1LevelValues.name(), osc1LevelValues.getRange(),
            osc1LevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1SineLevelValues.ID(), versionHint), osc1SineLevelValues.name(), osc1SineLevelValues.getRange(), osc1SineLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1TriangleLevelValues.ID(), versionHint), osc1TriangleLevelValues.name(), osc1TriangleLevelValues.getRange(), osc1TriangleLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1SquareLevelValues.ID(), versionHint), osc1SquareLevelValues.name(), osc1SquareLevelValues.getRange(), osc1SquareLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1TuneValues.ID(), versionHint), osc1TuneValues.name(), osc1TuneValues.getRange(), osc1TuneValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(noiseLevelValues.ID(), versionHint), noiseLevelValues.name(), noiseLevelValues.getRange(), noiseLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(bitcrusherBitDepthValues.ID(), versionHint), bitcrusherBitDepthValues.name(), bitcrusherBitDepthValues.getRange(), bitcrusherBitDepthValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1WavefolderThresholdValues.ID(), versionHint), osc1WavefolderThresholdValues.name(), osc1WavefolderThresholdValues.getRange(), osc1WavefolderThresholdValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(osc1WavefolderAmountValues.ID(), versionHint), osc1WavefolderAmountValues.name(), osc1WavefolderAmountValues.getRange(), osc1WavefolderAmountValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(env1AttackTimeValues.ID(), versionHint), env1AttackTimeValues.name(), env1AttackTimeValues.getRange(), env1AttackTimeValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(env1DecayTimeValues.ID(), versionHint), env1DecayTimeValues.name(), env1DecayTimeValues.getRange(), env1DecayTimeValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(env1SustainLevelValues.ID(), versionHint), env1SustainLevelValues.name(), env1SustainLevelValues.getRange(), env1SustainLevelValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(env1ReleaseTimeValues.ID(), versionHint), env1ReleaseTimeValues.name(), env1ReleaseTimeValues.getRange(), env1ReleaseTimeValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(lfo1FrequencyValues.ID(), versionHint), lfo1FrequencyValues.name(), lfo1FrequencyValues.getRange(), lfo1FrequencyValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(lfo1DepthValues.ID(), versionHint), lfo1DepthValues.name(), lfo1DepthValues.getRange(), lfo1DepthValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(lfo2FrequencyValues.ID(), versionHint), lfo2FrequencyValues.name(), lfo2FrequencyValues.getRange(), lfo2FrequencyValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(lfo2DepthValues.ID(), versionHint), lfo2DepthValues.name(), lfo2DepthValues.getRange(), lfo2DepthValues.defaultValue),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(outputVolumeValues.ID(), versionHint), outputVolumeValues.name(), outputVolumeValues.getRange(), outputVolumeValues.defaultValue),
        
        std::make_unique<juce::AudioParameterBool>(juce::ParameterID(powerOnValues.ID(), versionHint), powerOnValues.name(), powerOnValues.defaultValue)
    };
        
    // Routings
    for (auto routingInfo : modulationRoutingInfoList)
    {
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(routingInfo.names.ID, versionHint), routingInfo.names.name, juce::NormalisableRange<float>(scalingMin, scalingMax, scalingInterval, scalingSkewFactor, scalingUseSymmetricSkew), scalingDefault));
    }
    return layout;
}

void Shamsynth1AudioProcessor::assignModulationScalingParameters()
{
    for (auto routingInfo : modulationRoutingInfoList)
    {
        modulationScalingParameters.push_back(ModulationScalingParameter(parameters.getRawParameterValue(routingInfo.names.ID), routingInfo.sourceID, routingInfo.destinationID));
    }
}

void Shamsynth1AudioProcessor::assignParameters()
{
    // TODO: use variable names from Parameters.h instead of string literals
    osc1LevelParameter = parameters.getRawParameterValue("osc1Level");
    osc1SineLevelParameter = parameters.getRawParameterValue("osc1SineLevel");
    osc1TriangleLevelParameter = parameters.getRawParameterValue("osc1TriangleLevel");
    osc1SquareLevelParameter = parameters.getRawParameterValue("osc1SquareLevel");
    osc1TuneParameter = parameters.getRawParameterValue("osc1Tune");
    noiseLevelParameter = parameters.getRawParameterValue("noiseLevel");
    bitcrusherBitDepthParameter = parameters.getRawParameterValue("bitDepth");
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
    
    // Routings - this will need to be done dynamically as mod matrix will grow
    osc1EnvToOsc1LevelScalingParameter = parameters.getRawParameterValue("osc1EnvToOsc1LevelScaling");
    osc1EnvToTuneScalingParameter = parameters.getRawParameterValue("osc1EnvToOsc1TuneScaling");
    lfo1ToOsc1LevelScalingParameter = parameters.getRawParameterValue("lfo1ToOsc1LevelScaling");
    lfo1ToTuneScalingParameter = parameters.getRawParameterValue("lfo1ToOsc1TuneScaling");
    
    assignModulationScalingParameters();
}

void Shamsynth1AudioProcessor::addVoices()
{
    for (int i = 0; i < numberOfVoices; ++i)
    {
        voices.push_back(std::make_unique<Voice>());
    }
}

void Shamsynth1AudioProcessor::sendModulations(int frames)
{
    for (auto scalingParameter : modulationScalingParameters)
    {
        modMatrix.sendModulation(scalingParameter.getSourceID(), scalingParameter.getDestinationID(), scalingParameter.getValue(), frames);
    }
}

void Shamsynth1AudioProcessor::processSubblock(juce::AudioBuffer<float>& buffer, const int subblockIndex, const int numFramesInSubblock)
{
    if (!checkOnOffState())
    {
        return;
    }
    
    // TODO: Keep in object, move this to function?
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
    
    // TODO: make container of buffer values of scaling parameters? Currently values are read while sending to modMatrix
    
    // TODO: is this necessary?
    // move to function e.g. clearAllModulationBlocks();
    for (auto voice : voices)
    {
        voice->clearModulationBlocks();
    }
    // TODO: make e.g. lfo.clearModulationBlock();
    // TODO: clear lfo1 too
    // TODO: check if clearing is necessary / if this is the place to do it
    // lfo1.output->block->resetValues();
    lfo2.output->block->resetValues();
    
    lfo1.setFrequency(currentLfo1Frequency);
    lfo1.setDepth(currentLfo1Depth);
    lfo1.calculateNextBlock(numFramesInSubblock);
    lfo2.setFrequency(currentLfo2Frequency);
    lfo2.setDepth(currentLfo2Depth);
    lfo2.calculateNextBlock(numFramesInSubblock);
    
    // TODO: delete this - check it is called in prepareToPlay()
    osc1EnvOutputManager->reserveSpace(numFramesInSubblock);
    osc1TuneInputManager->reserveSpace(numFramesInSubblock);
    
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
        
        voice->envelope.calculateNextBlock(numFramesInSubblock);
    }
    
    sendModulations(numFramesInSubblock);
    
    int totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto& voice : voices)
    {
        voice->processSubblock(buffer, totalNumOutputChannels, subblockIndex, numFramesInSubblock);
    }
    
    // Final volume
    // Scale down volume to prevent clipping
    float scaledOutputVolume = currentOutputVolume * outputVolumeScale;
    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        
        for (int frame = subblockIndex; frame < subblockIndex + numFramesInSubblock; ++frame)
        {
            float finalValue = buffer.getSample(channel, frame) * scaledOutputVolume;
            buffer.setSample(channel, frame, finalValue);
        }
    }
}
