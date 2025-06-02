/*Communication Protocol for Arduino UNO with Daisy Seed.
This file will need to be incorporated into a master file for 
the UNO when it is complete. This file focuses on defining
and optimizing a UNO side comm protocol in coordination with
a Daisy Seed side comm protocol.*/

#include "Comms.h"


//Global Variable Declarations
String Message = ""; //Main message container

//Setup Code to run before Main Loop
void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

/*Rather than directly drawing graphics from Comm protocol, 
  Comm Protocol should post messages, and the Graphics
  Protocol can decide what to draw from there. For example...

  On startup UNO will initiate a handshake procedure with
  Daisy Seed to make sure everything is working, and while
  this happens, should display a startup sequence logo on the
  LCD. It can do this by "posting a message" that the Graphics
  Protocol will then read and perform this action with.

  When the handshake is complete, a message can be posted to tell
  the Graphics Protocol to display menu as normal.

  The LCD runs asynchronously, and will keep whatever's on the 
  screen until told to do otherwise. The message system would be 
  efficient because it would only force the LCD to update when
  a new message is posted, rather than having code to constantly
  chack whether an update is required. Messages should not describe 
  graphical content, but rather directions to be followed. However, 
  these directions will probably depend on previous messages as well?
  */

/*
  // Perform Handshake, Will probably want to reorganize this
  handshakeSuccess = startupHandshake(3);
  if (handshakeSuccess) {
    //Send message to Load Logo Image 
    //Begin Handshake
    //wait a few seconds, confirm response, or error
    //drawMainMenu(); Post message to draw main menu as normal
  } else {
    //send message to display error message on logo screen
    //Put UNO to sleep? (See Arduino Low Power Library)
  }
}
*/



//Main loop
void loop(void) {
  Message = readSerial();
}


