#include "../JuceLibraryCode/JuceHeader.h"


class ControlScene    : public Component
{
public:
    ControlScene(Slider::Listener* sliderListener, TextEditor::Listener* textListener)
    {
        volumeSlider.addListener (sliderListener);
        
        for ( int i = 0; i < numProperties; ++i)
        {
            textBoxes.add (new TextEditor);
            labels.add (new Label);  
            addAndMakeVisible (textBoxes[i]);
            addAndMakeVisible (labels[i]);
            textBoxes[i]->addListener(textListener);
            textBoxes[i]->setComponentID(names[i]);
        }
        addAndMakeVisible (volumeSlider);
    
    }

    ~ControlScene()
    {
    }

    void paint (Graphics& g) override
    {
        for (int i = 0; i != numProperties; ++i)
        {
            textBoxes[i]->setBounds (80*i,30, 75, 26);
            labels[i]->setBounds (80*i, 0, 75, 26);
            labels[i]->setText (names[i], dontSendNotification);
            textBoxes[i]->setBorder (BorderSize<int> {0,0,0,0});
        }
        volumeSlider.setBounds (0, 50, 150, 20);
        volumeSlider.setRange (0.0f,1.0f);
    }

    void resized() override
    {
    }

    
    

private:
    enum properties {freq, phase, sr, dur, parts};
    const static int numProperties = 5;
    String names[numProperties] {"Frequency", "Phase", "Samplerate", "Duration", "Partials"};
    
    OwnedArray<TextEditor> textBoxes;
    OwnedArray<Label> labels;
    Slider volumeSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlScene)
};
