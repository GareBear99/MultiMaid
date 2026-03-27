#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/BandModule.h"
#include "UI/CrossoverView.h"

class MultiMaidAudioProcessorEditor : public juce::AudioProcessorEditor,
                                      private juce::Timer
{
public:
    explicit MultiMaidAudioProcessorEditor (MultiMaidAudioProcessor&);
    ~MultiMaidAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;

    MultiMaidAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiMaidAudioProcessorEditor)
};
