/*
  ==============================================================================

    Parameters.cpp
    Created: 17 Mar 2026 1:42:36am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Parameters.h"

using namespace ParameterInfo;

std::vector<ParameterInfo::ModulationRoutingInfo> ParameterInfo::makeModulationRoutingInfoList()
{
    
    // TODO: make classes or type aliases to represent these pairs? move to scope accessible to processor for populating modMatrix?
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
    
    std::vector<ModulationRoutingInfo> infoList;
    
    for (auto output : outputInfoList)
    {
        for (auto input : inputInfoList)
        {
            infoList.push_back(ModulationRoutingInfo{
                {makeRoutingScalingID(output.first.ID , input.first.ID()), makeRoutingScalingName(output.first.ID, input.first.ID())},
                output.second,
                input.second
            });
        }
    };
    
    return infoList;
}

static std::string ParameterInfo::makeRoutingScalingID(std::string output, std::string input)
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

static std::string ParameterInfo::makeRoutingScalingName(std::string output, std::string input)
{
    return output + " to " + input + " Scaling";
}
