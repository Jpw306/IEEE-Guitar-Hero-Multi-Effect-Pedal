#include "DaisyDuino.h"
#include "Effect.h"

class RingModulation : public Effect {
  public:
    RingModulation() {}
    ~RingModulation() {}

    void Initialize(float sample_rate, int mode) override;
    void Process(float inputL, float inputR, float *outL, float *outR, int mode) override;
    const char* GetName() const override;
    int GetID() const override;

  private:
    Oscillator carrier;
    float carrier_signal;
};

