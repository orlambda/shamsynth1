/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


/*
 Members created by me
 */
 


/*
 End of members created by me
*/


//==============================================================================
Shamsynth1AudioProcessor::Shamsynth1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
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

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());
    // I am doing the above but for all channels - I need to check if this is correct
    for (auto i = 0; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    // Oscillators, etc.
        // For a complex synth, this will include all modulation, etc.
    
    // Temporary Voice instantiation until I have Voice ptrs/whatever somehow
    
    Voice v;
    voices.push_back(v);
//    Voice v1;
//    voices.push_back(v1);
//    Voice v2;
//    voices.push_back(v2);
    
    for (auto& voice : voices)
    {
         voice.processBlock(buffer, totalNumOutputChannels);
    }
    voices.pop_back();
//    voices.pop_back();
//    voices.pop_back();
    
//    juce::Random random;
//    
//    float totalNumSamples = buffer.getNumSamples();
//    
//    // Each oscillator/generator
//    // Starting with a white noise generator
//
//    for (auto sample = 0; sample < totalNumSamples; ++sample)
//    {
//        float sampleValue = random.nextFloat();
//        for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
//        {
//            buffer.setSample(channel, sample, sampleValue * 0.25 - 0.125);
//        }
//        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
    // Effects
    // for (auto& effect : effects)
        // {effect.processBlock(buffer};
    
    
    // Final volume
    
    
    // Original loop - we are not doing it like this
    //    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //    {
    //        auto* channelData = buffer.getWritePointer (channel);
    //
    //        // ..do something to the data...
    //    }
//}


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
