/*
  ==============================================================================

    Parameters.h
    Created: 17 Mar 2026 1:42:36am
    Author:  Orlando Shamlou

  ==============================================================================
*/

/*
 ### Parameter location list ###
 Location for all variables controlled by parameters
 
 ## Osc 1 ##
 - WaveOscillator
    level (Modulatablefloat)
    sine level (f)
    triangle level (f)
    square level (f)
    tune (ModulatableFloat)
 noise level (ModulatableFloat)
 bit depth (f)
 wavefolder threshold (f)
 wavefolder amount (f)
 
 ## Env 1 ##
 a
 d
 s
 r
 (all f)
 
 ## LFO 1 ##
 frequency (f)
 depth (f)
 
 ## LFO 2 ##
 frequency depth
 
 ## Synth ##
 output volume (f)
 power on (bool)
 
 */

#pragma once

#include "Modulation/ModulationIOList.h"

#include <JuceHeader.h>

#include <string>
#include <vector>

namespace ParameterInfo {

    // TODO: refactor repetitive classes
    // I avoid inheritance in the project but here should be ok as these structs aren't used during processing (check this!)

    struct ParameterNames
    {
        const std::string ID;
        const std::string name;
    };

    struct RangeValues {
        const float min;
        const float max;
        const float interval;
        const float skewFactor;
        const bool useSymmetricSkew = false;
    };

    struct ParameterFloatInfo
    {
        const ParameterNames names;
        const RangeValues rangeValues;
        const float defaultValue;
        std::string ID() const {return names.ID;}
        std::string name() const {return names.name;}
        juce::NormalisableRange<float> getRange() const;
    };

    struct ParameterBoolInfo
    {
        const ParameterNames names;
        const bool defaultValue;
        std::string ID() const {return names.ID;}
        std::string name() const {return names.name;}
    };

    struct ModulationOutputNames
    {
        const ParameterNames names;
        std::string ID() const {return names.ID;}
        std::string name() const {return names.name;}
    };

    // TODO: add getName() and getID()
    // This provides the info needed to create an AudioParameterFloat to the APVTS, link that parameter to (a wrapper of) an atomic in the processor, and give that atomic the routing info to send to the mod matrix
    struct ModulationRoutingInfo {
        ParameterNames names;
        ModulationSourceID sourceID;
        ModulationDestinationID destinationID;
    };

    // TODO: rename makeRoutingScalingID for consistency
    static std::string makeRoutingScalingID(std::string output, std::string input);
    static std::string makeRoutingScalingName(std::string output, std::string input);

