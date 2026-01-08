# NOTES

## Adding a new parameter
(this won't all be necessary when I refactor editor constructor & resized())
for a parameter named MyParam:

processor h: private:
    std::atomic<float>* MyParam = nullptr;

processor cpp: constructor parameters initialiser:
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("MyParamID", 1), "MyParam", 0.0f, 1.0f, 1.0f)
processor cpp: constructor:
    MyParam = MyParameters.getRawParameterValue("MyParamID");

editor h: private:
    juce::Label MyParamLabel;
    juce::Slider MyParamSlider;
    std::unique_ptr<SliderAttachment> MyParamAttachment;

editor cpp: constructor:
    MyParamLabel.setText("MyParam", juce::dontSendNotification);
    addAndMakeVisible(MyParamLabel);
    
    MyParamAttachment.reset(new SliderAttachment (valueTreeState, "MyParamID", MyParamSlider));
    
    MyParamSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    MyParamSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    MyParamSlider.setPopupDisplayEnabled(true, false, this);
    MyParamSlider.setTextValueSuffix(" MyParam");
    addAndMakeVisible(&MyParamSlider);

editor cpp: resized():
    MyParamSlider.setBounds(40, 40, 20, 150);
    MyParamLabel.setBounds(20, 180, 200, 50);

processor cpp: processBlock():
    add parameter buffer and read from atomic

use the parameter for something..