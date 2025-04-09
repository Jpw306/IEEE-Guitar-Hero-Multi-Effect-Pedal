#include "DaisyDuino.h"

class Lazor{
    public:
        Lazor() {}
        ~Lazor() {}

        void Initialize(float sample_rate, int numFilters);
        void Process(float inputL, float inputR, float *outL, float *outR);

    private:
        Oscillator lfo;
        float buff[9600];
        int filters;
        float l, outputL, outputR;
        size_t size;
        Allpass wire;
};