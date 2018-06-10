#include "../JuceLibraryCode/JuceHeader.h"

class WFLookAndFeel: public LookAndFeel_V4
{
    public:
    
        WFLookAndFeel()
        {
            setColour (Label::textColourId, Colour (255, 255, 255));
            setColour (TextEditor::textColourId, Colour (255,255,255));
            setColour (TextEditor::backgroundColourId, Colour (16,0,79));
            setColour (TextEditor::outlineColourId, Colour (16,0,79));
            setColour (TextEditor::focusedOutlineColourId, Colour (255,255,0));
        }
    
};
