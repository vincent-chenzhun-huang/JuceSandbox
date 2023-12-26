/*
  ==============================================================================

    AudioPlayer.cpp
    Created: 17 Dec 2023 9:34:05pm
    Author:  Vincent Huang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioPlayer.h"
#include "../Utils/PlayerThumbnail.h"

//==============================================================================
AudioPlayer::AudioPlayer() : state(Stopped), thumbnailCache(5), numUnits(8), playerThumbnail(512, formatManager, thumbnailCache), playHead(transportSource)
{
    addAndMakeVisible(&playButton);
    playButton.setButtonText("Play");
    playButton.onClick = [this] { playButtonClicked(); };

    addAndMakeVisible(&stopButton);
    stopButton.setButtonText("Stop");
    stopButton.onClick = [this] { stopButtonClicked(); };

    addAndMakeVisible(&openButton);
    openButton.setButtonText("Open");
    openButton.onClick = [this] { openButtonClicked(); };

    formatManager.registerBasicFormats();
    transportSource.addChangeListener (this);

    setAudioChannels (0, 2);

    addAndMakeVisible(&volumeLabel);
    volumeLabel.setText("Volume", juce::dontSendNotification);
    addAndMakeVisible(&volumeSlider);
    volumeSlider.setRange(0.0, 1.0, 0.1);
    volumeSlider.setValue(0.5);

    addAndMakeVisible(&noiseLabel);
    noiseLabel.setText("Noise", juce::dontSendNotification);
    addAndMakeVisible(&noiseSlider);
    noiseSlider.setRange(0.0, 0.5, 0.05);
    noiseSlider.setValue(0.0);

    addAndMakeVisible(&playerThumbnail);
    // print out the dimension of the thumbnail
    addAndMakeVisible(&playHead);
}

AudioPlayer::~AudioPlayer ()
{
    shutdownAudio();
}

void AudioPlayer::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
}

void AudioPlayer::resized()
{
    // print out component dimension
    auto area = getLocalBounds();
    area.reduce(area.getWidth() / (numUnits * 2), area.getHeight() / (numUnits * 2));
    auto areaHeight = area.getHeight();

    auto rowHeight = area.getHeight() / numUnits;
    openButton.setBounds(area.removeFromTop(rowHeight));

    auto buttonRow = area.removeFromTop(rowHeight);
    playButton.setBounds(buttonRow.removeFromLeft(area.getWidth() / 2));
    stopButton.setBounds(buttonRow);

    auto volumeRow = area.removeFromTop(rowHeight);
    volumeLabel.setBounds(volumeRow.removeFromLeft(volumeRow.getWidth() / 4));
    volumeSlider.setBounds(volumeRow);

    auto noiseRow = area.removeFromTop(rowHeight);
    noiseLabel.setBounds(noiseRow.removeFromLeft(noiseRow.getWidth() / 4));
    noiseSlider.setBounds(noiseRow);

    auto thumbnailHeight = areaHeight * (numUnits - paramUnits) / numUnits;
    auto thumbnailArea = area.removeFromBottom(thumbnailHeight);
    playerThumbnail.setBounds(thumbnailArea);

    playHead.setBounds(thumbnailArea);
}

void AudioPlayer::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        transportSourceChanged();
    }
}

void AudioPlayer::transportSourceChanged()
{
    if (transportSource.isPlaying())
    {
        changeState(Playing);
    } else if ((state == Stopping) || (state == Playing))
    {
        changeState(Stopped);
    } else if (state == Pausing)
    {
        changeState(Paused);
    }
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock(bufferToFill);

    auto level = (float) volumeSlider.getValue();
    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        bufferToFill.buffer->applyGain(channel, bufferToFill.startSample, bufferToFill.numSamples, level);
    }

    auto noiseLevel = (float) noiseSlider.getValue();
    // add random noise of noiseLevel to the buffer
    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        auto* inBuffer = bufferToFill.buffer->getReadPointer(channel, bufferToFill.startSample);
        auto* outBuffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            auto noise = (random.nextFloat() * 2.0f) - 1.0f;
            outBuffer[sample] = inBuffer[sample] + inBuffer[sample] * noise * noiseLevel;
        }
    }
}

void AudioPlayer::releaseResources()
{
    transportSource.releaseResources();
}

void AudioPlayer::changeState (TransportState newState) {
    /*
    State transition rules:
    - only change state when the newState is different from the current state
    - only change state when the newState is valid
    */

   if (state != newState)
   {
        state = newState;
        if (state == Stopped)
        {
            playButton.setButtonText("Play");
            stopButton.setButtonText("Stop");
            stopButton.setEnabled(false);
            playButton.setEnabled(true);
            transportSource.setPosition(0.0);
        } else if (state == Starting)
        {
            transportSource.start();
        } else if (state == Playing) 
        {
            playButton.setButtonText("Pause");
            stopButton.setButtonText("Stop");
            stopButton.setEnabled(true);
        } else if (state == Stopping)
        {
            transportSource.stop();
        } else if (state == Pausing)
        {
            transportSource.stop();
        } else if (state == Paused)
        {
            playButton.setButtonText("Resume");
            stopButton.setButtonText("Reset");
        }
   }
}

void AudioPlayer::openButtonClicked()
{
    fileChooser = std::make_unique<juce::FileChooser>("Select a Wave file to play...", juce::File{}, "*.wav");

    auto chooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc)
    {
        auto file = fc.getResult();

        if (file != juce::File{})
        {
            auto* reader = formatManager.createReaderFor(file);

            if (reader != nullptr)
            {
                auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
                transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
                playButton.setEnabled (true);
                playerThumbnail.setFile(file);
                readerSource.reset (newSource.release());
            }
        }
    });
}

void AudioPlayer::playButtonClicked()
{
    if ((state == Stopped) || (state == Paused))
    {
        changeState(Starting);
    } else if (state == Playing)
    {
        changeState(Pausing);
    }
}

void AudioPlayer::stopButtonClicked()
{
    if (state == Paused)
    {
        changeState(Stopped);
    } else if (state == Playing)
    {
        changeState(Stopping);
    }
}
