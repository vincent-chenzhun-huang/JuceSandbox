/*
  ==============================================================================

    PlayHead.cpp
    Created: 26 Dec 2023 11:49:10am
    Author:  Vincent Huang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayHead.h"

//==============================================================================
PlayHead::PlayHead(const juce::AudioTransportSource& transportSourceToUse) : transportSource(transportSourceToUse)
{
    startTimer(40);
}

PlayHead::~PlayHead()
{
}

void PlayHead::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    auto duration = (float) transportSource.getLengthInSeconds();

    if (duration > 0.0)
    {
        auto audioPosition = (float) transportSource.getCurrentPosition();
        auto drawPosition = (audioPosition / duration) * getWidth();

        g.setColour(juce::Colours::red);
        g.drawLine(drawPosition, 0.0f, drawPosition, (float) getHeight(), 2.0f);
    }
}

void PlayHead::timerCallback()
{
    repaint();
}
