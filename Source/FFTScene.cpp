#include "../JuceLibraryCode/JuceHeader.h"


class FFTScene : public Component
{
public:
    FFTScene(const AudioSampleBuffer& lt) : lookupTable {lt}
    {
    }

    ~FFTScene()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colour(16,0,79));

        g.setColour(Colours::white);
        g.setFont(Font ("Gill Sans", 24.0f, Font::bold));
        g.drawText("Spectrum", 10, 10, 300, 40, true);
        
    }
    
    void FFT()
    {
        
    }

    void resized() override
    {
    }

private:
    AudioSampleBuffer lookupTable;
    Array<float>* bins;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFTScene)
};
