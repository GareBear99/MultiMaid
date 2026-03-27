#pragma once
#include <JuceHeader.h>

namespace multimaid::dsp
{
    class ThreeBandCrossover
    {
    public:
        void prepare (const juce::dsp::ProcessSpec& spec)
        {
            sampleRate = spec.sampleRate;
            channels = (int) spec.numChannels;
            lowPassLowMid.prepare (spec);
            highPassLowMid.prepare (spec);
            lowPassMidHigh.prepare (spec);
            highPassMidHigh.prepare (spec);
            updateFilters();
        }

        void setCrossovers (float lowMidHz, float midHighHz)
        {
            xoverLowMid = juce::jlimit (40.0f, 1200.0f, lowMidHz);
            xoverMidHigh = juce::jlimit (800.0f, 12000.0f, juce::jmax (midHighHz, xoverLowMid + 100.0f));
            updateFilters();
        }

        void split (const juce::AudioBuffer<float>& input,
                    juce::AudioBuffer<float>& low,
                    juce::AudioBuffer<float>& mid,
                    juce::AudioBuffer<float>& high)
        {
            low.makeCopyOf (input, true);
            mid.makeCopyOf (input, true);
            high.makeCopyOf (input, true);

            {
                juce::dsp::AudioBlock<float> lowBlock (low);
                juce::dsp::ProcessContextReplacing<float> ctx (lowBlock);
                lowPassLowMid.process (ctx);
            }
            {
                juce::dsp::AudioBlock<float> highBlock (high);
                juce::dsp::ProcessContextReplacing<float> ctx (highBlock);
                highPassMidHigh.process (ctx);
            }
            {
                juce::AudioBuffer<float> hp (input.getNumChannels(), input.getNumSamples());
                hp.makeCopyOf (input, true);
                juce::dsp::AudioBlock<float> hpBlock (hp);
                juce::dsp::ProcessContextReplacing<float> hpCtx (hpBlock);
                highPassLowMid.process (hpCtx);

                juce::dsp::AudioBlock<float> midBlock (mid);
                juce::dsp::ProcessContextReplacing<float> midCtx (midBlock);
                lowPassMidHigh.process (midCtx);

                for (int ch = 0; ch < mid.getNumChannels(); ++ch)
                    mid.copyFrom (ch, 0, hp, ch, 0, hp.getNumSamples());

                juce::dsp::AudioBlock<float> finalMidBlock (mid);
                juce::dsp::ProcessContextReplacing<float> finalMidCtx (finalMidBlock);
                lowPassMidHigh.process (finalMidCtx);
            }
        }

    private:
        void updateFilters()
        {
            *lowPassLowMid.state  = *juce::dsp::IIR::Coefficients<float>::makeLowPass  (sampleRate, xoverLowMid);
            *highPassLowMid.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, xoverLowMid);
            *lowPassMidHigh.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass  (sampleRate, xoverMidHigh);
            *highPassMidHigh.state= *juce::dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, xoverMidHigh);
        }

        double sampleRate = 44100.0;
        int channels = 2;
        float xoverLowMid = 120.0f;
        float xoverMidHigh = 2500.0f;

        juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowPassLowMid, highPassLowMid, lowPassMidHigh, highPassMidHigh;
    };
}
