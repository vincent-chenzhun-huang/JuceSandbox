#pragma once

#include <JuceHeader.h>
#include "AudioPlayer.h"
#include "AudioRecorder.h"
#include "../Utils/Logger.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent(SandboxLogger* logger);
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    AudioPlayer audioPlayer;
    AudioRecorder audioRecorder;
    SandboxLogger* logger;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
