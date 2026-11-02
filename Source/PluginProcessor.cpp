#include "PluginProcessor.h"
#include "PluginEditor.h"

LTACrystalizeAudioProcessor::LTACrystalizeAudioProcessor()
    : AudioProcessor (BusesProperties()
        .withInput ("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)) {}

bool LTACrystalizeAudioProcessor::isBusesLayoutSupported (const BusesLayout& l) const
{
    const auto& in = l.getMainInputChannelSet();
    return in == l.getMainOutputChannelSet()
        && (in == juce::AudioChannelSet::mono() || in == juce::AudioChannelSet::stereo());
}

void LTACrystalizeAudioProcessor::prepareToPlay (double, int)
{
    heldSamples.fill (0.0f);
    holdCounter = 0;
}

void LTACrystalizeAudioProcessor::processBlock (juce::AudioBuffer<float>& b, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    if (!crystalized.load()) return;
    const int channels = juce::jmin (b.getNumChannels(), 2);
    for (int s = 0; s < b.getNumSamples(); ++s)
    {
        if (holdCounter == 0)
            for (int c = 0; c < channels; ++c)
            {
                const float x = juce::jlimit (-1.0f, 1.0f, b.getSample (c, s));
                heldSamples[(size_t)c] = std::round (x * 255.0f) / 255.0f;
            }
        for (int c = 0; c < channels; ++c)
            b.setSample (c, s, heldSamples[(size_t)c]);
        holdCounter = (holdCounter + 1) % 4;
    }
}

juce::AudioProcessorEditor* LTACrystalizeAudioProcessor::createEditor()
{
    return new LTACrystalizeAudioProcessorEditor (*this);
}
void LTACrystalizeAudioProcessor::getStateInformation (juce::MemoryBlock& d)
{
    juce::MemoryOutputStream s (d, false); s.writeBool (crystalized.load());
}
void LTACrystalizeAudioProcessor::setStateInformation (const void* d, int n)
{
    if (d && n > 0) { juce::MemoryInputStream s (d, (size_t)n, false); crystalized.store (s.readBool()); }
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new LTACrystalizeAudioProcessor(); }
