/*
  ==============================================================================

    Parameters.h
    Created: 17 Mar 2026 1:42:36am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <string>

// TODO: use namespace?

constexpr float osc1TuneMin = -24.0f;
constexpr float osc1TuneMax = 24.0f;
constexpr float osc1TuneDefault = 0.0f;

constexpr float osc1TuneModMultiplicationFactor = 12.0f;

constexpr float scalingMin = 0.0f;
constexpr float scalingMax = 1.0f;
constexpr float scalingDefault = 0.0f;

class Routings {
public:
static std::string makeScalingID(std::string output, std::string input)
{
    if (!output.empty())
    {
        output[0] = tolower(output[0]);
    }
    if (!input.empty())
    {
        input[0] = toupper(input[0]);
    }
    return output + "To" + input + "Scaling";
}
static std::string makeRoutingScalingName(std::string output, std::string input)
{
    return output + " to " + input + "Scaling";
}
};
