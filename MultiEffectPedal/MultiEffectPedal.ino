//Effect Headers
#include "DaisyDuino.h"
#include "RingModulation.h"
#include "AntiMatterCompressor.h"
#include "MatterCompressor.h"
#include "Reverb.h"
#include "PitchShift.h"
#include "USPSDelay.h"
#include "AutoWah.h"
#include "Phasor.h"

//Communication Headers
#include "Comms.h"

//Library Headers
#include <Arduino.h>
//External Library, download RotaryEncoder by Matthias Hertel
#include <RotaryEncoder.h>

//Rotary Encoder Inputs
//RE1
#define PIN_IN1 8
#define PIN_IN2 9
//#define PIN_IN3 (For button functionality)
//RE2
//RE3
//RE4

//Stomp Switch Inputs

//For tracking position of encoder (Will probably want to set this one from 0-100 as a default, and have each effect have its own limits for specific settings)
#define MAX_POS 19
#define MIN_POS 0

using namespace std;

DaisyHardware hw;

size_t num_channels;
static Oscillator osc;

bool effect = true;
float amplitude = 1.0;

int notes[3] = {261, 329, 392};  // C Arpeggio in hz (C, E, G)
int curEffect = 0;

// Works on DSY_SDRAM_BSS
RingModulation DSY_SDRAM_BSS RingMod;
AntiMatterCompressor DSY_SDRAM_BSS AMComp;
MatterCompressor DSY_SDRAM_BSS MComp;
Reverb DSY_SDRAM_BSS Rev;
AutoWah DSY_SDRAM_BSS AWah;

// Does not work on DSY_SDRAM_BSS
PitchShift PShift;
USPSDelay USPS; 
Lazor Phase;

// For rotary encoder
int wrapPos = 0;
int dir = 0;

//Will need to add more of these, as well as hard-code RE1's volume functionality
RotaryEncoder encoder1(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);
//RotaryEncoder RE1(PIN_IN)


void MyCallback(float **in, float **out, size_t size) {
  for (size_t i = 0; i < size; i++) {
    //float sig = osc.Process();
    float sig = in[0][i];     //For Guitar Input
    float outL = sig;
    float outR = sig;

    // Alter input signal
    if(effect) {
      switch (wrapPos/2) {
        case 0:
          RingMod.Process(sig, sig, &outL, &outR);
          break;
        case 1:
          AMComp.Process(sig, sig, &outL, &outR);
          break;
        case 2:
          MComp.Process(sig, sig, &outL, &outR);
          break;
        case 3:
          Rev.Process(sig, sig, &outL, &outR);
          break;
        case 4:
          PShift.Process(sig, sig, &outL, &outR);
          break;
        case 5:
          USPS.Process(sig, sig, &outL, &outR, 0);
          break;
        case 6:
          USPS.Process(sig, sig, &outL, &outR, 1);
          break;
        case 7:
          USPS.Process(sig, sig, &outL, &outR, 2);
          break;
        case 8:
          AWah.Process(sig, sig, &outL, &outR);
          break;
        case 9:
          Phase.Process(sig, sig, &outL, &outR);
          break;
      }
    }

    // Output signal
    out[0][i] = outL;
    out[1][i] = outR;
  }
}

void setup() {
  float sample_rate;
  // Initialize for Daisy pod at 48kHz
  hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
  num_channels = hw.num_channels;
  sample_rate = DAISY.get_samplerate();

  osc.Init(sample_rate);
  osc.SetFreq(261);
  osc.SetAmp(5.0);
  osc.SetWaveform(osc.WAVE_SAW);

  RingMod.Initialize(sample_rate);
  MComp.Initialize();
  Rev.Initialize(sample_rate);
  PShift.Initialize(sample_rate);
  USPS.Initialize(sample_rate);
  AWah.Initialize(sample_rate);
  Phase.Initialize(sample_rate, 32);

  Serial1.begin(9600);
  //button.Init(1000, false, 28, INPUT_PULLUP);

  DAISY.begin(MyCallback);
}

void loop(){
  //Rotary Encoder logic
  static int pos = 0;
  encoder.tick();

  //We created a few new variables to keep track of a change in position,
  //however, the library already does that
  int newPos = encoder1.getPosition();
  if (pos != newPos) {
    dir = (int)(encoder1.getDirection());
    pos = newPos;

    if(dir == 1) {
      Serial1.print("/I1R;");
    }
    if(dir == -1) {
      Serial1.print("/I1L;");
    }
    
    wrapPos += dir; // pos and newPos aren't even used, just the direction
    //Essentially, the entire first part of this code can be removed
    //Since all we have to find out is direction
  }
//WrapPos is the value that actually gets used
  if(wrapPos < MIN_POS)
    wrapPos = MAX_POS;
  if(wrapPos > MAX_POS)
    wrapPos = MIN_POS;
}

// void playNote(int frequency, int duration) {
//   osc.SetAmp(amplitude);
//   osc.SetFreq(frequency);
//   delay(duration);
//   osc.SetAmp(0.0);
// }

// void loop() {
//   // Play note sequence
//   for(int i = 0; i < size(notes); i++) {
//     playNote(notes[i], 1000);
//     delay(1000);
//   }

//   // Delay an extra second before looping
//   delay(1000);

//   // Swap between Dry and Wet signal
//   effect = !effect;

//   // Toggle effect on/off LED
//   //analogWrite(15, effect * 255);
// }