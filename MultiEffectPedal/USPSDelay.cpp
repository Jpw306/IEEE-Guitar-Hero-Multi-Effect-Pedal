#include "DaisyDuino.h"
#include "USPSDelay.h"

void USPSDelay::Process(float inputL, float inputR, float *outL, float *outR, int mode) {
  del_outL = delL.Read();
  del_outR = delR.Read();
  sig_outL = del_outL + inputL;
  sig_outR = del_outR + inputR;
  feedbackL = (del_outL * 0.5f) + inputL;
  feedbackR = (del_outR * 0.5f) + inputR;

  // Write to the delay
  delL.Write(feedbackL);
  delR.Write(feedbackR);

  switch(mode) {
    // Normal Delay
    case 0:
      *outL = sig_outL;
      *outR = sig_outR;
      break;
    // Ping Pong Delay
    //Perhaps this is less delay, and more post-processing. - MA
    case 1:
      if(tick.Process()) {
        toggleOutput = !toggleOutput;
      }
      *outL = toggleOutput * sig_outL;
      *outR = !toggleOutput * sig_outR;
      break;
    // Panning Delay
    //Perhaps this is less delay, and more post-processing. - MA
    case 2:
      *outL = osc.Process() * sig_outL;
      osc.PhaseAdd(0.5);  // Phase shift for cosine
      *outR = osc.Process() * sig_outR;
      osc.PhaseAdd(0.5); // Reset phase shift
      break;
  }
}

void USPSDelay::Initialize(float sample_rate) {
  delL.SetDelay(sample_rate * 0.25f);
  delR.SetDelay(sample_rate * 0.25f);

  // Oscillator for Panning delay
  osc.Init(sample_rate);
  osc.SetFreq(0.5);
  osc.SetAmp(1.0);
  osc.SetWaveform(osc.WAVE_SIN);

  toggleOutput = true;
  tick.Init(5.0f, sample_rate);
}