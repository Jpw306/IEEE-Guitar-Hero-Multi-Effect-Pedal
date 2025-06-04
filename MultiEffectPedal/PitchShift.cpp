#include "DaisyDuino.h"
#include "PitchShift.h"

void PitchShift::Process(float inputL, float inputR, float *outL, float *outR) {
  if(tick.Process()) {
    pitch.SetTransposition(transpose);
    transpose = transpose + 1;

    if(transpose > 20) {
      transpose = 0;
    }
  }

  *outL = pitch.Process(inputL) + inputL;
  *outR = pitch.Process(inputR) + inputR;
}


void PitchShift::Initialize(float sample_rate, int mode) {
  transpose = 0.0;

  pitch.Init(sample_rate);
  pitch.SetTransposition(transpose);
  tick.Init(5.0f, sample_rate);
}

const char* PitchShift::GetName() const {
    return "Pitch Shift";
}

int PitchShift::GetID() const {
    return 5;
}