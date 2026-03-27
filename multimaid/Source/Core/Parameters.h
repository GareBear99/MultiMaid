#pragma once
#include <JuceHeader.h>

namespace multimaid::params
{
    inline constexpr auto inputGain  = "inputGain";
    inline constexpr auto outputGain = "outputGain";
    inline constexpr auto dryWet     = "dryWet";
    inline constexpr auto xoverLowMid  = "xoverLowMid";
    inline constexpr auto xoverMidHigh = "xoverMidHigh";

    inline constexpr auto lowThreshold  = "lowThreshold";
    inline constexpr auto lowRatio      = "lowRatio";
    inline constexpr auto lowAttack     = "lowAttack";
    inline constexpr auto lowRelease    = "lowRelease";
    inline constexpr auto lowKnee       = "lowKnee";
    inline constexpr auto lowTrim       = "lowTrim";
    inline constexpr auto lowBypass     = "lowBypass";
    inline constexpr auto lowSolo       = "lowSolo";
    inline constexpr auto lowMute       = "lowMute";

    inline constexpr auto midThreshold  = "midThreshold";
    inline constexpr auto midRatio      = "midRatio";
    inline constexpr auto midAttack     = "midAttack";
    inline constexpr auto midRelease    = "midRelease";
    inline constexpr auto midKnee       = "midKnee";
    inline constexpr auto midTrim       = "midTrim";
    inline constexpr auto midBypass     = "midBypass";
    inline constexpr auto midSolo       = "midSolo";
    inline constexpr auto midMute       = "midMute";

    inline constexpr auto highThreshold = "highThreshold";
    inline constexpr auto highRatio     = "highRatio";
    inline constexpr auto highAttack    = "highAttack";
    inline constexpr auto highRelease   = "highRelease";
    inline constexpr auto highKnee      = "highKnee";
    inline constexpr auto highTrim      = "highTrim";
    inline constexpr auto highBypass    = "highBypass";
    inline constexpr auto highSolo      = "highSolo";
    inline constexpr auto highMute      = "highMute";

    juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
}
