# shamsynth1
A simple synthesizer JUCE plugin

## Minimum spec
The minimal list of features - more will continue to be added

- MIDI pitch input
- 10 voices, each with:
    - White noise generator with controls for:
        - Volume ADSR envelope
            - 4 dials, 0 - 1
        - Volume envelope overall time 0.1 - 10s
        - Volume
    - 2 wave generators with controls for:
        - Wave type
            - Sine
            - Square
            - Triangle
        - Relative pitch -24 - +24
        - Volume ADSR envelope
            - 4 dials, 0 - 1
        - Volume envelope overall time 0.1 - 10s
        - Pitch ADSR envelope
            - 4 dials, 0 - 1
        - Pitch envelope depth -24 - +24
        - Pitch envelope
        - Volume
- Overall Volume control

All volume controls have the same scale, e.g. -inf - 10dB