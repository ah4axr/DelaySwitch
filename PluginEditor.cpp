/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;
//==============================================================================
AndrewHp03delaySwitchAudioProcessorEditor::AndrewHp03delaySwitchAudioProcessorEditor (AndrewHp03delaySwitchAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(500, 500);

    auto& params = processor.getParameters();

    ///////////////////////////////////////////////////////////////////////////////////////
    AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(0);
    mDelayLMsecSlider.setBounds(10, 150, 100, 100);
    mDelayLMsecSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDelayLMsecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    mDelayLMsecSlider.setRange(audioParam->range.start, audioParam->range.end);
    mDelayLMsecSlider.setValue(*audioParam);
    mDelayLMsecSlider.setTextValueSuffix(" ms");
    mDelayLMsecSlider.addListener(this);
    addAndMakeVisible(mDelayLMsecSlider);
    addAndMakeVisible(delayLLabel);
    delayLLabel.setText("Delay L", juce::dontSendNotification);
    delayLLabel.setJustificationType(juce::Justification::centred);
    delayLLabel.attachToComponent(&mDelayLMsecSlider, false);

    audioParam = (AudioParameterFloat*)params.getUnchecked(1);
    mDelayRMsecSlider.setBounds(95, 150, 100, 100);
    mDelayRMsecSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDelayRMsecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    mDelayRMsecSlider.setRange(audioParam->range.start, audioParam->range.end);
    mDelayRMsecSlider.setValue(*audioParam);
    mDelayRMsecSlider.setTextValueSuffix(" ms");
    mDelayRMsecSlider.addListener(this);
    addAndMakeVisible(mDelayRMsecSlider);
    addAndMakeVisible(delayRLabel);
    delayRLabel.setText("Delay R", juce::dontSendNotification);
    delayRLabel.setJustificationType(juce::Justification::centred);
    delayRLabel.attachToComponent(&mDelayRMsecSlider, false);

    audioParam = (AudioParameterFloat*)params.getUnchecked(2);
    mWetDryMixSlider.setBounds(400, 150, 50, 255);
    mWetDryMixSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    mWetDryMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    mWetDryMixSlider.setRange(audioParam->range.start, audioParam->range.end);
    mWetDryMixSlider.setValue(*audioParam);
    mWetDryMixSlider.setTextValueSuffix("%");
    mWetDryMixSlider.addListener(this);
    addAndMakeVisible(mWetDryMixSlider);
    addAndMakeVisible(wetDryLabel);
    wetDryLabel.setText("Mix", juce::dontSendNotification);
    wetDryLabel.setJustificationType(juce::Justification::centred);
    wetDryLabel.attachToComponent(&mWetDryMixSlider, false);

    audioParam = (AudioParameterFloat*)params.getUnchecked(3);
    mFeedbackDbSlider.setBounds(50, 325, 100, 125);
    mFeedbackDbSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackDbSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    mFeedbackDbSlider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackDbSlider.setValue(*audioParam);
    mFeedbackDbSlider.addListener(this);
    addAndMakeVisible(mFeedbackDbSlider);
    addAndMakeVisible(feedbackLabel);
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centred);
    feedbackLabel.attachToComponent(&mFeedbackDbSlider, false);

    audioParam = (AudioParameterFloat*)params.getUnchecked(8);
    mFilterFcHighSlider.setBounds(210, 200, 125, 50);
    mFilterFcHighSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mFilterFcHighSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    mFilterFcHighSlider.setRange(audioParam->range.start, audioParam->range.end);
    mFilterFcHighSlider.setValue(*audioParam);
    mFilterFcHighSlider.setTextValueSuffix(" Hz");
    mFilterFcHighSlider.addListener(this);
    addAndMakeVisible(mFilterFcHighSlider);
    addAndMakeVisible(highFcLabel);
    highFcLabel.setText("High Frequency", juce::dontSendNotification);
    highFcLabel.setJustificationType(juce::Justification::centred);
    highFcLabel.attachToComponent(&mFilterFcHighSlider, false);

    audioParam = (AudioParameterFloat*)params.getUnchecked(9);
    mFilterFcMidSlider.setBounds(210, 302, 125, 50);
    mFilterFcMidSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mFilterFcMidSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    mFilterFcMidSlider.setRange(audioParam->range.start, audioParam->range.end);
    mFilterFcMidSlider.setValue(*audioParam);
    mFilterFcMidSlider.setTextValueSuffix(" Hz");
    mFilterFcMidSlider.addListener(this);
    addAndMakeVisible(mFilterFcMidSlider);
    addAndMakeVisible(midFcLabel);
    midFcLabel.setText("Mid Frequency", juce::dontSendNotification);
    midFcLabel.setJustificationType(juce::Justification::centred);
    midFcLabel.attachToComponent(&mFilterFcMidSlider, false);

    audioParam = (AudioParameterFloat*)params.getUnchecked(10);
    mFilterFcLowSlider.setBounds(210, 404, 125, 50);
    mFilterFcLowSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mFilterFcLowSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    mFilterFcLowSlider.setRange(audioParam->range.start, audioParam->range.end);
    mFilterFcLowSlider.setValue(*audioParam);
    mFilterFcLowSlider.setTextValueSuffix(" Hz");
    mFilterFcLowSlider.addListener(this);
    addAndMakeVisible(mFilterFcLowSlider);
    addAndMakeVisible(lowFcLabel);
    lowFcLabel.setText("Low Frequency", juce::dontSendNotification);
    lowFcLabel.setJustificationType(juce::Justification::centred);
    lowFcLabel.attachToComponent(&mFilterFcLowSlider, false);

    /////////////////////////////////////////////////////////////////////////////////
    audioParam = (AudioParameterFloat*)params.getUnchecked(4);
    mOffButton.setBounds(50, 50, 50, 50);
    mOffButton.setToggleState(*audioParam, false);
    mOffButton.addListener(this);
    mOffButton.setRadioGroupId(1000);
    addAndMakeVisible(mOffButton);
    addAndMakeVisible(mOffButtonLabel);
    mOffButtonLabel.setText("OFF", juce::dontSendNotification);
    mOffButtonLabel.setJustificationType(juce::Justification::centred);
    mOffButtonLabel.attachToComponent(&mOffButton, true);

    audioParam = (AudioParameterFloat*)params.getUnchecked(5);
    mTappedButton.setBounds(175, 50, 50, 50);
    mTappedButton.setToggleState(*audioParam, false);
    mTappedButton.addListener(this);
    mTappedButton.setRadioGroupId(1000);
    addAndMakeVisible(mTappedButton);
    addAndMakeVisible(mTappedButtonLabel);
    mTappedButtonLabel.setText("Tapped", juce::dontSendNotification);
    mTappedButtonLabel.setJustificationType(juce::Justification::centred);
    mTappedButtonLabel.attachToComponent(&mTappedButton, true);

    audioParam = (AudioParameterFloat*)params.getUnchecked(6);
    mPingPongButton.setBounds(300, 50, 50, 50);
    mPingPongButton.setToggleState(*audioParam, false);
    mPingPongButton.addListener(this);
    mPingPongButton.setRadioGroupId(1000);
    addAndMakeVisible(mPingPongButton);
    addAndMakeVisible(mPingPongButtonLabel);
    mPingPongButtonLabel.setText("Ping-Pong", juce::dontSendNotification);
    mPingPongButtonLabel.setJustificationType(juce::Justification::centred);
    mPingPongButtonLabel.attachToComponent(&mPingPongButton, true);

    audioParam = (AudioParameterFloat*)params.getUnchecked(7);
    mBothButton.setBounds(425, 50, 50, 50);
    mBothButton.setToggleState(*audioParam, false);
    mBothButton.addListener(this);
    mBothButton.setRadioGroupId(1000);
    addAndMakeVisible(mBothButton);
    addAndMakeVisible(mBothButtonLabel);
    mBothButtonLabel.setText("Both", juce::dontSendNotification);
    mBothButtonLabel.setJustificationType(juce::Justification::centred);
    mBothButtonLabel.attachToComponent(&mBothButton, true);

    audioParam = (AudioParameterFloat*)params.getUnchecked(11);
    mHighButton.setBounds(285, 150, 50, 25);
    mHighButton.setToggleState(*audioParam, false);
    mHighButton.addListener(this);
    addAndMakeVisible(mHighButton);
    addAndMakeVisible(mHighButtonLabel);
    mHighButtonLabel.setText("On/Off", juce::dontSendNotification);
    mHighButtonLabel.setJustificationType(juce::Justification::centred);
    mHighButtonLabel.attachToComponent(&mHighButton, true);

    audioParam = (AudioParameterFloat*)params.getUnchecked(12);
    mMidButton.setBounds(285, 245, 50, 50);
    mMidButton.setToggleState(*audioParam, false);
    mMidButton.addListener(this);
    addAndMakeVisible(mMidButton);
    addAndMakeVisible(mMidButtonLabel);
    mMidButtonLabel.setText("On/Off", juce::dontSendNotification);
    mMidButtonLabel.setJustificationType(juce::Justification::centred);
    mMidButtonLabel.attachToComponent(&mMidButton, true);

    audioParam = (AudioParameterFloat*)params.getUnchecked(13);
    mLowButton.setBounds(285, 347, 50, 50);
    mLowButton.setToggleState(*audioParam, false);
    mLowButton.addListener(this);
    addAndMakeVisible(mLowButton);
    addAndMakeVisible(mLowButtonLabel);
    mLowButtonLabel.setText("On/Off", juce::dontSendNotification);
    mLowButtonLabel.setJustificationType(juce::Justification::centred);
    mLowButtonLabel.attachToComponent(&mLowButton, true);

    audioParam = (AudioParameterFloat*)params.getUnchecked(14);
    mSyncButton.setBounds(100, 250, 50, 50);
    mSyncButton.setToggleState(*audioParam, false);
    mSyncButton.addListener(this);
    addAndMakeVisible(mSyncButton);
    addAndMakeVisible(mSyncButtonLabel);
    mSyncButtonLabel.setText("Sync", juce::dontSendNotification);
    mSyncButtonLabel.setJustificationType(juce::Justification::centred);
    mSyncButtonLabel.attachToComponent(&mSyncButton, true);
}

