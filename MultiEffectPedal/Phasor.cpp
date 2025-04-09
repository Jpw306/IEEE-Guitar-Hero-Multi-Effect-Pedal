#include "DaisyDuino.h"
#include "Phasor.h"

void Lazor::Process(float inputL, float inputR, float *outL, float *outR) {
    l = 0.05 + lfo.Process();
    wire.SetFreq(l);
    //float output = input;
    //for(int i = 0; i < filters; i++) {
    //    output = wire.Process(output);
    //}
    outputL = wire.Process(inputL);
    outputR = wire.Process(inputR);
    *outL = inputL + outputL;
    *outR = inputR + outputR;
}

void Lazor::Initialize(float sample_rate, int numFilters){
    filters = numFilters; 
    lfo.SetWaveform(lfo.WAVE_SIN);
    lfo.SetFreq(1);
    lfo.SetAmp(0.01);
    for(int i = 0; i < 9600; i++) {
        buff[i] = 0.0f;
    }
    wire.Init(sample_rate, buff, (int)9600);
}