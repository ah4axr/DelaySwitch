/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AndrewHp03delaySwitchAudioProcessor::AndrewHp03delaySwitchAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(mDelayLMsecParam = new juce::AudioParameterFloat("Delay Left in M Sec",
        "Delay L Time",
        50.0f,
        4000.0f,
        1000.0f
    ));
    addParameter(mDelayRMsecParam = new juce::AudioParameterFloat("Delay Right in M Sec",
        "Delay R Time",
        50.0f,
        4000.0f,
        1000.0f
    ));
    addParameter(mWetDryMixParam = new juce::AudioParameterFloat("Wet/Dry Mix",
        "Wet/Dry Mix",
        0.0f,
        100.0f,
        50.0f
    ));
    addParameter(mFeedbackDbParam = new juce::AudioParameterFloat("Feedback in db",
        "Feedback",
        0.0f,
        100.0f,
        100.0f
    ));
    addParameter(mOffParam = new juce::AudioParameterBool("Delay Off",
        "Off",
        false
    ));
    addParameter(mTappedParam = new juce::AudioParameterBool("Tapped Delay",
        "Tapped",
        false
    ));
    addParameter(mPingPongParam = new juce::AudioParameterBool("Ping Pong Delay",
        "Ping-Pong",
        true
    ));
    addParameter(mBothParam = new juce::AudioParameterBool("Both Delays",
        "Both Delay",
        false
    ));
    addParameter(mFilterFcParamHigh = new juce::AudioParameterFloat("Filter Cutoff High (Hz)",
        "High FC",
        2000.0f,
        20000.0f,
        10000.0f
    ));
    //Mid Params
    addParameter(mFilterFcParamMid = new juce::AudioParameterFloat("Filter Cutoff Mid (Hz)",
        "Mid FC",
        200.0f,
        2000.0f,
        1000.0f
    ));
    //Low params
    addParameter(mFilterFcParamLow = new juce::AudioParameterFloat("Filter Cutoff Low (Hz)",
        "Low FC",
        20.0f,
        200.0f,
        100.0f
    ));

    addParameter(mHighOnParam = new juce::AudioParameterBool("High On",
        "High",
        false
    ));
    addParameter(mMidOnParam = new juce::AudioParameterBool("Mid On",
        "Mid",
        false
    ));
    addParameter(mLowOnParam = new juce::AudioParameterBool("Low On",
        "Low",
        false
    ));
    addParameter(mSyncParam = new juce::AudioParameterBool("Sync Echoes",
        "Sync",
        true
    ));
    addParameter(mBothMixParam = new juce::AudioParameterFloat("Both delay mix",
        "Both Mix",
        0.0f,
        100.0f,
        50.0f
    ));
}

AndrewHp03delaySwitchAudioProcessor::~AndrewHp03delaySwitchAudioProcessor()
{
}

//==============================================================================
const juce::String AndrewHp03delaySwitchAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AndrewHp03delaySwitchAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AndrewHp03delaySwitchAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AndrewHp03delaySwitchAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AndrewHp03delaySwitchAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AndrewHp03delaySwitchAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AndrewHp03delaySwitchAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AndrewHp03delaySwitchAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AndrewHp03delaySwitchAudioProcessor::getProgramName (int index)
{
    return {};
}

void AndrewHp03delaySwitchAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

int AndrewHp03delaySwitchAudioProcessor::calcMsecToSamps(float mSec)
{
    return mSec * 0.001 * mFs;
}

//==============================================================================
void AndrewHp03delaySwitchAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mFs = sampleRate;

    //initialize with max delay length
    int maxSamps = calcMsecToSamps(MAXDELAYMSEC);
    mDelay1L.setMaximumDelay(maxSamps);
    mDelay1R.setMaximumDelay(maxSamps);

    //calcFilterCoeffs();
}

