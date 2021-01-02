/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StkLite-4.6.1/Delay.h"
#include "Mu45FilterCalc/Mu45FilterCalc.h"
#include "StkLite-4.6.1/BiQuad.h"

#define MAXDELAYMSEC 10000.0
//==============================================================================
/**
*/
class AndrewHp03delaySwitchAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    AndrewHp03delaySwitchAudioProcessor();
    ~AndrewHp03delaySwitchAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //Functions
    //==============================================================================
    void calcAlgorithmsParams();
    int calcMsecToSamps(float mSec);
    //void calcFilterCoeffs();

    //User
    //==============================================================================
    juce::AudioParameterFloat* mDelayLMsecParam;
    juce::AudioParameterFloat* mDelayRMsecParam;

    juce::AudioParameterFloat* mWetDryMixParam;
    juce::AudioParameterFloat* mFeedbackDbParam;
    juce::AudioParameterFloat* mBothMixParam;

    juce::AudioParameterBool* mOffParam;
    juce::AudioParameterBool* mTappedParam;
    juce::AudioParameterBool* mPingPongParam;
    juce::AudioParameterBool* mBothParam;

    juce::AudioParameterBool* mHighOnParam;
    juce::AudioParameterBool* mMidOnParam;
    juce::AudioParameterBool* mLowOnParam;

    juce::AudioParameterBool* mSyncParam;

    juce::AudioParameterFloat* mFilterFcParamHigh;
    juce::AudioParameterFloat* mFilterFcParamMid;
    juce::AudioParameterFloat* mFilterFcParamLow;

    //Algorithm
    //==============================================================================
    float mFeedbackGainLin;

    float mWetGain;
    float mDryGain;

    float mPPGain;
    float mTGain;

    float tapOffsetL;
    float tapOffsetR;

    bool mOff;
    bool mTapped;
    bool mPingPong;
    bool mBoth;

    bool mSync;

    bool mHighOn;
    bool mMidOn;
    bool mLowOn;

    //Member Objects- delay objects, filters, and sampling rate
    //==============================================================================
    stk::Delay mDelay1L;
    stk::Delay mDelay1R;

    stk::BiQuad mFilterLHigh;
    stk::BiQuad mFilterRHigh;

    stk::BiQuad mFilterLMid;
    stk::BiQuad mFilterRMid;

    stk::BiQuad mFilterLLow;
    stk::BiQuad mFilterRLow;
    float mFs;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AndrewHp03delaySwitchAudioProcessor)
};
