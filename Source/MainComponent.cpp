#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 800);
    addAndMakeVisible(&audioPlayer);
    addAndMakeVisible(&audioRecorder);
}

MainComponent::~MainComponent()
{}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    audioPlayer.setBounds(area.removeFromTop(proportionOfHeight(0.5)));
    // print out the dimension of audioRecorder
    audioRecorder.setBounds(area);
}
