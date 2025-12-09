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

all a noteOne MIDI Message does is reset the current angle and adjust the angleDelta
    (is resetting the current angle actually necessary? this starts the wave with a 0.0 sample which is good if the voice was silent)

so when does the angleDelta next get checked?

at the start of SineWaveVoice.renderNextBlock()
called by Synthesiser::renderVoices

TODO:

read:
Synthesiser::renderNextBlock, handle midi event etc
add breakpoint at startNote() and check call stack

see how MIDI events are handled
compare with 
processBlock() in [https://juce.com/tutorials/tutorial_code_basic_plugin/]