AndrewHp03delaySwitchAudioProcessorEditor::~AndrewHp03delaySwitchAudioProcessorEditor()
{
}

//==============================================================================
void AndrewHp03delaySwitchAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Delay Switch", getLocalBounds(), juce::Justification::centredTop, 1);
}

void AndrewHp03delaySwitchAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
void AndrewHp03delaySwitchAudioProcessorEditor::sliderValueChanged(Slider* slider)
{

    auto& params = processor.getParameters();
    if (slider == &mDelayLMsecSlider)
    {
        AudioParameterFloat* audioParamL = (AudioParameterFloat*)params.getUnchecked(0);
        *audioParamL = mDelayLMsecSlider.getValue();

        //sync button on, change one slider changes both
        if (mSyncButton.getToggleState() == true)
        {
            AudioParameterFloat* audioParamR = (AudioParameterFloat*)params.getUnchecked(1);
            *audioParamR = mDelayLMsecSlider.getValue();
        }
    }
    else if (slider == &mDelayRMsecSlider)
    {
        AudioParameterFloat* audioParamR = (AudioParameterFloat*)params.getUnchecked(1);
        *audioParamR = mDelayRMsecSlider.getValue();

        //sync button on, change one slider changes both
        if (mSyncButton.getToggleState() == true)
        {
            AudioParameterFloat* audioParamL = (AudioParameterFloat*)params.getUnchecked(0);
            *audioParamL = mDelayRMsecSlider.getValue();
        }
    }
    else if (slider == &mWetDryMixSlider)
    {
        AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(2);
        *audioParam = mWetDryMixSlider.getValue();
    }
    else if (slider == &mFeedbackDbSlider)
    {
        AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(3);
        *audioParam = mFeedbackDbSlider.getValue();
    }
    else if (slider == &mFilterFcHighSlider)
    {
        AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(8);
        *audioParam = mFilterFcHighSlider.getValue();
    }
    else if (slider == &mFilterFcMidSlider)
    {
        AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(9);
        *audioParam = mFilterFcMidSlider.getValue();
    }
    else if (slider == &mFilterFcLowSlider)
    {
        AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(10);
        *audioParam = mFilterFcLowSlider.getValue();
    }
}

