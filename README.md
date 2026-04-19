# shamsynth1 v1.0.41

## IMPORTANT SAFETY WARNING
This audio plugin is in early development and may contain errors which result in extremely loud and unexpected sounds. To protect your hearing, please use at a low volume and do not listen on headphones.

## Overview
A polyphonic synthesiser plugin with a variety of waveforms, effects, and modulation capabilities. Made with C++ and JUCE. Full features are listed below.

## Getting started
The plugin is available on [GitHub](https://github.com/orlambda/shamsynth1) or [itch.io](https://orlandoo.itch.io/shamsynth1). The most up-to-date version will always be on GitHub but will need you to compile it (see below), whereas the files on itch may be a few versions behind but are ready to use.

### Compilation
To compile this plugin you will need [JUCE](https://juce.com/get-juce/), an IDE (such as Xcode on macOS or Visual Studio on Windows), and a compiler that supports C++20. Clone the repo, open the `.jucer` file in the Projucer, save and open in your IDE, build, and locate the file. Mine build to `shamsynth1/Builds/MacOSX/build/Debug` as well as to `/Library/Audio/Plug-Ins/Components` - you can change the build locations. If you have never compiled anything, this process can range from simple to difficult. In the simplest case a beginner can do this, but if you have issues such as having to change compiler you may need to ask someone to help you or to download the plugin from itch.

### Installation
Once you have downloaded or built the plugin, move it to the relevant folder. E.g. for AU plugins on macOS, the folder is `/Library/Audio/Plug-Ins/Components`. (The AU plugin is the file whose name ends with `.component`.) The folder location is different on Windows and for VST3 - check the location for your system. You should now be able to open the plugin in a DAW or other host, such as Logic Pro or Reaper. You may need to scan for new plugins. JUCE also provide an audio plugin host for debugging if you don't want to install a full DAW - see [https://juce.com/tutorials/tutorial_create_projucer_basic_plugin/]() and scroll to 'Set up plug-in debugging (optional)' for instructions on how to install that. You don't need to set the plugin host as an executable in your IDE unless you are planning on debugging.

### Usage

#### Using multiple versions
Installing a new version of the plugin will likely replace the previous version (unless you are keeping it in a custom location etc.). This can introduce compatibility issues as features are added, value ranges may change, parameters may be removed, etc. You can avoid this by reinstalling the correct version of the plugin before opening any given DAW project.

If you plan on using saving a project that uses the plugin, keep a note of which version you used, so that if you install a newer version in the future, you can revert to the correct version for that project. You could also keep the DAW project and a copy of the plugin in a folder together. If you are using multiple versions in multiple projects, it would be worth keeping a copy of each version you've used together in a folder (separate from wherever your OS keeps plugins). You can also build any version using the git commit history. From v1.0.12 onwards, the version number is included in the corresponding commit message.

When the plugin reaches a more advanced state, likely from v1.1.0 or v2.0.0 onwards, minor updates (e.g. v1.1.0 to v1.2.0) will be backward compatible while major updates (e.g. v1.1.0 to v2.0.0) will not.

#### Monitoring
This audio plugin is in early development and may contain errors which result in extremely loud and unexpected sounds. To protect your hearing, please use at a low volume and do not listen on headphones. While I test to avoid this, and am unaware of this happening in any committed versions, I am a solo developer and mistakes do happen, and it is not worth the risk of damaging your hearing just because I have missed an edge case or forgotten to clear an audio buffer somewhere. 

Of course rendered audio files are safe to listen to, so if you want to use the plugin in a real project, you can render the plugin's audio in a separate project then import that audio file into your main project. You could also bounce in place, use a Reaper subproject, or similar. This will then be safe to monitor with headphones, as long as you are using an audio file, not the output of the plugin itself.

### Platforms
I am using macOS 15 and haven't tested the plugin on other platforms. I test both AU and VST3 builds. I hope to build to CLAP when JUCE 9 is released. The standalone version is buildable and seems to work but is not tested and does not take MIDI input, only input from the keyboard component in the plugin windows.

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
- Wavefolder per voice
    - Threshold parameter & slider
    - Scaling parameter & slider
- White noise generator per voice
    - Level parameter & slider
- Modulation sources (these routings are temporarily hard-coded)
    - ADSR Envelope
        - Envelope stage parameters and sliders
        - Routed to oscillator output volume
    - LFO 1 global, currently acts as tremolo effect
        - Frequency parameter & slider
        - Depth parameter & slider
        - Routed to output volume
    - LFO 2 global, currently acts as oscillator vibrato and noise tremolo
        - Frequency parameter & slider
        - Depth parameter & slider
        - Routed to noise generator volume
- Modulation Matrix
    - Allows ADSR Envelope to be routed to Oscillator Tune with variable scaling
- Output volume parameter & slider
- MIDI control
    - Pitch
    - Note on
    - Note off
- Parameters can be read from and written to by a host DAW
- Power on/off parameter & toggle button
    - Bypasses audio and MIDI processing

## Future features
- Oscillators
    - Multiple Oscillators
    - Phase offset parameter & slider
    - Waveshaping parameter & slider allowing blending waveforms with a single slider
- LFOs
    - Global and per-voice
    - Wave shape parameter & slider
    - Phase offset parameter & slider
- Modulation matrix
    - Routing from signal sources (oscillators, LFOs, envelopes, key velocity) to parameters
    - Scaling parameters and sliders of range [-1.0,1.0]
    - Global and per-voice signal sources routable to global and per-voice parameters
- Touch sensitivity
    - Optional
- Parameters/sliders
    - More appropriate value ranges
    - Skew factors
    - Change appearance to dial