# MIDI Tutorial Notes
[https://juce.com/tutorials/tutorial_synth_using_midi_input/]

Application : JUCEApplication
    std::unique_ptr<MainWindow> mainWindow, initialised with std::make_unique<MainContentComponent>()

MainContentComponent :  public juce::AudioAppComponent,
                        private juce::Timer
    juce::MidiKeyboardState keyboardState;
    SynthAudioSource synthAudioSource;

    functions passed on to synthAudioSource

SynthAudioSource : public juce::AudioSource
    juce::MidiKeyboardState& keyboardState;
    juce::Synthesiser synth;

    constructor
        initialises keyboardState (reference)
        adds 4 voices to synth
        adds 1 sine sound to synth

    getNextAudioBlock()
        processes MIDI buffer from keyboard state

        calls synth.renderNextBlock()

SineWaveVoice : public juce::SynthesiserVoice
    startNote() resets currentAngle, velocity, and angleDelta (doesn't store frequency) override

    stopNote() sets tailOff to 1.0 or resets angleDelta and calls clearCurrentNote() (from JUCE SynthesiserVoice) override

takeaway:
synth processes MIDI by calling SineWaveVoice.renderNextBlock(), SineWaveVoice.startNote(), etc

both external MIDI and MIDI from keyboardComponent both get processed into the incomingMIDI buffer

TODO:

read:
Synthesiser::renderNextBlock, handle midi event etc
add breakpoint at startNote() and check call stack

