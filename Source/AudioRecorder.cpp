/*
  ==============================================================================

    AudioRecorder.cpp
    Created: 27 Dec 2023 9:19:44pm
    Author:  Vincent Huang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioRecorder.h"

//==============================================================================
AudioRecorder::AudioRecorder() : audioSettings(deviceManager, 0, 256, 0, 256, false, false, false, false)
{
    addAndMakeVisible(&audioSettings);
}

AudioRecorder::~AudioRecorder()
{
}

void AudioRecorder::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("AudioRecorder", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void AudioRecorder::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
}

void AudioRecorder::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
}

void AudioRecorder::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void AudioRecorder::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    audioSettings.setBounds(getLocalBounds());
}
