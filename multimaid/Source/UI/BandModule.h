#pragma once
#include <JuceHeader.h>

namespace multimaid::ui
{
    struct BandSnapshot
    {
        juce::String label;
        float energyDb = -96.0f;
        float grDb = 0.0f;
    };

    inline void drawBandModule (juce::Graphics& g, juce::Rectangle<int> area, const BandSnapshot& snap, juce::Colour accent)
    {
        g.setColour (juce::Colours::white.withAlpha (0.04f));
        g.fillRoundedRectangle (area.toFloat(), 18.0f);
        g.setColour (juce::Colours::white.withAlpha (0.08f));
        g.drawRoundedRectangle (area.toFloat().reduced (0.5f), 18.0f, 1.0f);

        auto r = area.reduced (12);
        g.setColour (accent);
        g.setFont (juce::FontOptions (16.0f, juce::Font::bold));
        g.drawText (snap.label, r.removeFromTop (22), juce::Justification::centredLeft);

        auto meter = r.removeFromTop (120);
        g.setColour (juce::Colours::white.withAlpha (0.06f));
        g.fillRoundedRectangle (meter.toFloat(), 12.0f);

        auto energyHeight = juce::jmap (snap.energyDb, -96.0f, 0.0f, 0.0f, (float) meter.getHeight());
        auto grHeight = juce::jmap (snap.grDb, -24.0f, 0.0f, (float) meter.getHeight(), 0.0f);

        auto energyRect = meter.withTrimmedTop (meter.getHeight() - (int) energyHeight).reduced (10, 0);
        g.setColour (accent.withAlpha (0.7f));
        g.fillRoundedRectangle (energyRect.toFloat(), 8.0f);

        g.setColour (juce::Colours::red.withAlpha (0.7f));
        g.drawLine ((float) meter.getX(), meter.getY() + grHeight, (float) meter.getRight(), meter.getY() + grHeight, 2.0f);

        r.removeFromTop (8);
        g.setColour (juce::Colours::lightgrey);
        g.setFont (juce::FontOptions (13.0f));
        g.drawText ("Energy: " + juce::String (snap.energyDb, 1) + " dB", r.removeFromTop (18), juce::Justification::centredLeft);
        g.drawText ("GR: " + juce::String (snap.grDb, 1) + " dB", r.removeFromTop (18), juce::Justification::centredLeft);
    }
}
