# shamsynth1 v1.0.12
A synthesiser plugin made with C++ and JUCE.

To build this plugin, use [JUCE](https://juce.com/get-juce/). Clone the repo, open the .jucer file, save and open in your IDE, and build.

I am using macOS 15 and haven't tested the plugin on other platforms. I test both AU and VST3 builds. I hope to build to CLAP when JUCE 9 is released.

## Current features
- Sine wave oscillator
    - Volume parameter
    - Tune parameter
- Noise generator
    - Volume parameter
- Polyphony
- Bitcrusher
    - Bit depth parameter
- MIDI control
    - Pitch
    - Note on
    - Note off
- LFO 1, currently acts as tremolo effect
    - Frequency parameter
    - Depth parameter
    - Routed to output volume
- LFO 2, currently acts as vibrato and noise tremolo
    - Frequency parameter
    - Depth parameter
    - Routed to noise generator volume and wave osc tune
- Output volume parameter

## Future features
- Enable DAW automation
- Multiple wave oscillators (2?) with controls:
    - Wave type
        - Sine
        - Square
        - Triangle
    - Wave blend?
    - Relative pitch -24 - +24
    - Volume ADSR envelope
        - 4 dials, 0 - 1
    - Volume envelope overall time 0.1 - 10s
    - Pitch ADSR envelope
        - 4 dials, 0 - 1
    - Pitch envelope depth -24 - +24
    - Pitch envelope
    - Volume
- White noise generator controls:
    - Volume ADSR envelope
        - 4 dials, 0 - 1
    - Volume envelope overall time 0.1 - 10s
    - Volume
- LFO controls:
    - Frequency
    - Depth
    - Wave shape
    - Phase offset?
- Modulation matrix (or similar)
    - Routing from LFOs and other sources
- Measure volume in dB