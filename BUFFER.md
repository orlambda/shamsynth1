find + replace both names 

processor h: private:
    std::atomic<float>* osc1SquareLevelParameter = nullptr;

processor cpp: constructor parameters initialiser:
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("osc1SquareLevel", 1), "Osc 1 Square Level", 0.0f, 1.0f, 1.0f)
processor cpp: constructor:
    osc1SquareLevelParameter = parameters.getRawParameterValue("osc1SquareLevel");

editor h: private:
    juce::Label osc1SquareLevelLabel;
    juce::Slider osc1SquareLevelSlider;
    std::unique_ptr<SliderAttachment> osc1SquareLevelAttachment;

editor cpp: constructor:
    osc1SquareLevelLabel.setText("Osc 1 Square Level", juce::dontSendNotification);
    addAndMakeVisible(osc1SquareLevelLabel);
    osc1SquareLevelAttachment.reset(new SliderAttachment (valueTreeState, "osc1SquareLevel", osc1SquareLevelSlider));
    osc1SquareLevelSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1SquareLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1SquareLevelSlider.setPopupDisplayEnabled(true, false, this);
    osc1SquareLevelSlider.setTextValueSuffix(" semitones");
    addAndMakeVisible(&osc1SquareLevelSlider);

editor cpp: resized():
    osc1SquareLevelSlider.setBounds(40, 40, 20, 150);
    osc1SquareLevelLabel.setBounds(20, 180, 200, 50);

processor cpp: processBlock():
    add parameter buffer and read from atomic

use the parameter for something..