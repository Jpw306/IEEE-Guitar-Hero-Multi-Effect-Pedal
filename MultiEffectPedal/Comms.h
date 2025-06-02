#include "DaisyDuino.h"

//Check for Serial Communications, Return received message
String readSerial() {
  String message;
  if (Serial.available() > 0) {
    if (Serial.find('/')) {
        message.concat(Serial.readStringUntil(';'));
        return message;
    }
  } return ""; //Return an empty string if no message
}



//Establish Connection with Ardunio UNO
void estConn() {
  // To be called in void setup()
  //try to connect with UNO, receive Start message from UNO
  // Send an Acknowledge, wait for a response from UNO
  // If no response, wait then try again
  // On 3rd fail, tell UNO it can send but not receive
  // If UNO receives that message, it will know that only one 
  // comm line is broken
  // If valid response received, continue as normal

  //Handshake Message Container
  String ConnMessage = "";

  //try 3 times to establish connection
  for (int i = 3; i > 0; i--) {
    delay(1000); //Wait 1 second
    //Serial.print("/H;");  //Send Handshake
    
    int j = 1000; //Try to receive Start a few times
    while (j > 0) {
      ConnMessage = readSerial();
      if (ConnMessage != "") {
        decodeM(ConnMessage); 
      } else {j--;}
      //since decodeM will handle the content of the message, 
      //this function doesn't need to return anything.
    }
  }
  // If nothing received after 3 tries, call function
  //in error section of decodeM

  //Will need an error list in documentation
  //With this protocol, there are generally 3 areas of failure:
  //1. Completely broken communication, i.e. neither being able to send/receive
  //2. DS can receive, but UNO can't receive
  //3. UNO can receive, but DS can't receive
  
  //In 2's case, the UNO will show an error, but the DS will not
  //In 3's case, the DS can send a handshake request, and then start beeping
  // This will let the UNO know that it is receiving properly, but the DS is not
  // Beeping will notify user that this is the case
}



//Decode User Input from Daisy Seed Rotary Encoders or Serial Plotter
void decodeM(String message) {
  //Encoder input should be sent as a two character code '1R', '2L', '3B', ...
  //if (UserInput == "LEDON") {

  //Decode 1st Character, used to determine what kind of message received
  switch (message[0]) {
    //Cases should be sorted in frequency order (Most frequent actions at top)
    case 'UI': //Consider changing to just 'U' or just 'I'. Or leave as is for clarity
      //send to another switch statement to figure out what the user input was, see old test code below
      break;
    case 'E': //Error code, UART is working but something else isn't (I dunno what but...)
      //Tell LCD to display an error message
    case 'A': //Acknowledge Code. Will probably only run once, so put at bottom.
      //estConn success, tell the world!
      break;
  }
  
  /* Old Test code, use as template
  switch (message[0]) {
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

  switch (message[1]) {
    case 'L': //Turned Left
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    case 'R': //Turned Right
      digitalWrite(LED_BUILTIN, LOW);
      break;
    case 'P': //Push

      break;
    default:  //No Input/Error
      
      break;
  }*/
}