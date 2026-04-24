/*
  ==============================================================================

    audio_maths.cpp
    Created: 9 Jan 2026 6:58:51pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "audio_maths.h"

float audio_maths::increaseHzUsingCents(float startingFrequency, float centsIncrease)
{
    return startingFrequency * (pow(2.0f, (centsIncrease / 1200.0f)));
}

// Probably don't need this
float audio_maths::centsIntervalToHz(float startingFrequency, float centsIncrease)
{
    return increaseHzUsingCents(startingFrequency, centsIncrease) - startingFrequency;
}
