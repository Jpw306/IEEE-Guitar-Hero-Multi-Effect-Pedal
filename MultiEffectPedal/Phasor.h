#include "DaisyDuino.h"
#include "Effect.h"

class Lazor : public Effect{
    public:
        Lazor() {}
        ~Lazor() {}

        void Initialize(float sample_rate, int num_filters, int mode) override;
        void Process(float inputL, float inputR, float *outL, float *outR, int mode) override;
        const char* GetName() const override;
        int GetID() const override;

    private:
        Oscillator lfo;
        float buff[9600];
        int filters;
        float l, outputL, outputR;
        size_t size;
        Allpass wire;
};