#include "DaisyDuino.h"
#include "Effect.h"

class AntiMatterCompressor : public Effect{
  public:
    AntiMatterCompressor();
    ~AntiMatterCompressor();

    void Initialize(float sample_rate, int mode) override;
    void Process(float inputL, float inputR, float *outL, float *outR, int mode) override;
    const char* GetName() const override;
    int GetID() const override;

  private:
    bool bypassHard = false;
    bool bypassSoft = false;

    float hardClip(float in);
    float softClip(float in);
    float gate(float in);
};