#include "../JuceLibraryCode/JuceHeader.h"


class VisualScene    : public Component
{
public:
    VisualScene(const AudioSampleBuffer& lt) : lookupTable {lt}
    {
    }

    ~VisualScene()
    {
    }

    void paint (Graphics& g) override
    {

        g.fillAll (Colour {16,0,79});

        g.setColour (Colours::white);
        g.setFont (Font ("Gill Sans", 28.0f, Font::bold));
        g.drawText ("Circline", 10, 0, 300, 40, true);
        
        g.setColour (Colour {69,0,255});
        setPlot();
        g.strokePath (plot, PathStrokeType (3.0f));
    }
    
    // Draw the audio plot
    void setPlot()
    {
        plot.clear();
        
        auto xmax {static_cast<float>(getLocalBounds().getWidth())};
        auto ymax {static_cast<float>(getHeight())};
        
        auto lookupTableSize = lookupTable.getNumSamples();
        
        plot.startNewSubPath(0,ymax/2);
        int i = 0;
        auto samples = lookupTable.getReadPointer(0);
        for (int p = 0; p < lookupTableSize; ++p) {
            plot.lineTo(i*xmax/lookupTableSize,samples[p] * ymax/2+ymax/2);
            ++i;
        }
    }
    
    void resized() override
    {
        
    }
    


private:
    
    const AudioSampleBuffer& lookupTable;
    Path plot;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualScene)
};
