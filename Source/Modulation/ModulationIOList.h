/*
  ==============================================================================

    ModulationIOList.h
    Created: 19 Mar 2026 5:01:35pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

// TODO: rename these because ID is also used for parameter strings?
enum class ModulationSourceID
{
    lfo1,
    lfo2,
    // TODO: rename e.g. osc1 env?
    adsrEnv,
    osc1Waveform
};

enum class ModulationDestinationID
{
    osc1Level,
    osc1NoiseLevel,
    osc1Tune,
    osc1BitDepth,
    lfo1Freq,
    lfo1Depth,
    lfo2Freq,
    lfo2Depth,
    wavefolderThreshold,
    wavefolderAmount
};
