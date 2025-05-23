#include "DaisyDuino.h"
#include "Reverb.h"

void Reverb::Process(float inputL, float inputR, float *outL, float *outR) {
  verb.Process(inputL, inputR, outL, outR);
  *outL = *outL + inputL;
  *outR = *outR + inputR;
}

void Reverb::Initialize(float sample_rate) {
  verb.Init(sample_rate);
  verb.SetFeedback(0.60f);
  verb.SetLpFreq(12000.0f);
}