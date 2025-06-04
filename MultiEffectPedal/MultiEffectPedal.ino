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

//Library Headers
#include <Arduino.h>
//External Library, download RotaryEncoder by Matthias Hertel
#include <RotaryEncoder.h>

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
static RingModulation DSY_SDRAM_BSS RingMod;
static AntiMatterCompressor DSY_SDRAM_BSS AMComp;
static MatterCompressor DSY_SDRAM_BSS MComp;
static Reverb DSY_SDRAM_BSS Rev;
static AutoWah DSY_SDRAM_BSS AWah;
static Lazor DSY_SDRAM_BSS Phase;

// Does not work on DSY_SDRAM_BSS
static PitchShift PShift;
static USPSDelay USPS; 

// Vector to store all effects
// Iterate across all members, check if effect is active, if so, perform effect.process
std::vector<Effect*> allEffects;

// For rotary encoder
int wrapPos = 0;
int dir = 0;

//Will need to add more of these, as well as hard-code RE1's volume functionality
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);
//RotaryEncoder RE1(PIN_IN)


void MyCallback(float **in, float **out, size_t size) {
  for (size_t i = 0; i < size; i++) {
    //float sig = osc.Process();
    float sig = in[0][i];     //For Guitar Input
    float outL = sig;
    float outR = sig;

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

  RingMod.Initialize(sample_rate, 0);
  AMComp.Initialize(sample_rate, 0);
  MComp.Initialize(sample_rate, 0);
  Rev.Initialize(sample_rate, 0);
  PShift.Initialize(sample_rate, 0);
  USPS.Initialize(sample_rate, 0);
  AWah.Initialize(sample_rate, 0);
  Phase.Initialize(sample_rate, 4, 0);

  allEffects.push_back(&Rev);
  allEffects.push_back(&USPS);
  allEffects.push_back(&AWah);
  allEffects.push_back(&Phase);
  allEffects.push_back(&PShift);
  allEffects.push_back(&RingMod);
  allEffects.push_back(&MComp);
  allEffects.push_back(&AMComp);


  SelectEffects();

  std::vector<std::string> effectsList;

  // Alter input signal
  for (auto effect : allEffects)
  {
    if (effect->active)
    {
      effect->Process(sig, sig, &outL, &outR, effect->getMode());
      effectsList.push_back(effect->GetName());
    }
  }

  Serial1.begin(9600);
  //button.Init(1000, false, 28, INPUT_PULLUP);

  DAISY.begin(MyCallback);
}
void SelectEffects(){
  selectButton.update();
  int selectedEffect = wrapPos / 2;
}
void SelectEffects(){
  selectButton.update();
  int selectedEffect = wrapPos / 2;
}

void loop(){
  //Rotary Encoder logic
  static int pos = 0;
  encoder.tick();

  int newPos = encoder.getPosition();
  if (pos != newPos) {
    dir = (int)(encoder.getDirection());
    pos = newPos;

    if(dir == 1) {
      Serial1.print("/1R;");
    }
    if(dir == -1) {
      Serial1.print("/1L;");
    }
    
    wrapPos += dir;
  }

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