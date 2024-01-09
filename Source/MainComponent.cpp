#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(SandboxLogger* logger) : logger(logger), audioPlayer(logger), audioRecorder(logger)
{
    setSize (600, 800);
    logger->log("Loading audio player", SandboxLogger::LogLevel::LOGGER_DEBUG);
    addAndMakeVisible(&audioPlayer);
    logger->log("Loading audio recorder", SandboxLogger::LogLevel::LOGGER_DEBUG);
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