void AndrewHp03delaySwitchAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AndrewHp03delaySwitchAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AndrewHp03delaySwitchAudioProcessor::calcAlgorithmsParams()
{
    //set gains
    mWetGain = mWetDryMixParam->get() / 100.0;
    mDryGain = 1.0 - mWetGain;

    mPPGain = mBothMixParam->get() / 100.0;
    mTGain = 1.0 - mPPGain;

    mSync = mSyncParam->get();

    //set delay time
    //int samps = calcMsecToSamps(mDelayMsecParam->get());
    int sampsL = calcMsecToSamps(mDelayLMsecParam->get());
    int sampsR = calcMsecToSamps(mDelayRMsecParam->get());

    if (mSync == true)
    {
        mDelay1L.setDelay(sampsL);
        mDelay1R.setDelay(sampsL);
    }
    else
    {
        mDelay1L.setDelay(sampsL);
        mDelay1R.setDelay(sampsR);
    }

    tapOffsetL = mDelayLMsecParam->get() / 1000;
    tapOffsetR = mDelayRMsecParam->get() / 1000;

    //set feedback gain
    mFeedbackGainLin = mFeedbackDbParam->get() / 100;

    mOff = mOffParam->get();
    mTapped = mTappedParam->get();
    mPingPong = mPingPongParam->get();
    mBoth = mBothParam->get();

    mHighOn = mHighOnParam->get();
    mMidOn = mMidOnParam->get();
    mLowOn = mLowOnParam->get();

    //calc filter coefficients array of floats
    float fcHigh = mFilterFcParamHigh->get();
    float coeffs[5];
    Mu45FilterCalc::calcCoeffsLPF(coeffs, fcHigh, 1.0, mFs);
    //set coefficients for each filter
    mFilterLHigh.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    mFilterRHigh.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);

    //calc peak filter
    float fcMid = mFilterFcParamMid->get();
    float gMid = -20.0;

    Mu45FilterCalc::calcCoeffsPeak(coeffs, fcMid, gMid, 5.0, mFs);
    //set coefficients for each filter
    mFilterLMid.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    mFilterRMid.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);

    //calcHPF
    float fcLow = mFilterFcParamLow->get();
    Mu45FilterCalc::calcCoeffsHPF(coeffs, fcLow, 1.0, mFs);
    //set coefficients for each filter
    mFilterLLow.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    mFilterRLow.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
}

