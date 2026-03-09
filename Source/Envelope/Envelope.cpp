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
            {
                float value = position;
                lastValueForRelease = value;
                values.setValue(i, value);
                break;
                }
            case State::decay:
            {
                float value = 1.0f-(position*(1.0f-sustainLevel));
                lastValueForRelease = value;
                lastValueForQuickRelease = value;
                values.setValue(i, value);
                break;
            }
            case State::sustain:
            {
                float value = sustainLevel;
                lastValueForRelease = value;
                lastValueForQuickRelease = value;
                values.setValue(i, value);
                break;
            }
            case State::release:
            {
                float value = sustainLevel-(sustainLevel*position);
                lastValueForQuickRelease = value;
                values.setValue(i, value);
                break;
            }
            case State::prematureRelease:
            {
                float value = lastValueForRelease-(lastValueForRelease*position);
                lastValueForQuickRelease = value;
                values.setValue(i, value);
                break;
            }
            case State::quickReleaseToRetrigger:
            {
                float value = lastValueForQuickRelease-(lastValueForQuickRelease*position);
                values.setValue(i, value);
                break;
            }
            case State::inactive:
            {
                values.setValue(i, 0.0f);
                break;
            }
            default:
            {
                break;
            }
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
            {
                position += 1.0f/(attackTime*sampleRate);
                break;
            }
            case State::decay:
            {
                position += 1.0f/(decayTime*sampleRate);
                break;
            }
            case State::release:
            case State::prematureRelease:
            {
                position += 1.0f/(releaseTime*sampleRate);
                break;
            }
            case State::quickReleaseToRetrigger:
            {
                position += 1.0f/(quickReleaseTime*sampleRate);
                break;
            }
            default:
                break;
        }
        if (position >= 1.0f)
        {
            switch (static_cast<State>(currentState))
            {
                case State::attack:
                case State::decay:
                case State::release:
                case State::prematureRelease:
                case State::quickReleaseToRetrigger:
                {
                    progressState();
                    break;
                }
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
        {
            currentState = State::decay;
            break;
        }
        case State::decay:
        {
            currentState = State::sustain;
            break;
        }
        case State::sustain:
        {
            currentState = State::release;
            break;
        }
        case State::release:
        case State::prematureRelease:
        {
            currentState = State::inactive;
            break;
        }
        case State::quickReleaseToRetrigger:
        {
            // Probably unnecesary as immediately retriggering
            currentState = State::inactive;
            trigger();
        }
        case State::inactive:
        {
            break;
        }
        default:
        {
            break;
        }
    }
    position = 0.0f;
}

void Envelope::release()
{
    if (currentState == State::sustain)
    {
        currentState = State::release;
        position = 0.0f;
    }
    else
    {
        currentState = State::prematureRelease;
        position = 0.0f;
    }
}

void Envelope::trigger()
{
    currentState = State::attack; position = 0.0f;
}

void Envelope::queueTrigger()
{
    if (currentState == State::attack || currentState == State::decay || currentState == State::sustain)
    {
        currentState = State::quickReleaseToRetrigger;
        position = 0.0f;
    }
    else
    {
        trigger();
    }
}

void Envelope::setAttackTime(float seconds)
{
    // min ramp is 2 samples
    float lengthOfSample = 1.0f/sampleRate;
    float min = lengthOfSample * 2.0f;
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
    float lengthOfSample = 1.0f/sampleRate;
    float min = lengthOfSample * 2.0f;
    if (decayTime < min)
    {
        decayTime = min;
    }
    else
    {
        decayTime = seconds;
    }
}

void Envelope::setSustainLevel(float level)
{
    sustainLevel = level;
}

void Envelope::setReleaseTime(float seconds)
{
    // min ramp is 2 samples
    float lengthOfSample = 1.0f/sampleRate;
    float min = lengthOfSample * 2.0f;
    if (releaseTime < min)
    {
        releaseTime = min;
    }
    else
    {
        releaseTime = seconds;
    }
}

void Envelope::reset()
{
    position = 0.0f;
    lastValueForQuickRelease = 0.0f;
    lastValueForRelease = 0.0f;
    currentState = State::inactive;
}
