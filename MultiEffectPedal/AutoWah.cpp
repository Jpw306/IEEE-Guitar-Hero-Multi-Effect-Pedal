#include "DaisyDuino.h"
#include "AutoWah.h"

void AutoWah::Process(float inputL, float inputR, float *outL, float *outR) {
  *outL = wah.Process(inputL);
  *outR = wah.Process(inputR);
}

void AutoWah::Initialize(float sample_rate) {
  wah.Init(sample_rate);
  wah.SetLevel(1);
  wah.SetDryWet(100);
  wah.SetWah(1);
}