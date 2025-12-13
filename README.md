# shamsynth1
A synthesiser plugin made with C++ and JUCE.

To build this plugin, use JUCE, which you can get [here](https://juce.com/get-juce/).

I am using macOS 15 and haven't tested the plugin on other platforms.

## Current features
- Voice
- Sine wave oscillator
- Noise generator
- MIDI control:
    - Pitch
    - Note on
    - Note off
- Output volume slider

## Future features
- Enable DAW automation
- Polyphony
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
- LFO with controls:
    - Frequency
    - Depth
    - Phase offset?
    - Routing (what it affects)
- Measure volume in dB