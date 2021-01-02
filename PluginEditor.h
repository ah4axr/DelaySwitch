/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AndrewHp03delaySwitchAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener, public juce::Button::Listener,
    public juce::Timer
{
public:
    AndrewHp03delaySwitchAudioProcessorEditor (AndrewHp03delaySwitchAudioProcessor&);
    ~AndrewHp03delaySwitchAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;
    void timerCallback() override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AndrewHp03delaySwitchAudioProcessor& audioProcessor;

    //Sliders
    juce::Slider mDelayLMsecSlider;
    juce::Slider mDelayRMsecSlider;

    juce::Slider mWetDryMixSlider;
    juce::Slider mFeedbackDbSlider;

    juce::Slider mFilterFcHighSlider;
    juce::Slider mFilterFcMidSlider;
    juce::Slider mFilterFcLowSlider;

    //Buttons
    juce::ToggleButton mOffButton;
    juce::ToggleButton mTappedButton;
    juce::ToggleButton mPingPongButton;
    juce::ToggleButton mBothButton;

    juce::ToggleButton mSyncButton;

    juce::ToggleButton mHighButton;
    juce::ToggleButton mMidButton;
    juce::ToggleButton mLowButton;

    juce::Label delayLLabel;
    juce::Label delayRLabel;
    juce::Label feedbackLabel;

    juce::Label wetDryLabel;

    juce::Label highFcLabel;
    juce::Label midFcLabel;
    juce::Label lowFcLabel;

    juce::Label mHighButtonLabel;
    juce::Label mMidButtonLabel;
    juce::Label mLowButtonLabel;

    juce::Label mOffButtonLabel;
    juce::Label mTappedButtonLabel;
    juce::Label mPingPongButtonLabel;
    juce::Label mBothButtonLabel;

    juce::Label mSyncButtonLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AndrewHp03delaySwitchAudioProcessorEditor)
};
