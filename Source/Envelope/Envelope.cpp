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
    for (int i = 0; i < values.size(); ++i)
    {
        switch (static_cast<State>(currentState))
        {
            case State::attack:
                values.setValue(i, position);
                break;
            case State::sustain:
                values.setValue(i, 1.0);
                break;
            case State::release:
                values.setValue(i, 1.0-position);
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
    // Calculate length of sample in seconds
    if (currentState != State::inactive)
    {
        float sampleLength = 1.0/sampleRate;
        position += sampleLength;
        if (position >= 1.0)
        {
            switch (static_cast<State>(currentState))
            {
                case State::attack:
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

void Envelope::setAttackTime(float milliseconds)
{
    attackTime = milliseconds / 1000.0;
}
void Envelope::setReleaseTime(float milliseconds)
{
    releaseTime = milliseconds / 1000.0;
    
}
