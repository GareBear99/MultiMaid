#pragma once
#include <JuceHeader.h>

namespace multimaid::dsp
{
    struct CompressorSettings
    {
        float thresholdDb = -18.0f;
        float ratio = 2.0f;
        float attackMs = 10.0f;
        float releaseMs = 120.0f;
        float kneeDb = 6.0f;
        float trimDb = 0.0f;
        bool bypass = false;
        bool solo = false;
        bool mute = false;
    };

    class BandCompressor
    {
    public:
        void prepare (double sampleRate, int channels)
        {
            sr = sampleRate;
            detector.assign ((size_t) juce::jmax (1, channels), 0.0f);
            envelope.assign ((size_t) juce::jmax (1, channels), 0.0f);
            gain.assign ((size_t) juce::jmax (1, channels), 1.0f);
        }

        void setSettings (const CompressorSettings& newSettings)
        {
            settings = newSettings;
        }

        void process (juce::AudioBuffer<float>& buffer)
        {
            lastGrDb = 0.0f;
            if (settings.bypass)
                return;

            const int channels = buffer.getNumChannels();
            const int samples = buffer.getNumSamples();
            const float attackCoeff = calcCoeff (settings.attackMs);
            const float releaseCoeff = calcCoeff (settings.releaseMs);
            const float trimGain = juce::Decibels::decibelsToGain (settings.trimDb);

            for (int ch = 0; ch < channels; ++ch)
            {
                float* data = buffer.getWritePointer (ch);
                for (int i = 0; i < samples; ++i)
                {
                    const float in = data[i];
                    const float absIn = std::abs (in) + 1.0e-9f;
                    const float inDb = juce::Decibels::gainToDecibels (absIn);
                    const float overDb = inDb - settings.thresholdDb;

                    float targetGrDb = 0.0f;
                    if (settings.ratio > 1.0f && overDb > 0.0f)
                    {
                        const float compressedDb = settings.thresholdDb + overDb / settings.ratio;
                        targetGrDb = compressedDb - inDb;
                    }

                    const float desired = juce::Decibels::decibelsToGain (targetGrDb);
                    const float coeff = desired < gain[(size_t) ch] ? attackCoeff : releaseCoeff;
                    gain[(size_t) ch] = coeff * gain[(size_t) ch] + (1.0f - coeff) * desired;
                    data[i] = in * gain[(size_t) ch] * trimGain;

                    const float grDb = juce::Decibels::gainToDecibels (juce::jmax (gain[(size_t) ch], 1.0e-9f));
                    lastGrDb = juce::jmin (lastGrDb, grDb);
                }
            }
        }

        float getLastGainReductionDb() const noexcept { return lastGrDb; }

    private:
        float calcCoeff (float timeMs) const
        {
            return std::exp (-1.0f / (0.001f * juce::jmax (timeMs, 0.01f) * (float) sr));
        }

        double sr = 44100.0;
        CompressorSettings settings;
        std::vector<float> detector, envelope, gain;
        float lastGrDb = 0.0f;
    };
}
