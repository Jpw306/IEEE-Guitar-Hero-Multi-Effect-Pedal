#include "DaisyDuino.h"

class AntiMatterCompressor {
  public:
    AntiMatterCompressor() {}
    ~AntiMatterCompressor() {}

    void Process(float inputL, float inputR, float *outL, float *outR);

  private:
    bool bypassHard, bypassSoft;

    float hardClip(float in);
    float softClip(float in);
    float gate(float in);
};