    // TODO: consider using modulationScalingParameterSubstrings, or defining the substrings elsewhere, as they are repeated here
    // Osc 1
    const ParameterFloatInfo osc1LevelValues = {{"osc1Level", "Osc 1 Level"}, {0.0f, 1.0f, 0.001f, 1.0f}, 1.0f};
    const ParameterFloatInfo osc1SineLevelValues = {{"osc1SineLevel", "Osc 1 Sine Level"}, {0.0f, 1.0f, 0.001f, 1.0f}, 1.0f};
    const ParameterFloatInfo osc1TriangleLevelValues = {{"osc1TriangleLevel", "Osc 1 Triangle Level"}, {0.0f, 1.0f, 0.001f, 1.0f}, 1.0f};
    const ParameterFloatInfo osc1SquareLevelValues = {{"osc1SquareLevel", "Osc 1 Square Level"}, {0.0f, 1.0f, 0.001f, 1.0f}, 1.0f};
    const ParameterFloatInfo osc1TuneValues = {{"osc1Tune", "Osc 1 Tune"}, {-24.0f, 24.0f, 0.001f, 1.0f, true}, 0.0f};
    const ParameterFloatInfo noiseLevelValues = {{"noiseLevel", "Noise Level"}, {0.0f, 1.0f, 0.001f, 0.75f}, 0.0f};
    static ParameterFloatInfo bitcrusherBitDepthValues = {{"bitDepth", "Bit Depth"}, {1.0f, 32.0f, 0.001f, 0.5f}, 32.0f};
    const ParameterFloatInfo osc1WavefolderThresholdValues = {{"osc1WavefolderThreshold", "Osc 1 Wavefolder Threshold"}, {0.0f, 1.0f, 0.001f, 1.0f}, 1.0f};
    const ParameterFloatInfo osc1WavefolderAmountValues = {{"osc1WavefolderAmount", "Osc 1 Wavefolder Amount"}, {0.0f, 4.0f, 0.001f, 1.0f}, 0.0f};
    // Env 1
    const ParameterFloatInfo env1AttackTimeValues = {{"env1AttackTime", "Env 1 Attack Time"}, {0.0f, 5.0f, 0.001f, 0.5f}, 0.0f};
    const ParameterFloatInfo env1DecayTimeValues = {{"env1DecayTime", "Env 1 Decay Time"}, {0.0f, 5.0f, 0.001f, 0.5f}, 0.0f};
    const ParameterFloatInfo env1SustainLevelValues = {{"env1SustainLevel", "Env 1 Sustain Level"}, {0.0f, 1.0f, 0.001f, 1.0f}, 1.0f};
    const ParameterFloatInfo env1ReleaseTimeValues = {{"env1ReleaseTime", "Env 1 Release Time"}, {0.0f, 5.0f, 0.001f, 0.5f}, 0.0f};
    // LFO 1
    const ParameterFloatInfo lfo1FrequencyValues = {{"lfo1Frequency", "LFO 1 Frequency"}, {0.0f, 40.0f, 0.001f, 0.5f}, 0.0f};
    const ParameterFloatInfo lfo1DepthValues = {{"lfo1Depth", "LFO 1 Depth"}, {0.0f, 1.0f, 0.001f, 0.5f}, 1.0f};
    // LFO 2
    const ParameterFloatInfo lfo2FrequencyValues = {{"lfo2Frequency", "LFO 2 Frequency"}, {0.0f, 40.0f, 0.001f, 0.5f}, 0.0f};
    const ParameterFloatInfo lfo2DepthValues = {{"lfo2Depth", "LFO 2 Depth"}, {0.0f, 1.0f, 0.001f, 0.5f}, 1.0f};
    // Synth
    const ParameterFloatInfo outputVolumeValues = {{"outputVolume", "Output Volume"}, {0.0f, 1.0f, 0.001f, 1.0f}, 0.5f};
    const ParameterBoolInfo powerOnValues = {{"powerOn", "Power On"}, true};

    // Scaling ids and names
    // these are used to form the full ids and names of modulation scaling parameters
    
    // ModulationOutputs
    // TODO: why does using ModulationOutputNames cause an error (see NOTES.md)
    const ParameterNames osc1EnvOutputSubstrings = {"osc1Env", "Osc 1 Env"};
    const ParameterNames lfo1OutputSubstrings = {"lfo1", "LFO 1"};
    const ParameterNames lfo2OutputSubstrings = {"lfo2", "LFO 2"};

    std::vector<ParameterInfo::ModulationRoutingInfo> makeModulationRoutingInfoList();
    const inline std::vector<ModulationRoutingInfo> modulationRoutingInfoList = makeModulationRoutingInfoList();

    // TODO: Use ModulationIOList IDs

    constexpr float levelMaximumModFactor = 1.0f;
    constexpr float tuneMaximumModFactor = 12.0f;
    // TODO: can this (and all ParameterFloatValues) be made constexpr? may need to move struct definitions to .cpp file?
    const float bitcrusherBitDepthMaximumModFactor = bitcrusherBitDepthValues.rangeValues.max;

    constexpr float scalingMin = -1.0f;
    constexpr float scalingMax = 1.0f;
    constexpr float scalingInterval = 0.01f;
    constexpr float scalingSkewFactor = 1.0f;
    constexpr float scalingUseSymmetricSkew = true;
    constexpr float scalingDefault = 0.0f;

    // Noise
    constexpr float noiseVolumeScale = 1.0f;
    constexpr float noiseHalfVolumeScale = noiseVolumeScale / 2.0f;

    // Overall synth volume
    constexpr float outputVolumeScale = 0.05f;
}
