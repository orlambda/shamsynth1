/*
  ==============================================================================

    Envelope.h
    Created: 2 Mar 2026 9:14:55am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "../Modulation/ModulationSignalBlock.h"

// ADSR envelope

class Envelope
{
public:
    enum class State
    {
        attack,
        decay,
        sustain,
        release,
        prematureRelease,
        quickReleaseToRetrigger,
        inactive
    };
    State currentState = State::inactive;
    bool isActive(){return currentState != State::inactive;}
    void setSampleRate(float rate){sampleRate = rate;}
    void progressPosition();
    void progressState();
    std::shared_ptr<ModulationSignalBlock> values = std::make_shared<ModulationSignalBlock>();
    void calculateNextBlock(int samples);
    void reserveSpace(float sampleCount);
    void setAttackTime(float seconds);
    void setDecayTime(float seconds);
    void setSustainLevel(float level);
    void setReleaseTime(float seconds);
    void trigger();
    void immediatelySilence(){currentState = State::inactive;}
    void release();
    void queueTrigger();
    void reset();
private:
    float sampleRate = 0.0f;
    // Position is from  [0-1)
    float position = 0.0f;
    float lastValueForQuickRelease = 0.0f;
    float lastValueForRelease = 0.0f;
    // Temporary: hard-coded heretw
    // SECONDS
    float attackTime = 0.0f;
    float decayTime = 0.0f;
    float sustainLevel = 1.0f;
    float releaseTime = 0.0f;
    float quickReleaseTime = 0.01f;
    bool timedSustain = false;

};
