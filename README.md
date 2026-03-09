# shamsynth1 v1.0.25

## IMPORTANT SAFETY WARNING
This audio plugin may contain errors which result in extremely loud and unexpected sounds. To protect your hearing, please use at a low volume and do not listen on headphones.

## Overview
A polyphonic synthesiser plugin made with C++ and JUCE with a variety of waveforms, white noise, a bitcrusher, and LFOs.

## Installation and usage
To compile this plugin you will need to use [JUCE](https://juce.com/get-juce/). Clone the repo, open the `.jucer` file in the Projucer, save and open in your IDE, and build. Once you have downloaded or built the plugin, move it to the relevant folder. E.g. for AU plugins on macOS, the folder is `/Library/Audio/Plug-Ins/Components`. The folder location is different on Windows and for VST3 - check the location for your system. You should now be able to open the plugin in a DAW or other host, such as Logic Pro or Reaper. You may need to scan for new plugins. JUCE also provide an audio plugin host for debugging if you don't want to install a full DAW - see [https://juce.com/tutorials/tutorial_create_projucer_basic_plugin/]() and scroll to 'Set up plug-in debugging (optional)' for instructions on how to install that. You don't need to set the plugin host as an executable in your IDE unless you are planning on debugging.

I am using macOS 15 and haven't tested the plugin on other platforms. I test both AU and VST3 builds. I hope to build to CLAP when JUCE 9 is released.

## Current features
- 16-voice polyphony
- Oscillator per voice
    - Level parameter & slider
    - Sin level parameter & slider
    - Triangle level parameter & slider
    - Square level parameter & slider
    - Tune parameter & slider
- Bitcrusher per voice
    - Bit depth parameter & slider
- White noise generator per voice
    - Level parameter & slider
- ADSR Envelope
    - Envelope stage parameters and sliders
    - Routed to Oscillator output volume
- LFO 1, currently acts as tremolo effect
    - Frequency parameter & slider
    - Depth parameter & slider
    - Routed to Oscillator output volume
- LFO 2, currently acts as vibrato and noise tremolo
    - Frequency parameter & slider
    - Depth parameter & slider
    - Routed to noise generator volume and wave osc tune
- Output volume parameter & slider
- MIDI control
    - Pitch
    - Note on
    - Note off
- Parameters can be read from and written to by a host DAW
- Power on/off parameter & toggle button
    - Bypasses audio and MIDI processing

## Future features
- LFO controls:
    - Wave shape
    - Phase offset?
- Modulation matrix (or similar)
    - Routing from LFOs, envelopes, and other signal sources
- Measure volume in dB
- Touch sensitivity
- Parameters/sliders
    - More appropriate value ranges
    - Skew factors