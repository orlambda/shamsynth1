/*
  ==============================================================================

    audio_maths.h
    Created: 9 Jan 2026 6:58:51pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <cmath>

namespace audio_maths
{
    float increaseHzUsingCents(float startingFrequency, float centsIncrease)
    {
        return startingFrequency * (pow(2, (centsIncrease / 1200)));
    }

    // Probably don't need this
    float centsIntervalToHz(float startingFrequency, float centsIncrease)
    {
        return increaseHzUsingCents(startingFrequency, centsIncrease) - startingFrequency;
    }
}
