/*
  ==============================================================================

    Envelope.h
    Created: 2 Mar 2026 9:14:55am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "../ModifierBlock/ModifierBlock.h"

#include <vector>

// AR envelope - sustains while key is held

class Envelope
{
public:
    enum class State
    {
        attack,
        sustain,
        release,
        inactive
    };
    State currentState = State::inactive;
    bool isActive(){return currentState != State::inactive;}
    void setSampleRate(float rate){sampleRate = rate;}
    void progressPosition();
    void progressState();
    ModifierBlock values;
    void calculateNextBlock(int samples);
    void reserveSpace(float sampleCount);
    void setAttackTime(float milliseconds);
    void setReleaseTime(float milliseconds);
    void trigger(){currentState = State::attack; position = 0.0;}
    void immediatelySilence(){currentState = State::inactive;}
    void release();
private:
    float sampleRate = 0.0;
    // Position is from  [0-1)
    float position = 0.0;
    // Temporary: hard-coded here
    // SECONDS
    float attackTime = 0.5;
    float releaseTime = 0.5;
};
