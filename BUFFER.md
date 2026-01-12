
processor h: private:
    std::atomic<float>* osc1Tune = nullptr;

processor cpp: constructor parameters initialiser:
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("osc1TuneID", 1), "Osc 1 Tune", 0.0f, 1.0f, 1.0f)
processor cpp: constructor:
    osc1Tune = parameters.getRawParameterValue("osc1TuneID");

editor h: private:
    juce::Label osc1TuneLabel;
    juce::Slider osc1TuneSlider;
    std::unique_ptr<SliderAttachment> osc1TuneAttachment;

editor cpp: constructor:
    osc1TuneLabel.setText("Osc 1 Tune", juce::dontSendNotification);
    addAndMakeVisible(osc1TuneLabel);
    osc1TuneAttachment.reset(new SliderAttachment (valueTreeState, "osc1TuneID", osc1TuneSlider));
    osc1TuneSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1TuneSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1TuneSlider.setPopupDisplayEnabled(true, false, this);
    osc1TuneSlider.setTextValueSuffix(" semitones");
    addAndMakeVisible(&osc1TuneSlider);

editor cpp: resized():
    osc1TuneSlider.setBounds(40, 40, 20, 150);
    osc1TuneLabel.setBounds(20, 180, 200, 50);

processor cpp: processBlock():
    add parameter buffer and read from atomic

use the parameter for something..