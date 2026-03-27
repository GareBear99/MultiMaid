#include "Parameters.h"

namespace
{
    using APVTS = juce::AudioProcessorValueTreeState;

    std::unique_ptr<juce::RangedAudioParameter> makeFloat(const juce::String& id, const juce::String& name,
                                                          float min, float max, float def, float step = 0.01f)
    {
        return std::make_unique<juce::AudioParameterFloat>(id, name, juce::NormalisableRange<float>(min, max, step), def);
    }

    std::unique_ptr<juce::RangedAudioParameter> makeBool(const juce::String& id, const juce::String& name, bool def = false)
    {
        return std::make_unique<juce::AudioParameterBool>(id, name, def);
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout multimaid::params::createLayout()
{
    APVTS::ParameterLayout layout;

    layout.add(makeFloat(inputGain, "Input", -24.0f, 24.0f, 0.0f, 0.01f));
    layout.add(makeFloat(outputGain, "Output", -24.0f, 24.0f, 0.0f, 0.01f));
    layout.add(makeFloat(dryWet, "Mix", 0.0f, 1.0f, 1.0f, 0.001f));
    layout.add(makeFloat(xoverLowMid, "Low/Mid Xover", 40.0f, 1200.0f, 120.0f, 1.0f));
    layout.add(makeFloat(xoverMidHigh, "Mid/High Xover", 800.0f, 12000.0f, 2500.0f, 1.0f));

    auto addBand = [&layout] (const juce::String& prefix, const juce::String& label)
    {
        layout.add(makeFloat(prefix + "Threshold", label + " Threshold", -60.0f, 0.0f, -18.0f, 0.01f));
        layout.add(makeFloat(prefix + "Ratio", label + " Ratio", 1.0f, 20.0f, 2.0f, 0.01f));
        layout.add(makeFloat(prefix + "Attack", label + " Attack", 0.1f, 200.0f, 10.0f, 0.01f));
        layout.add(makeFloat(prefix + "Release", label + " Release", 5.0f, 1000.0f, 120.0f, 0.01f));
        layout.add(makeFloat(prefix + "Knee", label + " Knee", 0.0f, 24.0f, 6.0f, 0.01f));
        layout.add(makeFloat(prefix + "Trim", label + " Trim", -18.0f, 18.0f, 0.0f, 0.01f));
        layout.add(makeBool(prefix + "Bypass", label + " Bypass"));
        layout.add(makeBool(prefix + "Solo", label + " Solo"));
        layout.add(makeBool(prefix + "Mute", label + " Mute"));
    };

    addBand("low",  "Low");
    addBand("mid",  "Mid");
    addBand("high", "High");

    return layout;
}
