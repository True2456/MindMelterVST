/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor : public juce::AudioProcessorEditor,
    public Slider::Listener
{
public:
    NewProjectAudioProcessorEditor(NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;



    void sliderValueChanged(Slider* slider) override;
private:

    Image backgroundImage;
    // Fx 1 - Declaring gui controls + labels for distortion
    Slider Drive;
    Label DriveLabel;
    Slider Crunch;
    Label CrunchLabel;
    Slider DryWet;
    Label DryWetLabel;

    // Fx 2 - Declaring gui controls + labels for the reverb function
    Slider Size;
    Label SizeLabel;
    Slider Space;
    Label SpaceLabel;
    Slider DryWet2;
    Label DryWet2Label;

    //Volume - Declaring volume gui control and label
    Slider Volume;
    Label VolumeLabel;

    //Volume - Linking Apvts to volume control to allow for DAW to control automation of parameters
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> VolumeAttachment;

    //Fx 1 - Linking Apvts to reverb controls to allow for DAW to control automation of parameters
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> DriveAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> CrunchAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> DryWetAttachment;

    // Fx 2 - linking Apvts to distortion controls to allow for DAW to control automation of parameters
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> SizeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> SpaceAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> DryWet2Attachment;


    NewProjectAudioProcessor& audioProcessor;


public:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewProjectAudioProcessorEditor)
};