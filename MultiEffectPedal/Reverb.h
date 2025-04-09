#include "DaisyDuino.h"

class Reverb {
  public:
    Reverb() {}
    ~Reverb() {}

    void Initialize(float sample_rate);
    void Process(float inputL, float inputR, float *outL, float *outR);

  private:
    ReverbSc verb;
};