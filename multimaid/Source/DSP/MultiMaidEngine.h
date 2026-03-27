#pragma once
#include <JuceHeader.h>
#include "BandCompressor.h"
#include "CrossoverNetwork.h"

namespace multimaid::dsp
{
    struct BandMeterState
    {
        float energyDb = -96.0f;
        float grDb = 0.0f;
    };

    struct EngineFrame
    {
        BandMeterState low, mid, high;
        float inputDb = -96.0f;
        float outputDb = -96.0f;
    };

    class MultiMaidEngine
    {
    public:
        void prepare (double sampleRate, int maxBlockSize, int numChannels)
        {
            juce::ignoreUnused (maxBlockSize);
            juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) juce::jmax (1, maxBlockSize), (juce::uint32) juce::jmax (1, numChannels) };
            crossover.prepare (spec);
            lowComp.prepare (sampleRate, numChannels);
            midComp.prepare (sampleRate, numChannels);
            highComp.prepare (sampleRate, numChannels);
            lowBuffer.setSize (numChannels, maxBlockSize, false, false, true);
            midBuffer.setSize (numChannels, maxBlockSize, false, false, true);
            highBuffer.setSize (numChannels, maxBlockSize, false, false, true);
            dryBuffer.setSize (numChannels, maxBlockSize, false, false, true);
            frame = {};
        }

        void setCrossovers (float lowMid, float midHigh)
        {
            crossover.setCrossovers (lowMid, midHigh);
        }

        void setLowSettings (const CompressorSettings& s)  { lowSettings = s; lowComp.setSettings (s); }
        void setMidSettings (const CompressorSettings& s)  { midSettings = s; midComp.setSettings (s); }
        void setHighSettings (const CompressorSettings& s) { highSettings = s; highComp.setSettings (s); }

        void process (juce::AudioBuffer<float>& buffer, float inputGainDb, float outputGainDb, float dryWet)
        {
            dryBuffer.makeCopyOf (buffer, true);
            applyGain (buffer, inputGainDb);
            frame.inputDb = getBufferDb (buffer);

            crossover.split (buffer, lowBuffer, midBuffer, highBuffer);

            lowComp.process (lowBuffer);
            midComp.process (midBuffer);
            highComp.process (highBuffer);

            if (lowSettings.mute)  lowBuffer.clear();
            if (midSettings.mute)  midBuffer.clear();
            if (highSettings.mute) highBuffer.clear();

            const bool anySolo = lowSettings.solo || midSettings.solo || highSettings.solo;
            if (anySolo)
            {
                if (! lowSettings.solo)  lowBuffer.clear();
                if (! midSettings.solo)  midBuffer.clear();
                if (! highSettings.solo) highBuffer.clear();
            }

            buffer.clear();
            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            {
                buffer.addFrom (ch, 0, lowBuffer, ch, 0, buffer.getNumSamples());
                buffer.addFrom (ch, 0, midBuffer, ch, 0, buffer.getNumSamples());
                buffer.addFrom (ch, 0, highBuffer, ch, 0, buffer.getNumSamples());
            }

            applyGain (buffer, outputGainDb);
            mixDryWet (buffer, dryBuffer, dryWet);
            frame.outputDb = getBufferDb (buffer);
            frame.low = meterFrom (lowBuffer, lowComp.getLastGainReductionDb());
            frame.mid = meterFrom (midBuffer, midComp.getLastGainReductionDb());
            frame.high = meterFrom (highBuffer, highComp.getLastGainReductionDb());
        }

        const EngineFrame& getFrame() const noexcept { return frame; }

    private:
        static void applyGain (juce::AudioBuffer<float>& b, float db)
        {
            b.applyGain (juce::Decibels::decibelsToGain (db));
        }

        static void mixDryWet (juce::AudioBuffer<float>& wet, const juce::AudioBuffer<float>& dry, float mix)
        {
            const float dryGain = 1.0f - mix;
            const float wetGain = mix;
            wet.applyGain (wetGain);
            for (int ch = 0; ch < wet.getNumChannels(); ++ch)
                wet.addFrom (ch, 0, dry, ch, 0, wet.getNumSamples(), dryGain);
        }

        static float getBufferDb (const juce::AudioBuffer<float>& buffer)
        {
            double sum = 0.0;
            const int n = juce::jmax (1, buffer.getNumChannels() * buffer.getNumSamples());
            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            {
                const float* d = buffer.getReadPointer (ch);
                for (int i = 0; i < buffer.getNumSamples(); ++i)
                    sum += d[i] * d[i];
            }
            return juce::Decibels::gainToDecibels ((float) std::sqrt (sum / (double) n), -96.0f);
        }

        static BandMeterState meterFrom (const juce::AudioBuffer<float>& b, float grDb)
        {
            return { getBufferDb (b), grDb };
        }

        ThreeBandCrossover crossover;
        BandCompressor lowComp, midComp, highComp;
        CompressorSettings lowSettings, midSettings, highSettings;
        juce::AudioBuffer<float> lowBuffer, midBuffer, highBuffer, dryBuffer;
        EngineFrame frame;
    };
}