void AndrewHp03delaySwitchAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    //update params
    calcAlgorithmsParams();

    //process sample
    auto* channelDataLeft = buffer.getWritePointer(0);
    auto* channelDataRight = buffer.getWritePointer(1);

    //temps
    float outL, outR, tempL, tempR, tapSampL, tapSampR;

    if (mOff == true)
    {
        mDelay1L.clear();
        mDelay1R.clear();
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            channelDataLeft[samp] = channelDataLeft[samp];
            channelDataRight[samp] = channelDataRight[samp];
        }
    }
    else if (mTapped == true)
    {
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            outL = channelDataLeft[samp];
            outR = channelDataRight[samp];

            tempL = mDelay1L.nextOut();
            tempR = mDelay1R.nextOut();

            //Feedback filters
            if (mHighOn == true)
            {
                tempL = mFilterLHigh.tick(tempL);
                tempR = mFilterRHigh.tick(tempR);
            }
            if (mMidOn == true)
            {
                tempL = mFilterLMid.tick(tempL);
                tempR = mFilterRMid.tick(tempR);
            }
            if (mLowOn == true)
            {
                tempL = mFilterLLow.tick(tempL);
                tempR = mFilterRLow.tick(tempR);
            }

            tapSampL = mDelay1L.tapOut(48000 * tapOffsetL) * .0625;
            tapSampL += mDelay1L.tapOut(36000 * tapOffsetL) * .125;
            tapSampL += mDelay1L.tapOut(24000 * tapOffsetL) * .25;
            tapSampL += mDelay1L.tapOut(12000 * tapOffsetL) * .5;

            tapSampR = mDelay1R.tapOut(48000 * tapOffsetR) * .0625;
            tapSampR += mDelay1R.tapOut(36000 * tapOffsetR) * .125;
            tapSampR += mDelay1R.tapOut(24000 * tapOffsetR) * .25;
            tapSampR += mDelay1R.tapOut(12000 * tapOffsetR) * .5;

            mDelay1L.tick(mWetGain * outL + mFeedbackGainLin * tempL);
            mDelay1R.tick(mWetGain * outR + mFeedbackGainLin * tempR);

            outL = (mDryGain * channelDataLeft[samp] + mWetGain * tempL) + tapSampL;
            outR = (mDryGain * channelDataRight[samp] + mWetGain * tempR) + tapSampR;

            //send to output
            channelDataLeft[samp] = outL;
            channelDataRight[samp] = outR;
        }
    }
    else if (mPingPong == true)
    {
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            outL = (channelDataLeft[samp] + channelDataRight[samp]) / 2;
            outR = channelDataRight[samp] / 2;

            tempL = mDelay1R.nextOut();
            tempR = mDelay1L.nextOut();
            //Feedback filters
            if (mHighOn == true)
            {
                tempL = mFilterLHigh.tick(tempL);
                tempR = mFilterRHigh.tick(tempR);
            }
            if (mMidOn == true)
            {
                tempL = mFilterLMid.tick(tempL);
                tempR = mFilterRMid.tick(tempR);
            }
            if (mLowOn == true)
            {
                tempL = mFilterLLow.tick(tempL);
                tempR = mFilterRLow.tick(tempR);
            }

            mDelay1L.tick(mWetGain * outL + mFeedbackGainLin * tempL);
            mDelay1R.tick(mWetGain * outR + mFeedbackGainLin * tempR);

            outL = (mDryGain * outL + mWetGain * tempL);
            outR = (mDryGain * outR + mWetGain * tempR);
            //send to output
            channelDataLeft[samp] = outL;
            channelDataRight[samp] = outR;
        }
    }
    else if (mBoth == true)
    {
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            outL = (channelDataLeft[samp] + channelDataRight[samp]) / 2;
            outR = channelDataRight[samp] / 2;

            tempL = mDelay1R.nextOut();
            tempR = mDelay1L.nextOut();

            //Feedback filters
            if (mHighOn == true)
            {
                tempL = mFilterLHigh.tick(tempL);
                tempR = mFilterRHigh.tick(tempR);
            }
            if (mMidOn == true)
            {
                tempL = mFilterLMid.tick(tempL);
                tempR = mFilterRMid.tick(tempR);
            }
            if (mLowOn == true)
            {
                tempL = mFilterLLow.tick(tempL);
                tempR = mFilterRLow.tick(tempR);
            }

            tapSampL = mDelay1L.tapOut(48000 * tapOffsetL) * .0625;
            tapSampL += mDelay1L.tapOut(36000 * tapOffsetL) * .125;
            tapSampL += mDelay1L.tapOut(24000 * tapOffsetL) * .25;
            tapSampL += mDelay1L.tapOut(12000 * tapOffsetL) * .5;

            tapSampR = mDelay1R.tapOut(48000 * tapOffsetR) * .0625;
            tapSampR += mDelay1R.tapOut(36000 * tapOffsetR) * .125;
            tapSampR += mDelay1R.tapOut(24000 * tapOffsetR) * .25;
            tapSampR += mDelay1R.tapOut(12000 * tapOffsetR) * .5;

            mDelay1L.tick(mWetGain * outL + mFeedbackGainLin * tempL);
            mDelay1R.tick(mWetGain * outR + mFeedbackGainLin * tempR);

            outL = (mDryGain * outL + mWetGain * tempL) + tapSampL;
            outR = (mDryGain * outR + mWetGain * tempR) + tapSampR;
            //send to output
            channelDataLeft[samp] = outL;
            channelDataRight[samp] = outR;
        }
    }
}

//==============================================================================
bool AndrewHp03delaySwitchAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AndrewHp03delaySwitchAudioProcessor::createEditor()
{
    return new AndrewHp03delaySwitchAudioProcessorEditor (*this);
}

//==============================================================================
void AndrewHp03delaySwitchAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AndrewHp03delaySwitchAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AndrewHp03delaySwitchAudioProcessor();
}