void AndrewHp03delaySwitchAudioProcessorEditor::buttonClicked(Button* button)
{
    //auto state = button->getToggleState();
    //juce::String stateString = state ? "ON" : "OFF";
    auto& params = processor.getParameters();
    if (button == &mOffButton)
    {
        AudioParameterBool* audioParam = (AudioParameterBool*)params.getUnchecked(4);
        *audioParam = mOffButton.getToggleState();
    }
    else if (button == &mTappedButton)
    {
        AudioParameterBool* audioParam = (AudioParameterBool*)params.getUnchecked(5);
        *audioParam = mTappedButton.getToggleState();
    }
    else if (button == &mPingPongButton)
    {
        AudioParameterBool* audioParam = (AudioParameterBool*)params.getUnchecked(6);
        *audioParam = mPingPongButton.getToggleState();
    }
    else if (button == &mBothButton)
    {
        AudioParameterBool* audioParam = (AudioParameterBool*)params.getUnchecked(7);
        *audioParam = mBothButton.getToggleState();
    }
    else if (button == &mHighButton)
    {
        AudioParameterBool* audioParam = (AudioParameterBool*)params.getUnchecked(11);
        *audioParam = mHighButton.getToggleState();
    }
    else if (button == &mMidButton)
    {
        AudioParameterBool* audioParam = (AudioParameterBool*)params.getUnchecked(12);
        *audioParam = mMidButton.getToggleState();
    }
    else if (button == &mLowButton)
    {
        AudioParameterBool* audioParam = (AudioParameterBool*)params.getUnchecked(13);
        *audioParam = mLowButton.getToggleState();
    }
    else if (button == &mSyncButton)
    {
        AudioParameterBool* audioParam = (AudioParameterBool*)params.getUnchecked(14);
        *audioParam = mSyncButton.getToggleState();
        if (*audioParam == true)
        {
            //click button, both delayL and R get set to delayL time
            AudioParameterFloat* audioParamR = (AudioParameterFloat*)params.getUnchecked(1);
            *audioParamR = mDelayLMsecSlider.getValue();
        }
    }
}

