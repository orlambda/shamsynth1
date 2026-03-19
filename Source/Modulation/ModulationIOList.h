/*
  ==============================================================================

    ModulationIOList.h
    Created: 19 Mar 2026 5:01:35pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

enum class ModulationSourceID
{
    lfo1,
    lfo2,
    adsrEnv,
    osc1Waveform
};

enum class ModulationDestinationID
{
    osc1Level,
    osc1Tune,
    lfo1Freq,
    lfo1Depth,
    lfo2Freq,
    lfo2Depth,
    wavefolderThreshold,
    wavefolderScale
};
