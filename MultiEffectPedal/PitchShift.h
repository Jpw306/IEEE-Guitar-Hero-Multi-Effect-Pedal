#include "DaisyDuino.h"

class PitchShift {
  public:
    PitchShift() {}
    ~PitchShift() {}

    void Initialize(float sample_rate);
    void Process(float inputL, float inputR, float *outL, float *outR);

  private:
    PitchShifter pitch;
    Metro tick;
    float transpose;
};