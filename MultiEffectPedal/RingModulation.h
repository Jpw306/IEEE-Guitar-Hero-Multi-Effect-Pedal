#include "DaisyDuino.h"

class RingModulation {
  public:
    RingModulation() {}
    ~RingModulation() {}

    void Initialize(float sample_rate);
    void Process(float inputL, float inputR, float *outL, float *outR);

  private:
    Oscillator carrier;
    float carrier_signal;
};