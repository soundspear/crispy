/*
  ==============================================================================

    MoreControlPanel.h
    Created: 28 Mar 2020 8:45:31pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Constants.h"

//==============================================================================
/*
*/
class MoreControlPanel    : public Component
{
public:
    MoreControlPanel(AudioProcessorValueTreeState& params) : parameters(params)
    {
        initSlider(autoGainAmountSlider, autoGainAmountSliderAttachment, Constants::ID_AUTO_GAIN_AMOUNT);
        initSlider(oversamplingSlider, oversamplingSliderAttachment, Constants::ID_OVERSAMPLING);
        initSlider(dryGainSlider, dryGainSliderAttachment, Constants::ID_DRY_GAIN);
        dryGainSlider.setSliderStyle(Slider::LinearVertical);
        initSlider(wetGainSlider, wetGainSliderAttachment, Constants::ID_WET_GAIN);
        wetGainSlider.setSliderStyle(Slider::LinearVertical);
        
        initLabel(autoGainLabel, &autoGainAmountSlider, "Auto-Gain");
        initLabel(oversamplingLabel, &oversamplingSlider, "Oversampling");
        initLabel(dryLabel, &dryGainSlider, "Dry");
        initLabel(wetLabel, &wetGainSlider, "Wet");
    }

    ~MoreControlPanel()
    {
        
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colour::fromHSV(0.0f, 0.0f, 0.4f, 0xff));
    }

    void resized() override
    {
        int padding = 5;
        int rotaryWidth = getWidth() / 4;
        int sliderWidth = 30;
        int centerGap = 60;
        
        Rectangle<int> bounds = getLocalBounds();
        bounds.reduce(padding, padding);
        
        bounds.removeFromTop(50);
        
        autoGainAmountSlider.setBounds(bounds.removeFromLeft(rotaryWidth));
        oversamplingSlider.setBounds(bounds.removeFromRight(rotaryWidth));
        
        int excess = bounds.getWidth() - 2*sliderWidth - 2*padding - centerGap;
        bounds.reduce(excess/2, 0);
        
        dryGainSlider.setBounds(bounds.removeFromLeft(sliderWidth));
        wetGainSlider.setBounds(bounds.removeFromRight(sliderWidth));
    }

private:
    AudioProcessorValueTreeState& parameters;
    
    Slider autoGainAmountSlider,
        oversamplingSlider,
        dryGainSlider,
        wetGainSlider;
    
    Label autoGainLabel, oversamplingLabel, dryLabel, wetLabel;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    
    std::unique_ptr<SliderAttachment> autoGainAmountSliderAttachment,
        oversamplingSliderAttachment,
        dryGainSliderAttachment,
        wetGainSliderAttachment;
    
    void initSlider(Slider& slider, std::unique_ptr<SliderAttachment>& attachment, String paramId){
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        slider.setPopupDisplayEnabled(true, true, this);
        slider.setPopupMenuEnabled(true);
        attachment.reset(new SliderAttachment(parameters, paramId, slider));
    }
    
    void initLabel(Label& label, Component* owner, String text){
        label.setText(text, dontSendNotification);
        label.attachToComponent(owner, false);
        label.setJustificationType(Justification::centred);
        label.setFont(Font(24.0f));
        addAndMakeVisible(label);
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoreControlPanel)
};