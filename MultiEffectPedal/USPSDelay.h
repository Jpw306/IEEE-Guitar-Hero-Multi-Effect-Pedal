#include "DaisyDuino.h"

#define MAX_DELAY static_cast<size_t>(48000 * 0.75f) // defining MAX_DELAY to 0.75*48000 hz

class USPSDelay {
  public:
    USPSDelay() {}
    ~USPSDelay() {}

    void Initialize(float sample_rate);
    void Process(float inputL, float inputR, float *outL, float *outR, int mode);

  private:
    DelayLine<float, MAX_DELAY> delL, delR; // delayline of MAX_DELAY number of floats
    Oscillator osc;
    Metro tick;
    float feedbackL, feedbackR, del_outL, del_outR, sig_outL, sig_outR;
    bool toggleOutput;
};