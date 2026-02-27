/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <memory>

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
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("osc1Level", 1), "Osc 1 Level", juce::NormalisableRange<float>(0.0f, 1.0f), 1.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("osc1SineLevel", 1), "Osc 1 Sine Level", juce::NormalisableRange<float>(0.0f, 1.0f), 1.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("osc1TriangleLevel", 1), "Osc 1 Triangle Level", juce::NormalisableRange<float>(0.0f, 1.0f), 1.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("osc1SquareLevel", 1), "Osc 1 Square Level", juce::NormalisableRange<float>(0.0f, 1.0f), 1.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("osc1Tune", 1), "Osc 1 Tune", -24.0f, 24.0f, 0.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("noiseLevel", 1), "Noise Level", juce::NormalisableRange<float>(0.0f, 1.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("bitcrusherBitDepth", 1), "Bit Depth", 1.0f, 32.0f, 32.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("lfo1Frequency", 1), "LFO 1 Frequency", juce::NormalisableRange<float>(0.0f, 40.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("lfo1Depth", 1), "LFO 1 Depth", juce::NormalisableRange<float>(0.0f, 1.0f), 1.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("lfo2Frequency", 1), "LFO 2 Frequency", juce::NormalisableRange<float>(0.0f, 40.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("lfo2Depth", 1), "LFO 2 Depth", juce::NormalisableRange<float>(0.0f, 1.0f), 1.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("outputVolume", 1), "Output Volume", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f)
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
    lfo1FrequencyParameter = parameters.getRawParameterValue("lfo1Frequency");
    lfo1DepthParameter = parameters.getRawParameterValue("lfo1Depth");
    lfo2FrequencyParameter = parameters.getRawParameterValue("lfo2Frequency");
    lfo2DepthParameter = parameters.getRawParameterValue("lfo2Depth");
    outputVolumeParameter = parameters.getRawParameterValue("outputVolume");
    
    for (int i = 0; i < numberOfVoices; ++i)
    {
        voices.push_back(std::make_unique<Voice>());
        voices.back()->addNoiseLevelModifier(lfo2);
        voices.back()->addOscTuneModifier(lfo2);
    }
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
    // Pre-playback initialisation
    for (auto voice : voices)
    {
        voice->sampleRate = sampleRate;
    }
    // Refactor repetitive code
    lfo1.setSampleRate(sampleRate);
    lfo1.startOsc(*lfo1FrequencyParameter);
    lfo1.reserveSpace(samplesPerBlock);
    lfo2->setSampleRate(sampleRate);
    lfo2->startOsc(*lfo2FrequencyParameter);
    lfo2->reserveSpace(samplesPerBlock);
}

void Shamsynth1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    //  TODO: Is this necessary (I don't think so)
    voices.clear();
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
    float currentNoiseLevel = *noiseLevelParameter;
    float currentLfo1Frequency = *lfo1FrequencyParameter;
    float currentLfo1Depth = *lfo1DepthParameter;
    float currentLfo2Frequency = *lfo2FrequencyParameter;
    float currentLfo2Depth = *lfo2DepthParameter;
    float currentOutputVolume = *outputVolumeParameter;
    
    // MIDI
    // Avoid changing midiMessages
    juce::MidiBuffer midiBuffer = midiMessages;
    // Keyboard component in plugin window
    keyboardState.processNextMidiBuffer(midiBuffer, 0, totalNumSamples, true);
    processMidi(midiBuffer);
    
    // LFOs etc
    lfo1.setFrequency(currentLfo1Frequency);
    lfo1.setDepth(currentLfo1Depth);
    lfo1.calculateNextBlock(totalNumSamples);
    lfo2->setFrequency(currentLfo2Frequency);
    lfo2->setDepth(currentLfo2Depth);
    lfo2->calculateNextBlock(totalNumSamples);
    
    // Synthesis
    for (auto& voice : voices)
    {
        voice->updateOsc1Level(currentOsc1Level);
        voice->updateOsc1SineLevel(currentOsc1SineLevel);
        voice->updateOsc1TriangleLevel(currentOsc1TriangleLevel);
        voice->updateOsc1SquareLevel(currentOsc1SquareLevel);
        voice->updateOsc1Tune(currentOsc1Tune);
        voice->updateNoiseLevel(currentNoiseLevel);
        voice->updateBitcrusherBitDepth(currentBitcrusherBitDepth);
        voice->processBlock(buffer, totalNumOutputChannels);
    }

    // Effects
    // for (auto& effect : effects)
        // {effect->processBlock(buffer);}

    // Final volume
    // Scale down volume to account for increase from LFO and prevent clipping
    float scaledOutputVolume = currentOutputVolume * outputVolumeScale;
    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        for (int sample = 0; sample < totalNumSamples; ++sample)
        {
            float processedOutputVolume = scaledOutputVolume * (lfo1.getValue(sample) + 1);
            float finalValue = buffer.getSample(channel, sample) * processedOutputVolume;
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
}

void Shamsynth1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
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
    // If this note is not already down
    if (!voiceWithNoteDown(p_midiNoteNumber))
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
        voices[index]->silence();
    }
}

std::optional<int> Shamsynth1AudioProcessor::voiceWithNoteDown(int p_midiNoteNumber)
{
    for (int i = 0; i < voices.size(); ++i)
    {
//        if (voices[i]->isActive() && voices[i]->getMidiNoteNumber() == p_midiNoteNumber)
//        {
//            return i;
//        }
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
