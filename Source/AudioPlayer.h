/*
  ==============================================================================

    AudioPlayer.h
    Created: 17 Dec 2023 9:34:05pm
    Author:  Vincent Huang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/PlayerThumbnail.h"
#include "../Utils/PlayHead.h"

//==============================================================================
/*
*/

enum TransportState
{
    Stopped,
    Starting,
    Playing,
    Pausing,
    Paused,
    Stopping
};

class AudioPlayer  : public juce::AudioAppComponent,
                     public juce::ChangeListener
{
public:
    AudioPlayer();
    ~AudioPlayer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    // playback controls
    juce::TextButton playButton;
    juce::TextButton stopButton;
    juce::TextButton openButton;
    juce::Label volumeLabel;
    juce::Slider volumeSlider;
    juce::Label noiseLabel;
    juce::Slider noiseSlider;

    juce::Random random;

    // I/O
    std::unique_ptr<juce::FileChooser> fileChooser;

    // audio
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    TransportState state;

    PlayerThumbnail playerThumbnail;
    PlayHead playHead;
    
    juce::AudioThumbnailCache thumbnailCache;

    void changeState(TransportState newState);
    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void transportSourceChanged();

    int numUnits; // for dividing the area into unit rows
    int paramUnits;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayer)
};
