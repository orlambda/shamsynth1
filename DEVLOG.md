# Devlog

Notes about the process of making this plugin, including challenges I've faced, what I've learned, and future aims.

Entries are in reverse chronological order.

## 2025-12-12

v.1.0.0+1

The synthesiser is currently very simple but useable - it has a single voice that outputs a combination of white noise and a pure sine wave, with note on/off and pitch control from midi input. It also has an overall volume output slider.

### Scope and process

I started this project not knowing the exact scope of it. My primary aim was just to create some sort of working synthesiser, and to add features to it over time, rather than to define a precise specification and plan the code around it from the beginning. My thinking was that it would be more useful to jump right in and start learning, and use what I've learnt for future projects that are defined more clearly from the start. Nevertheless, I have had certain features in mind that would be nice to add, ranging from fairly simple (ADSR envelopes) to complex (modularity). I think this has been a good approach as I haven't wasted time solving the wrong problems or planning features that might never be implemented in this project, I have a good starting point to continue adding features, and I've already learnt enough to improve my approach to making future plugins.

It's taken longer to get the project to this point than I anticipated (not that that is a surprise), because I've felt that certain problems I've encountered have been worth researching, or sent me on sidetracks that I think have been useful, given that this is not a commercial project, and learning is more important than delivering features as soon as possible.

I've been reading the [JUCE tutorials](https://juce.com/learn/tutorials/), and one reason I chose this project was that it would be a good way to integrate what I learn from each tutorial into a single project. Rather than copy and pasting the code and moving on, I've been reading the given code and explanations, and considering if there's anything I would do differently or would need to change, e.g. separating UI and processing code that are kept together in the [MIDI synth tutorial](https://juce.com/tutorials/tutorial_synth_using_midi_input/).

At the start of the project I defined a minimum list of features I wanted for the synth:

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

Looking back, this list was excessive for a minimal product. However, I still think each of these features will be possible to implement in a reasonable time (weeks or months).

I don't yet have a time frame for adding complex features like modularity, or more advanced DSP. Rather than aiming to make a full modular synthesiser, I may be able to start with something relatively simple, such as having one LFO which can control the frequency of another LFO, which in turn can modify a `WaveOscillator`'s frequency. If I want to make these routable, I can avoid the complexity of a typical modular UI by using dropdown menus, rather than plugging wires into sockets or similar.

Volume output is not automatable in a DAW - this will be something to add.

### Problems encountered and what I've learnt

In the [MIDI volume slider tutorial](https://juce.com/tutorials/tutorial_code_basic_plugin/), the processor's `noteOnVel` variable is updated whenever the a slider in the UI is changed. The slider value is initialised by a magic number in the editor's constructor. A magic number is not ideal, but a larger problem is that the value is uninitialised if the processor is running and the plugin's window hasn't been opened. To solve this, I initalise my output volume variable in `processor::prepareToPlay()`, and initialise the slider value from the processor's public variable. This is not an issue, as the processor owns the editor so this variable will always be initialised. (I do need to check if it's better to initialise in the processor's constructor.)

I realised that there was an issue where keeping a value, such as output volume, in a single variable that is used both by input and processing, was not ideal as this could be changed during processing. For example, if a block is processed channel by channel, rather than sample by sample, the volume could be updated while one channel is being processed and before moving to the next channel, resulting in asymmetrical output. I checked that this was true using the debugger. The simplest solution is to copy each variable to a buffer at the start of each block. Similarly, the `Voice` and `WaveOscillator` classes will need to access certain variables from the processor. I have considered various ways of approaching this. One is to pass these variables by reference which may be the simplest. I have also considered making a class that keeps two values of the same variable - one of the current state of input, and one for the value currently used for processing, with functions such as `updateValue()` to copy the input variable to the processing variable. I could use a template to allow for various variables such as floats (volume, etc.), bools (touch sensitivity, etc.) and others. An alternative would be to make a struct that contains all of the variables controllable by UI, and having two instances of this struct, for input and processing. This struct could be passed from processor to its member classes, again, by reference or by value. Testing will be required to measure performance costs of each approach.

This project seems to lend itself fairly well to object-oriented programming, with many classes sharing similar behaviours, such as processing blocks of samples and requiring the sample rate to be updated. However, I am not convinced this is the best approach rather than a convenient approach. So far, I am avoiding multiple inheritance when I can, even though I haven't measured the performance cost yet to know if this is really an issue. I am giving thought to data-oriented design, having watched [a talk by Mike Acton](https://www.youtube.com/watch?v=rX0ItVEVjHc), and to how this might apply to this project.

I don't like the chain of `if else` statements that will grow in the editor's `sliderValueChanged`. I have considered using a map to link sliders to the variable they control, so the relevant variable can be updated with a single statement. Wrapping these variables in a class using a template as described above should simplify this.

### The JUCE library

I have chosen not to use certain classes from the JUCE library, such as `juce::Synthesiser`, for multiple reasons:
- Writing them myself is a good learning exercise and forces me to think about structure and how my classes interact.
- I want to able to control precisely how my classes behave, particularly if I add complex features in the future.
- The JUCE library uses a lot of multiple inheritance, which would be good to avoid for performance (I will test this eventually).

There are disadvantages to not using the given classes:
- I am not familiarising myself with the JUCE library.
- JUCE classes are tested and should be more reliable than my own code.
- Using the JUCE library might be quicker.

I decided the pros outweigh the cons. None of the cons are major issues:
- I am still reading the JUCE library code and documentation to understand the tutorials and think of the pros and cons of how they implemented their library. I can also work on future projects that do use the JUCE library if I want experience working with those classes. 
- Learning to test my own code is a good thing, and given the nature of this project, learning is a higher priority than ensuring the code is totally bug-free.
- The project doesn't have deadlines or any time pressure. I want to be able to work quickly, but adding features quicker using a library for this project doesn't mean I will be able to work quicker in future projects, it just speeds up this one. I could set myself deadlines for the experience of working with time pressure, but I am still logging my work and improving relevant skills such as estimating how long completing tasks will take.