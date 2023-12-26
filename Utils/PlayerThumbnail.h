/*
  ==============================================================================

    AudioThumbnail.h
    Created: 26 Dec 2023 11:46:39am
    Author:  Vincent Huang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlayerThumbnail  : public juce::Component, private juce::ChangeListener
{
public:
    PlayerThumbnail(int sourceSamplesPerThumbnailSample, juce::AudioFormatManager& formatManager, juce::AudioThumbnailCache& cache);
    ~PlayerThumbnail() override;

    void setFile(juce::File& file);
    void paintIfNoFileLoaded(juce::Graphics& g);
    void paintIfFileLoaded(juce::Graphics& g);
    void paint (juce::Graphics&) override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    juce::AudioThumbnail thumbnail;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerThumbnail)
};
