#include "PluginEditor.h"

MultiMaidAudioProcessorEditor::MultiMaidAudioProcessorEditor (MultiMaidAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setResizable (true, true);
    setResizeLimits (980, 620, 1600, 1000);
    setSize (1180, 760);
    startTimerHz (30);
}

void MultiMaidAudioProcessorEditor::timerCallback()
{
    repaint();
}

void MultiMaidAudioProcessorEditor::paint (juce::Graphics& g)
{
    using namespace juce;
    auto area = getLocalBounds();

    Colour bg1 = Colour::fromRGB (11, 14, 20);
    Colour bg2 = Colour::fromRGB (20, 26, 38);
    Colour gold = Colour::fromRGB (255, 230, 170);
    Colour amber = Colour::fromRGB (255, 198, 120);
    Colour cyan = Colour::fromRGB (130, 220, 255);
    Colour warm = Colour::fromRGB (255, 176, 120);

    g.setGradientFill (ColourGradient (bg2, 0, 0, bg1, 0, (float) getHeight(), false));
    g.fillAll();

    auto header = area.removeFromTop (86).reduced (16, 12);
    g.setColour (Colours::white.withAlpha (0.05f));
    g.fillRoundedRectangle (header.toFloat(), 20.0f);
    g.setColour (Colours::white.withAlpha (0.08f));
    g.drawRoundedRectangle (header.toFloat().reduced (0.5f), 20.0f, 1.0f);

    auto h = header.reduced (16, 12);
    g.setColour (gold);
    g.setFont (FontOptions (34.0f, Font::bold));
    g.drawText ("MultiMaid", h.removeFromTop (34), Justification::centredLeft);
    g.setColour (Colours::lightgrey);
    g.setFont (FontOptions (15.0f));
    g.drawText ("3-band multiband control engine — shape stays in FreeEQ8, glue stays in GlueMaid.", h.removeFromTop (20), Justification::centredLeft);

    auto body = area.reduced (16, 8);
    auto top = body.removeFromTop (430);
    auto bottom = body.reduced (0, 0);

    auto left = top.removeFromLeft (top.getWidth() / 3).reduced (0, 0);
    auto center = top.removeFromLeft (top.getWidth() / 2).reduced (8, 0);
    auto right = top.reduced (8, 0);

    const auto& frame = audioProcessor.getLatestFrame();
    multimaid::ui::drawBandModule (g, left, { "LOW", frame.low.energyDb, frame.low.grDb }, warm);
    multimaid::ui::drawBandModule (g, center, { "MID", frame.mid.energyDb, frame.mid.grDb }, amber);
    multimaid::ui::drawBandModule (g, right, { "HIGH", frame.high.energyDb, frame.high.grDb }, cyan);

    auto lowerLeft = bottom.removeFromLeft ((int) (bottom.getWidth() * 0.58f));
    auto lowerRight = bottom.reduced (8, 0);

    multimaid::ui::drawCrossoverView (g, lowerLeft, audioProcessor.apvts.getRawParameterValue (multimaid::params::xoverLowMid)->load(),
                                      audioProcessor.apvts.getRawParameterValue (multimaid::params::xoverMidHigh)->load());

    g.setColour (Colours::white.withAlpha (0.04f));
    g.fillRoundedRectangle (lowerRight.toFloat(), 16.0f);
    g.setColour (Colours::white.withAlpha (0.08f));
    g.drawRoundedRectangle (lowerRight.toFloat().reduced (0.5f), 16.0f, 1.0f);

    auto r = lowerRight.reduced (14);
    g.setColour (gold);
    g.setFont (FontOptions (16.0f, Font::bold));
    g.drawText ("Global Status", r.removeFromTop (20), Justification::centredLeft);
    g.setColour (Colours::lightgrey);
    g.setFont (FontOptions (14.0f));
    g.drawText ("Input:  " + String (frame.inputDb, 1) + " dB", r.removeFromTop (22), Justification::centredLeft);
    g.drawText ("Output: " + String (frame.outputDb, 1) + " dB", r.removeFromTop (22), Justification::centredLeft);
    r.removeFromTop (8);
    g.drawText ("Role lock:", r.removeFromTop (18), Justification::centredLeft);
    g.drawText ("• FreeEQ8 shapes", r.removeFromTop (18), Justification::centredLeft);
    g.drawText ("• MultiMaid controls", r.removeFromTop (18), Justification::centredLeft);
    g.drawText ("• GlueMaid glues", r.removeFromTop (18), Justification::centredLeft);
}

void MultiMaidAudioProcessorEditor::resized()
{
}
