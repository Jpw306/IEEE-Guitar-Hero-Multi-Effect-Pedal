#include "DaisyDuino.h"
#include "MatterCompressor.h"

void MatterCompressor::Process(float inputL, float inputR, float *outL, float *outR) {
  *outL = comp.Process(inputL) * 0.2;
  *outR = comp.Process(inputR) * 0.2;
}

void MatterCompressor::Initialize(float sample_rate, int mode) {
  comp.SetThreshold(-64.0f); //compresses sound above -64dB
  comp.SetRatio(2.0f); //compression ratio 2:1
  comp.SetAttack(0.005f); 
  comp.SetRelease(0.1250);
  setMode(mode)
}

const char* MatterCompressor::GetName() const {
    return "MatterCompressor";
}

int MatterCompressor::GetID() const {
    return 3;
}