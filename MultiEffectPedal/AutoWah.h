#include "DaisyDuino.h"
#include "Effect.h"
class AutoWah : public Effect{
  public:
    AutoWah() {}
    ~AutoWah() {}

    void Initialize(float sample_rate, int mode) override;
    void Process(float inputL, float inputR, float *outL, float *outR, int mode) override;
    const char* GetName() const override;
    int GetID() const override;

  private:
    Autowah wah; 
};