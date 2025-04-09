#include "DaisyDuino.h"

class AutoWah {
  public:
    AutoWah() {}
    ~AutoWah() {}

    void Initialize(float sample_rate);
    void Process(float inputL, float inputR, float *outL, float *outR);

  private:
    Autowah wah; 
};