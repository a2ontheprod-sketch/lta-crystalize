#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class LTACrystalizeAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit LTACrystalizeAudioProcessorEditor (LTACrystalizeAudioProcessor&);
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    void timerCallback() override;
    void startAnimation();
    LTACrystalizeAudioProcessor& processor;
    juce::TextButton button { "CRYSTALISE" };
    float progress = 1.0f;
    bool animating = false;
    double startMs = 0.0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTACrystalizeAudioProcessorEditor)
};
