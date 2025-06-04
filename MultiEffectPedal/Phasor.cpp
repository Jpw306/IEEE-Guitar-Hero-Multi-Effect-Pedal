#include "DaisyDuino.h"
#include "Phasor.h"

void Lazor::Process(float inputL, float inputR, float *outL, float *outR) {
    l = 0.01 + lfo.Process();
    wire.SetFreq(l);
    outputL = inputL;
    outputR = inputR;
    for(int i = 0; i < filters; i++) {
        outputL = wire.Process(outputL);
        outputR = wire.Process(outputR);
    }
    *outL = outputL;
    *outR = outputR;
}

void Lazor::Initialize(float sample_rate, int numFilters, int mode){
    filters = numFilters; 
    lfo.SetWaveform(lfo.WAVE_SIN);
    lfo.SetFreq(1);
    lfo.SetAmp(0.02);
    for(int i = 0; i < 9600; i++) {
        buff[i] = 0.0f;
    }
    wire.Init(sample_rate, buff, (int)9600);
}

const char* Lazor::GetName() const {
    return "Lazor";
}

int Lazor::GetID() const {
    return 4;
}