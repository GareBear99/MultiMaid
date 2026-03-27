#include "PluginProcessor.h"
#include "PluginEditor.h"

MultiMaidAudioProcessor::MultiMaidAudioProcessor()
    : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMETERS", multimaid::params::createLayout())
{
}

const juce::String MultiMaidAudioProcessor::getName() const { return JucePlugin_Name; }
bool MultiMaidAudioProcessor::acceptsMidi() const { return false; }
bool MultiMaidAudioProcessor::producesMidi() const { return false; }
bool MultiMaidAudioProcessor::isMidiEffect() const { return false; }
double MultiMaidAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int MultiMaidAudioProcessor::getNumPrograms() { return 1; }
int MultiMaidAudioProcessor::getCurrentProgram() { return 0; }
void MultiMaidAudioProcessor::setCurrentProgram (int) {}
const juce::String MultiMaidAudioProcessor::getProgramName (int) { return {}; }
void MultiMaidAudioProcessor::changeProgramName (int, const juce::String&) {}

void MultiMaidAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    engine.prepare (sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void MultiMaidAudioProcessor::releaseResources() {}

bool MultiMaidAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
        && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

multimaid::dsp::CompressorSettings MultiMaidAudioProcessor::readBand (const juce::String& prefix) const
{
    auto get = [this] (const juce::String& id)
    {
        return apvts.getRawParameterValue (id)->load();
    };

    multimaid::dsp::CompressorSettings s;
    s.thresholdDb = get (prefix + "Threshold");
    s.ratio       = get (prefix + "Ratio");
    s.attackMs    = get (prefix + "Attack");
    s.releaseMs   = get (prefix + "Release");
    s.kneeDb      = get (prefix + "Knee");
    s.trimDb      = get (prefix + "Trim");
    s.bypass      = get (prefix + "Bypass") > 0.5f;
    s.solo        = get (prefix + "Solo") > 0.5f;
    s.mute        = get (prefix + "Mute") > 0.5f;
    return s;
}

void MultiMaidAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ignoreUnused (midi);
    juce::ScopedNoDenormals noDenormals;

    for (int ch = getTotalNumInputChannels(); ch < getTotalNumOutputChannels(); ++ch)
        buffer.clear (ch, 0, buffer.getNumSamples());

    engine.setCrossovers (apvts.getRawParameterValue (multimaid::params::xoverLowMid)->load(),
                          apvts.getRawParameterValue (multimaid::params::xoverMidHigh)->load());
    engine.setLowSettings  (readBand ("low"));
    engine.setMidSettings  (readBand ("mid"));
    engine.setHighSettings (readBand ("high"));

    engine.process (buffer,
                    apvts.getRawParameterValue (multimaid::params::inputGain)->load(),
                    apvts.getRawParameterValue (multimaid::params::outputGain)->load(),
                    apvts.getRawParameterValue (multimaid::params::dryWet)->load());
}

bool MultiMaidAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* MultiMaidAudioProcessor::createEditor() { return new MultiMaidAudioProcessorEditor (*this); }

void MultiMaidAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void MultiMaidAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName (apvts.state.getType()))
        apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultiMaidAudioProcessor();
}
