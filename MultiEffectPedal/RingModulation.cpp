#include "DaisyDuino.h"
#include "RingModulation.h"

void RingModulation::Process(float inputL, float inputR, float *outL, float *outR) {
  carrier_signal = carrier.Process();
  *outL = inputL * carrier_signal;
  *outR = inputR * carrier_signal;
}

void RingModulation::Initialize(float sample_rate) {
  carrier.Init(sample_rate);
  carrier.SetFreq(311);
  carrier.SetAmp(1.0);
  carrier.SetWaveform(carrier.WAVE_SIN);
}