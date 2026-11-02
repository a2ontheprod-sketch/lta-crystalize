#pragma once
#include <JuceHeader.h>

class LTACrystalizeAudioProcessor : public juce::AudioProcessor
{
public:
    LTACrystalizeAudioProcessor();
    void prepareToPlay (double, int) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout&) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "LTA Crystalize"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}
    void getStateInformation (juce::MemoryBlock&) override;
    void setStateInformation (const void*, int) override;
    bool isCrystalized() const noexcept { return crystalized.load(); }
    void setCrystalized (bool b) noexcept { crystalized.store(b); }
private:
    std::atomic<bool> crystalized { false };
    std::array<float, 2> heldSamples { 0.0f, 0.0f };
    int holdCounter = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTACrystalizeAudioProcessor)
};
