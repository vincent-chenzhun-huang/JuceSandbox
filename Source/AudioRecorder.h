/*
  ==============================================================================

    AudioRecorder.h
    Created: 27 Dec 2023 9:19:44pm
    Author:  Vincent Huang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AudioRecorder  : public juce::AudioAppComponent
{
public:
    AudioRecorder();
    ~AudioRecorder() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

private:
    juce::AudioDeviceSelectorComponent audioSettings;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioRecorder)
};
