/*
  ==============================================================================

    PlayHead.h
    Created: 26 Dec 2023 11:49:10am
    Author:  Vincent Huang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlayHead  : public juce::Component, private juce::Timer
{
public:
    PlayHead(const juce::AudioTransportSource&);
    ~PlayHead() override;

    void paint (juce::Graphics&) override;
private:
    void timerCallback() override;

    const juce::AudioTransportSource& transportSource;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayHead)
};
