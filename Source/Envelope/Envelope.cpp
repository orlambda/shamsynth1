/*
  ==============================================================================

    Envelope.cpp
    Created: 2 Mar 2026 9:14:55am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Envelope.h"

void Envelope::calculateNextBlock(int samples)
{
    reserveSpace(samples);
    // TEMPORARY: ALWAYS SILENCE
    for (int i = 0; i < samples; ++i)
    {
        switch (static_cast<State>(currentState))
        {
            case State::attack:
                values.setValue(i, position);
                break;
            case State::decay:
                values.setValue(i, 1.0-(position*(1-sustainLevel)));
                break;
            case State::sustain:
                values.setValue(i, sustainLevel);
                break;
            case State::release:
                values.setValue(i, sustainLevel-(sustainLevel*position));
                break;
            case State::inactive:
                values.setValue(i, 0.0);
                break;
            default:
                break;
        }
        progressPosition();
    }
}

void Envelope::reserveSpace(float sampleCount)
{
    if (sampleCount > values.size())
    {
        values.reserveSpace(sampleCount);
    }
}

void Envelope::progressPosition()
{
    if (currentState != State::inactive)
    {
        switch (static_cast<State>(currentState))
        {
            case State::attack:
                position += 1.0/(attackTime*sampleRate);
                break;
            case State::decay:
                position += 1.0/(decayTime*sampleRate);
                break;
            case State::release:
                position += 1.0/(releaseTime*sampleRate);
                break;
            default:
                break;
        }
        if (position >= 1.0)
        {
            switch (static_cast<State>(currentState))
            {
                case State::attack:
                    progressState();
                    break;
                case State::decay:
                    progressState();
                    break;
                case State::release:
                    progressState();
                    break;
                default:
                    break;
            }
        }
    }
}

void Envelope::progressState()
{
    switch (static_cast<State>(currentState))
    {
        case State::attack:
            currentState = State::decay;
            break;
        case State::decay:
            currentState = State::sustain;
            break;
        case State::sustain:
            currentState = State::release;
            break;
        case State::release:
            currentState = State::inactive;
            break;
        case State::inactive:
            break;
        default:
            break;
    }
    position = 0.0;
}

void Envelope::release()
{
    currentState = State::release;
    position = 0.0;
}

void Envelope::setAttackTime(float seconds)
{
    // min ramp is 2 samples
    float lengthOfSample = 1.0/sampleRate;
    float min = lengthOfSample * 2.0;
    if (attackTime < min)
    {
        attackTime = min;
    }
    else
    {
        attackTime = seconds;
    }
}

void Envelope::setDecayTime(float seconds)
{
    // min ramp is 2 samples
    float lengthOfSample = 1.0/sampleRate;
    float min = lengthOfSample * 2.0;
    if (decayTime < min)
    {
        decayTime = min;
    }
    else
    {
        decayTime = seconds;
    }
}
void Envelope::setReleaseTime(float seconds)
{
    // min ramp is 2 samples
    float lengthOfSample = 1.0/sampleRate;
    float min = lengthOfSample * 2.0;
    if (releaseTime < min)
    {
        releaseTime = min;
    }
    else
    {
        releaseTime = seconds;
    }
    
}
