#include "DaisyDuino.h"
#include "Effect.h"

class PitchShift : public Effect {
  public:
    PitchShift() {}
    ~PitchShift() {}

    void Initialize(float sample_rate, int mode) override;
    void Process(float inputL, float inputR, float *outL, float *outR, int mode) override;
    const char* GetName() const override;
    int GetID() const override;

  private:
    PitchShifter pitch;
    Metro tick;
    float transpose;
};