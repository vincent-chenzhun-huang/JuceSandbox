/*
  ==============================================================================

    AudioThumbnail.cpp
    Created: 26 Dec 2023 11:46:39am
    Author:  Vincent Huang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayerThumbnail.h"

//==============================================================================
PlayerThumbnail::PlayerThumbnail(int sourceSamplesPerThumbnailSample, juce::AudioFormatManager& formatManager, juce::AudioThumbnailCache& cache)
    : thumbnail(sourceSamplesPerThumbnailSample, formatManager, cache)
{
    thumbnail.addChangeListener(this);
}

PlayerThumbnail::~PlayerThumbnail()
{
}

void PlayerThumbnail::setFile(juce::File& file)
{
    thumbnail.setSource(new juce::FileInputSource(file));
}

void PlayerThumbnail::paint (juce::Graphics& g)
{
    if (thumbnail.getNumChannels() == 0)
        paintIfNoFileLoaded(g);
    else
        paintIfFileLoaded(g);
}

void PlayerThumbnail::paintIfNoFileLoaded(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.drawFittedText("No File Loaded", getLocalBounds(), juce::Justification::centred, 1);
}

void PlayerThumbnail::paintIfFileLoaded(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    thumbnail.drawChannels(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 1.0f);
}

void PlayerThumbnail::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &thumbnail)
        repaint();
}