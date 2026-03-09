/*
  ==============================================================================

    wrappers.h
    Created: 9 Mar 2026 12:45:00pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <memory>

// Temporary wrapper
class atomicBool
{
    public:
    atomicBool(std::atomic<float>* p_p){
        p = p_p;}
    void setParam(std::atomic<float>* p_p){p = p_p;}
    std::atomic<float>* getParam(){return p;}
    std::atomic<float>* operator=(std::atomic<float>* p_p){return p = p_p;}
    bool isTrue(){return *p >= 0.5f;};
    private:
    std::atomic<float>* p = nullptr;
};
