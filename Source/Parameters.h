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

#include <string>

namespace ParameterValues {

    // TODO: make struct containing const std::string ID and const std::string name

    struct ParameterFloatValues
    {
        const std::string ID;
        const std::string name;
        const float minValue;
        const float maxValue;
        const float defaultValue;
    };

    struct ParameterBoolValues
    {
        const std::string ID;
        const std::string name;
        const bool defaultValue;
    };
    
    struct modulationOutputScalingParameterSubstrings
    {
        const std::string ID;
        const std::string name;
    };

    // TODO: consider using modulationScalingParameterSubstrings, or defining the substrings elsewhere, as they are repeated here
    // Osc 1
    const ParameterFloatValues osc1LevelValues = {"osc1Level", "Osc 1 Level", 0.0f, 1.0f, 1.0f};
    const ParameterFloatValues osc1SineLevelValues = {"osc1SineLevel", "Osc 1 Sine Level", 0.0f, 1.0f, 1.0f};
    const ParameterFloatValues osc1TriangleLevelValues = {"osc1TriangleLevel", "Osc 1 Triangle Level", 0.0f, 1.0f, 1.0f};
    const ParameterFloatValues osc1SquareLevelValues = {"osc1SquareLevel", "Osc 1 Square Level", 0.0f, 1.0f, 1.0f};
    const ParameterFloatValues osc1TuneValues = {"osc1Tune", "Osc 1 Tune", -24.0f, 24.0f, 0.0f};
    const ParameterFloatValues noiseLevelValues = {"noiseLevel", "Noise Level", 0.0f, 1.0f, 0.0f};
    const ParameterFloatValues bitcrusherBitDepthValues = {"bitDepth", "Bit Depth", 1.0f, 32.0f, 32.0f};
    const ParameterFloatValues osc1WavefolderThresholdValues = {"osc1WavefolderThreshold", "Osc 1 Wavefolder Threshold", 0.0f, 1.0f, 1.0f};
    const ParameterFloatValues osc1WavefolderAmountValues = {"osc1WavefolderAmount", "Osc 1 Wavefolder Amount", 0.0f, 4.0f, 0.0f};
    // Env 1
    const ParameterFloatValues env1AttackTimeValues = {"env1AttackTime", "Env 1 Attack Time", 0.0f, 5.0f, 0.0f};
    const ParameterFloatValues env1DecayTimeValues = {"env1DecayTime", "Env 1 Decay Time", 0.0f, 5.0f, 0.0f};
    const ParameterFloatValues env1SustainLevelValues = {"env1SustainLevel", "Env 1 Sustain Level", 0.0f, 1.0f, 1.0f};
    const ParameterFloatValues env1ReleaseTimeValues = {"env1ReleaseTime", "Env 1 Release Time", 0.0f, 5.0f, 0.0f};
    // LFO 1
    const ParameterFloatValues lfo1FrequencyValues = {"lfo1Frequency", "LFO 1 Frequency", 0.0f, 40.0f, 0.0f};
    const ParameterFloatValues lfo1DepthValues = {"lfo1Depth", "LFO 1 Depth", 0.0f, 1.0f, 1.0f};
    // LFO 2
    const ParameterFloatValues lfo2FrequencyValues = {"lfo2Frequency", "LFO 2 Frequency", 0.0f, 40.0f, 0.0f};
    const ParameterFloatValues lfo2DepthValues = {"lfo2Depth", "LFO 2 Depth", 0.0f, 1.0f, 1.0f};
    // Synth
    const ParameterFloatValues outputVolumeValues = {"outputVolume", "Output Volume", 0.0f, 1.0f, 0.5f};
    const ParameterBoolValues powerOnValues = {"powerOn", "Power On", true};

    // Scaling ids and names
    // these are used to form the full ids and names of modulation scaling parameters
    
    // ModulationOutputs
    const modulationOutputScalingParameterSubstrings osc1EnvOutputSubstrings = {"osc1Env", "Osc 1 Env"};
    const modulationOutputScalingParameterSubstrings lfo1OutputSubstrings = {"lfo1", "LFO 1"};
    const modulationOutputScalingParameterSubstrings lfo2OutputSubstrings = {"lfo2", "LFO 2"};

    constexpr float levelMaximumModFactor = 1.0f;
    constexpr float tuneMaximumModFactor = 12.0f;
    // TODO: can this (and all ParameterFloatValues) be made constexpr? may need to move struct definitions to .cpp file?
    const float bitcrusherBitDepthMaximumModFactor = bitcrusherBitDepthValues.maxValue;

    constexpr float scalingMin = -1.0f;
    constexpr float scalingMax = 1.0f;
    constexpr float scalingDefault = 0.0f;

    // Noise
    constexpr float noiseVolumeScale = 1.0f;
    constexpr float noiseHalfVolumeScale = noiseVolumeScale / 2.0f;

    // Overall synth volume
    constexpr float outputVolumeScale = 0.05f;
}

class Routings {
public:
    static std::string makeScalingID(std::string output, std::string input)
    {
        if (!output.empty())
        {
            output[0] = tolower(output[0]);
        }
        if (!input.empty())
        {
            input[0] = toupper(input[0]);
        }
        return output + "To" + input + "Scaling";
}
    static std::string makeRoutingScalingName(std::string output, std::string input)
    {
        return output + " to " + input + " Scaling";
    }
};
