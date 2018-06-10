#include "../JuceLibraryCode/JuceHeader.h"


#include "Oscillator.cpp"
#include "VisualScene.cpp"
#include "FFTScene.cpp"
#include "ControlScene.cpp"
#include "WFLookAndFeel.cpp"

class MainContentComponent   : public AudioAppComponent, public Slider::Listener, public TextEditor::Listener
{
public:
    MainContentComponent(): oscillator {waveTable}
    {
        setLookAndFeel(&lookAndFeel);
        addAndMakeVisible(&visScene);
        addAndMakeVisible(&fftScene);
        addAndMakeVisible(&ctrlScene);
        setSize (800, 600);
        

        wavetableSize = 128;
        waveTable.setSize(1, wavetableSize);
        createWaveTable();        setAudioChannels (0, 2);
    }

    ~MainContentComponent()
    {
        setLookAndFeel(nullptr);
        shutdownAudio();
    }

    inline void updateFreq()
    {
        increment = frequency * wavetableSize / currentSamplerate;
        phase = fmod (phase + increment, wavetableSize);
    }
    
    // Create wavetable samplebuffer
    inline void createWaveTable() {
        auto samples = waveTable.getWritePointer(0);
        
        for ( int i = 0; i < waveTable.getNumSamples(); ++i)
        {
            samples[i] = std::sin(6.28*i);
        }
    }
    
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {

        frequency.store (440.0f);
        phase.store(0.0f);
        currentSamplerate = sampleRate;
        amplitude.store (0);
        
        
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        

        // Get writepointers for left and right channels
        float* const leftChannel = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
        float* const rightChannel = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    
        // Read the wavetable data into the buffer
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            leftChannel[sample] = oscillator.getNextSample() * amplitude.load();
            rightChannel[sample] = oscillator.getNextSample() * amplitude.load();
            
            updateFreq();
            
        }
    }

    void releaseResources() override
    {

    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colour {6,3,33});

    }

    void resized() override
    {
        
        Rectangle<int> area {getLocalBounds()};
        int boxes {getHeight()/3};
        int margin {5};
        
        visScene.setBounds (area.removeFromTop (boxes).reduced (margin));
        fftScene.setBounds (area.removeFromTop (boxes).reduced (margin));
        ctrlScene.setBounds (area.removeFromTop (boxes).reduced (margin));
        
    }
    
    void setFrequency(double f)
    {
        frequency = f;
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        amplitude.store(0.25f * slider->getValue());
    }

    
    void textEditorReturnKeyPressed (TextEditor& textbox) override
    {
        if (!textbox.isEmpty())
        {
            float temp = textbox.getText().getFloatValue();
            if (textbox.getComponentID() == "Frequency")
            {
                frequency.store(temp);
            }
            
        }
    }
    

private:
    
    Oscillator oscillator;
    AudioSampleBuffer waveTable;
    int wavetableSize;
    std::atomic<float> frequency;
    std::atomic<float> phase;
    std::atomic<float> amplitude;
    double increment;
    int currentSamplerate;
    Value sliderValue;
    

    
    WFLookAndFeel lookAndFeel;
    
    VisualScene visScene {waveTable};
    FFTScene fftScene {waveTable};
    ControlScene ctrlScene {this, this};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


Component* createMainContentComponent()     { return new MainContentComponent(); }
