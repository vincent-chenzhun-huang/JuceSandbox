#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    addAndMakeVisible(&audioPlayer);
}

MainComponent::~MainComponent()
{}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    audioPlayer.setBounds(area.removeFromLeft(area.getWidth()));
}
