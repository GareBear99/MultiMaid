#pragma once
#include <JuceHeader.h>

namespace multimaid::ui
{
    inline void drawCrossoverView (juce::Graphics& g, juce::Rectangle<int> area, float lowMidHz, float midHighHz)
    {
        g.setColour (juce::Colours::white.withAlpha (0.04f));
        g.fillRoundedRectangle (area.toFloat(), 16.0f);
        g.setColour (juce::Colours::white.withAlpha (0.08f));
        g.drawRoundedRectangle (area.toFloat().reduced (0.5f), 16.0f, 1.0f);

        auto r = area.reduced (12);
        g.setColour (juce::Colour::fromRGB (255, 230, 170));
        g.setFont (juce::FontOptions (15.0f, juce::Font::bold));
        g.drawText ("Crossover View", r.removeFromTop (20), juce::Justification::centredLeft);

        auto graph = r.reduced (0, 8);
        g.setColour (juce::Colours::white.withAlpha (0.05f));
        for (int i = 0; i < 5; ++i)
        {
            const float x = juce::jmap ((float) i / 4.0f, (float) graph.getX(), (float) graph.getRight());
            g.drawVerticalLine ((int) x, (float) graph.getY(), (float) graph.getBottom());
        }

        auto mapFreq = [&graph] (float hz)
        {
            const float minHz = 20.0f;
            const float maxHz = 20000.0f;
            const float norm = (std::log (hz) - std::log (minHz)) / (std::log (maxHz) - std::log (minHz));
            return juce::jmap (norm, 0.0f, 1.0f, (float) graph.getX(), (float) graph.getRight());
        };

        const float x1 = mapFreq (lowMidHz);
        const float x2 = mapFreq (midHighHz);
        g.setColour (juce::Colour::fromRGB (255, 196, 128));
        g.drawLine (x1, (float) graph.getY(), x1, (float) graph.getBottom(), 2.0f);
        g.setColour (juce::Colour::fromRGB (130, 220, 255));
        g.drawLine (x2, (float) graph.getY(), x2, (float) graph.getBottom(), 2.0f);

        g.setColour (juce::Colours::lightgrey);
        g.setFont (juce::FontOptions (12.0f));
        g.drawText (juce::String ((int) lowMidHz) + " Hz", (int) x1 + 4, graph.getY() + 4, 100, 16, juce::Justification::left);
        g.drawText (juce::String ((int) midHighHz) + " Hz", (int) x2 + 4, graph.getY() + 20, 120, 16, juce::Justification::left);
    }
}
