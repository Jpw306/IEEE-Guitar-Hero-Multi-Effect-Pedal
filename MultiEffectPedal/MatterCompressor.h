#include "DaisyDuino.h"

class MatterCompressor {
  public:
    MatterCompressor() {}
    ~MatterCompressor() {}

    void Initialize();
    void Process(float inputL, float inputR, float *outL, float *outR);

  private:
    Compressor comp;
};