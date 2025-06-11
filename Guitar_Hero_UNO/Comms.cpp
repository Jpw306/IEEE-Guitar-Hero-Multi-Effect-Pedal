
#include<Arduino.h>
#include "Comms.h"

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



//Establish Connection with Daisy Seed
String estConn() {
  //Try 3 times to establish connection with DS
  
  // Send a start code, wait for a response from DS
  // On 3rd fail, tell Graphics Protocol to display error message
  // If valid response, continue as normal

  //Handshake Message Container
  String ConnMessage = "";

  //try 3 times to establish connection
  for (int i = 3; i > 0; i--) {
    delay(1000); //Wait 1 second
    Serial.print("/H;");  //Send Handshake
    
    int j = 1000; //Try to receive Acknowledge a few times
    while (j > 0) {
      ConnMessage = readSerial();
      if (ConnMessage != "") {
        return ConnMessage; //If message received, return
      } else {j--;}
    }
  }
  // If nothing received after 3 tries, return error message
  return "/E0;"; //Error Message 0, total failure in comunication between devices
}



//Decode User Input from Daisy Seed Rotary Encoders or Serial Plotter
void decodeM(String m) { //maybe pass message by reference? Message could be received, immediately decoded/used, then on next loop received again
  //Encoder input should be sent as a two character code '1R', '2L', '3B', ...
  //if (UserInput == "LEDON") {

  // Format: Type, xx, xx, xx

  //Decode 1st Character, used to determine what kind of message received
  switch (m[0]) {
    //Cases should be sorted in frequency order (Most frequent actions at top)
    case 'I': //I for Input
      //Find out what UI was, do something
      //Format: Type, Encoder #, Action
      //Perhaps a more efficient code could be devised?
      switch (m[1]) {
        case '1': //Rotary Encoder 1
          switch (m[2]) {
            case 'L':

              break;
            case 'R':

              break;
            case 'P':

              break;

            default:
              break;
          }
          break;
        case '2': //Rotary Encoder 2
          switch (m[2]) {
            case 'L':

              break;
            case 'R':

              break;
            case 'P':

              break;
              
            default:
              break;
          }
          break;
        case '3': //Rotary Encoder 3
          switch (m[2]) {
            case 'L':

              break;
            case 'R':

              break;
            case 'P':

              break;
              
            default:
              break;
          }
          break;

        default:

          break;
      }
      break;

    case 'E': //Error code, UART is working but something else isn't (I dunno what but...)
      //Find out what's wrong, Tell LCD to display an error message.
      switch (m[1]) {
        case '0':
          //call graphics to display error message and short description
          break;

        default:
          break;
      }

    case 'A': //Acknowledge Code. Will probably only run once, so put at bottom.
      //estConn success, tell the world!
      //Boot up as normal
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