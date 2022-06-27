/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
SIDAudioProcessorEditor::SIDAudioProcessorEditor (SIDAudioProcessor& p)
  : ProcessorEditor (p), sidProc (p)
{
    additionalProgramming = "Dag Lem";

    using AP = SIDAudioProcessor;

    for (auto pp : p.getPluginParameters())
    {
        gin::ParamComponent* c;

        if (pp->getUid().contains ("tune") || pp->getUid().contains ("fine"))
            c = new gin::Knob (pp, true);
        else if (pp->getUid() == AP::paramWave1 || pp->getUid() == AP::paramWave2 || pp->getUid() == AP::paramWave3)
            c = new gin::Select (pp);
        else
            c = pp->isOnOff() ? (gin::ParamComponent*) new gin::Switch (pp) : (gin::ParamComponent*) new gin::Knob (pp);

        addAndMakeVisible (c);
        controls.add (c);
    }

    addAndMakeVisible (&scope);

    setGridSize (17, 3);

    scope.setNumSamplesPerPixel (2);
    scope.setVerticalZoomFactor (3.0f);
    scope.setColour (gin::TriggeredScope::lineColourId, findColour (gin::PluginLookAndFeel::grey45ColourId));
    scope.setColour (gin::TriggeredScope::traceColourId + 0, findColour (gin::PluginLookAndFeel::accentColourId));
    scope.setColour (gin::TriggeredScope::envelopeColourId + 0, juce::Colours::transparentBlack);
    scope.setColour (gin::TriggeredScope::traceColourId + 1, findColour (gin::PluginLookAndFeel::accentColourId));
    scope.setColour (gin::TriggeredScope::envelopeColourId + 1, juce::Colours::transparentBlack);
}

SIDAudioProcessorEditor::~SIDAudioProcessorEditor()
{
}

//==============================================================================
void SIDAudioProcessorEditor::paint (juce::Graphics& g)
{
    ProcessorEditor::paint (g);
}

void SIDAudioProcessorEditor::resized()
{
    using AP = SIDAudioProcessor;

    ProcessorEditor::resized();

    int idx = 0;
    juce::Rectangle<int> rc;
    for (auto pp : sidProc.getPluginParameters())
    {
        if (idx < 30)
        {
            if (idx % 10 == 8)
            {
                rc = getGridArea (idx % 10, idx / 10);
                componentForId (pp->getUid())->setBounds (rc.removeFromTop (rc.getHeight() / 2).translated (0, 7));
            }
            else if (idx % 10 == 9)
            {
                componentForId (pp->getUid())->setBounds (rc);
            }
            else
            {
                componentForId (pp->getUid())->setBounds (getGridArea (idx % 10, idx / 10));
            }
        }
        else if (idx == 38)
        {
            componentForId (pp->getUid())->setBounds (getGridArea (16, 0));
        }
        else if (idx == 40)
        {
            componentForId (pp->getUid())->setBounds (getGridArea (16, 1));
        }
        else
        {
            componentForId (pp->getUid())->setBounds (getGridArea (9 + (idx - 30), 2));
        }

        idx++;
    }

    rc = getGridArea (0, 2);
    componentForId (AP::paramWave3)->setBounds (rc.removeFromTop (rc.getHeight() / 2).translated (0, 7));
    componentForId (AP::paramOutput3)->setBounds (rc);

    scope.setBounds (getGridArea (9, 0, 7, 2).reduced (5));
}
