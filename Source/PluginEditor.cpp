/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //Making GUI controls and labels visible
    addAndMakeVisible(Volume);
    addAndMakeVisible(VolumeLabel);
    addAndMakeVisible(Drive);
    addAndMakeVisible(DriveLabel);
    addAndMakeVisible(DryWet);
    addAndMakeVisible(DryWetLabel);
    addAndMakeVisible(Crunch);
    addAndMakeVisible(CrunchLabel);
    addAndMakeVisible(Size);
    addAndMakeVisible(SizeLabel);
    addAndMakeVisible(Space);
    addAndMakeVisible(SpaceLabel);
    addAndMakeVisible(DryWet2);
    addAndMakeVisible(DryWet2Label);


    //Fx 1 - Distortion GUI control parameters
    Drive.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    Drive.setValue(1.0f);
    Drive.setRange(1.0f, 10.0f, 0.01f);
    Drive.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    Drive.addListener(this);
    DriveAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRIVE", Drive);
    DriveLabel.setText("Drive", dontSendNotification);
    DriveLabel.attachToComponent(&Drive, false);

    DryWet.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    DryWet.setValue(0.0f);
    DryWet.setRange(0.0f, 1.0f, 0.01f);
    DryWet.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    DryWet.addListener(this);
    DryWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRYWET", DryWet);
    DryWetLabel.setText("DryWet", dontSendNotification);
    DryWetLabel.attachToComponent(&DryWet, false);

    Crunch.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    Crunch.setValue(1.0f);
    Crunch.setRange(1.0f, 4.5f, 0.01f);
    Crunch.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    Crunch.addListener(this);
    CrunchAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "CRUNCH", Crunch);
    CrunchLabel.setText("Crunch", dontSendNotification);
    CrunchLabel.attachToComponent(&Crunch, false);

    //Fx 2 - Reverb GUI control parameters
    Size.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    Size.setValue(1.0f);
    Size.setRange(1.0f, 10.0f, 0.01f);
    Size.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    Size.addListener(this);
    SizeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SIZE", Size);
    SizeLabel.setText("Size", dontSendNotification);
    SizeLabel.attachToComponent(&Size, false);

    DryWet2.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    DryWet2.setValue(0.0f);
    DryWet2.setRange(0.0f, 1.0f, 0.01f);
    DryWet2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    DryWet2.addListener(this);
    DryWet2Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRYWET2", DryWet2);
    DryWet2Label.setText("Dry/Wet Verb", dontSendNotification);
    DryWet2Label.attachToComponent(&DryWet2, false);

    Space.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    Space.setValue(1.0f);
    Space.setRange(1.0f, 4.5f, 0.01f);
    Space.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    Space.addListener(this);
    SpaceAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SPACE", Space);
    SpaceLabel.setText("Space", dontSendNotification);
    SpaceLabel.attachToComponent(&Space, false);




    // Vol GUI control parameters
    Volume.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Volume.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 10);
    Volume.setRange(-60.0f, 10.0f, 0.01f);
    Volume.setValue(0.0f);
    Volume.addListener(this);
    VolumeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VOL", Volume);
    VolumeLabel.setText("Volume", dontSendNotification);
    VolumeLabel.attachToComponent(&Volume, true);

    //Declaring the size of the VST window
    backgroundImage = ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);
    setSize (900, 500);
}


NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(Colours::black);
    g.drawImage(backgroundImage, getLocalBounds().toFloat());

}

void NewProjectAudioProcessorEditor::resized()
{
    //Declaring layout of various GUI parameters and controls
    Volume.setBounds(750, 100, 50, 300);

    Drive.setBounds(100, 100, 200, 100);
    DryWet.setBounds(500, 100, 200, 100);
    Crunch.setBounds(300, 100, 200, 100);

    Size.setBounds(100, 300, 200, 100);
    DryWet2.setBounds(500, 300, 200, 100);
    Space.setBounds(300, 300, 200, 100);
}

//Linking the slider values to the corresponding fx parameter values
void NewProjectAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &Volume)
    {
        audioProcessor.Vol = Volume.getValue();
    }
    if (slider == &DryWet)
    {
        audioProcessor.drywet = DryWet.getValue();
    }
    if (slider == &Crunch)
    {
        audioProcessor.crunch = Crunch.getValue();
    }
    if (slider == &Drive)
    {
        audioProcessor.drive = Drive.getValue();
    }
    if (slider == &DryWet2)
    {
        audioProcessor.drywet2 = DryWet2.getValue();
    }
    if (slider == &Size)
    {
        audioProcessor.size = Size.getValue();
    }
    if (slider == &Space)
    {
        audioProcessor.space = Space.getValue();
    }
}