void AndrewHp03delaySwitchAudioProcessorEditor::timerCallback()
{
    auto& params = processor.getParameters();
    //Update the value of each slider to match the value in the Processor    
    AudioParameterFloat* delayLTime = (AudioParameterFloat*)params.getUnchecked(0);
    mDelayLMsecSlider.setValue(delayLTime->get(), dontSendNotification);
    AudioParameterFloat* delayRTime = (AudioParameterFloat*)params.getUnchecked(1);
    mDelayRMsecSlider.setValue(delayRTime->get(), dontSendNotification);
    AudioParameterFloat* wetDry = (AudioParameterFloat*)params.getUnchecked(2);
    mWetDryMixSlider.setValue(wetDry->get(), dontSendNotification);
    AudioParameterFloat* feedback = (AudioParameterFloat*)params.getUnchecked(3);
    mFeedbackDbSlider.setValue(feedback->get(), dontSendNotification);

    AudioParameterFloat* high = (AudioParameterFloat*)params.getUnchecked(8);
    mFilterFcHighSlider.setValue(high->get(), dontSendNotification);
    AudioParameterFloat* mid = (AudioParameterFloat*)params.getUnchecked(9);
    mFilterFcMidSlider.setValue(mid->get(), dontSendNotification);
    AudioParameterFloat* low = (AudioParameterFloat*)params.getUnchecked(10);
    mFilterFcLowSlider.setValue(low->get(), dontSendNotification);

    AudioParameterBool* off = (AudioParameterBool*)params.getUnchecked(4);
    mOffButton.setToggleState(off->get(), dontSendNotification);
    AudioParameterBool* tapped = (AudioParameterBool*)params.getUnchecked(5);
    mTappedButton.setToggleState(tapped->get(), dontSendNotification);
    AudioParameterBool* pingPong = (AudioParameterBool*)params.getUnchecked(6);
    mPingPongButton.setToggleState(pingPong->get(), dontSendNotification);
    AudioParameterBool* both = (AudioParameterBool*)params.getUnchecked(7);
    mBothButton.setToggleState(both->get(), dontSendNotification);

    AudioParameterBool* highOn = (AudioParameterBool*)params.getUnchecked(11);
    mHighButton.setToggleState(highOn->get(), dontSendNotification);
    AudioParameterBool* midOn = (AudioParameterBool*)params.getUnchecked(12);
    mMidButton.setToggleState(midOn->get(), dontSendNotification);
    AudioParameterBool* lowOn = (AudioParameterBool*)params.getUnchecked(13);
    mLowButton.setToggleState(lowOn->get(), dontSendNotification);

    AudioParameterBool* syncOn = (AudioParameterBool*)params.getUnchecked(14);
    mSyncButton.setToggleState(syncOn->get(), dontSendNotification);
}
