#include "../JuceLibraryCode/JuceHeader.h"

class Oscillator {
  
public:
    Oscillator(const AudioSampleBuffer& waveBuffer): lookupTable {waveBuffer}
    {
        
    }
    
    
    inline float getNextSample() {
        return 0.0f;
    }

private:
    const AudioSampleBuffer& lookupTable;
    
};
