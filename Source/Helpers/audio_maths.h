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
    float increaseHzUsingCents(float startingFrequency, float centsIncrease);
    // Probably don't need this
    float centsIntervalToHz(float startingFrequency, float centsIncrease);
}
