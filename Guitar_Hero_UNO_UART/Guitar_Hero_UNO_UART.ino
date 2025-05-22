#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//Custom Color Definitions
#define ORANGE 0xFA32

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//Serial Communication Input Buffer
String DebugInput = "";
String UserInput = "";
bool handshakeSuccess = false;

//AltSoftSerial altSerial;

/* Custom Function Declarations*/
void drawLogo();
void drawMainMenu();
void drawUserSelect();


void serialEcho(String echo);
bool startupHandshake(int trylimit);




//Setup Code to run before Main Loop
void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
  tft.reset();
  uint16_t identifier = 0x9341;
  tft.begin(identifier);

  tft.fillScreen(BLACK);
  tft.setCursor(0,0);

  //TFT is 240x320 pixels (Width corresponds to short side by default)


  // Load Logo Image 
  drawLogo();

  // Perform Handshake
  handshakeSuccess = startupHandshake(3);
  if (handshakeSuccess) {
    //wait a few seconds then load main menu
    delay(3000);
    drawMainMenu();
  } else {
    //display error message on logo screen
    tft.setCursor(120, 300);
    tft.println("Error: Communication Failure");
    //Put UNO to sleep (See Arduino Low Power Library)
  }
}




//Main loop
void loop(void) {
  readSerial();
}








//Establish Connection with Daisy Seed
bool startupHandshake(int trylimit) {
  /* To be called in void setup()
  Logo can be shown on screen while UNO tries to establish
  connection with DS, will wait a bit then try 3 times to 
  connect.
  */

  // Send a start code, wait for a response from DS
  // If no response, wait then try again
  // On 3rd fail, display error on screen, 'shut down'
  // If valid response, continue as normal
  for (int i = 0; i < trylimit; i++) {
    delay(1000); //Wait 1 second
    Serial.print("/H;");  //Send Handshake
    
    int j = 1000;         //Try to receive Acknowledge a few times
    while (j > 0) {
      if (Serial.available() > 0) { //If something received, stop waiting
        if (Serial.find('/')) {
          DebugInput.concat(Serial.readStringUntil(';')); //Store received code
          return true;  //Return success
        }
      } else {j--;}
    }
  }
  // If nothing received after 3 tries, return fail state
  
  return false;
}

//Check for Serial Communications
void readSerial() {
  if (Serial.available() > 0) {
    if (Serial.find('/')) {
        UserInput.concat(Serial.readStringUntil(';'));
        decodeInput();
    }
  }
}




//Decode User Input from Daisy Seed Rotary Encoders or Serial Plotter
void decodeInput() {
  //Encoder input should be sent as a two character code '1R', '2L', '3B', ...
  //if (UserInput == "LEDON") {
  switch (UserInput[0]) {
    case '1': //Rotary Encoder 1
      //Tell UNO what encoder was used
      break;
    case '2': //Rotary Encoder 2
      //Tell UNO what encoder was used
      break;
    case '3': //Rotary Encoder 3
      //Tell UNO what encoder was used
      break;
    default:
      
      break;
  }

  switch (UserInput[1]) {
    case 'L': //Turned Left
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    case 'R': //Turned Right
      digitalWrite(LED_BUILTIN, LOW);
      break;
    case 'B': //Button

      break;
    default:  //No Input/Error
      
      break;
  }
  UserInput = "";
}

//Echo Received Serial Communications - For Debug Purposes
void serialEcho(String echo) {
  Serial.println(echo);
  //altSerial.println(echo);
}

void drawLogo() {
  tft.fillScreen(BLACK);
  tft.setCursor(0,0);

  //tft.drawBitmap();
}

void drawMainMenu() {

}

void drawUserSelect() {

}