#include "DaisyDuino.h"
#include "Comms.h"

/*  UPDATE TO COMM PROTOCOL
There are a few different message types being sent:
- User Input
- Stats
- Error Codes
- Acknowledge Codes
- maybe something else

For fast message decrypting, and to keep track
of what kinds of messages are being received,
 a new symbol should be added to the beginning
 of messages that denotes what type they are, 
 so that they can be immediately filtered by
 the switch case decrypter. 

  This is practical for a few reasons. Say a function 
 here is called and is expecting an acknowledge 
 message, but instead receives a stat list. Error.
 But with this system, the function can be called 
 inside the message decrypter when that particular
 message is received and then do something with it, rather 
 than precariously waiting on a specific input.

 Ex: --> "/I1R;"
  Decrypter would scan the first character, and 
  immediately know that it is a User input, and 
  then send it to the user input functions
    --> "/S----;"
  Decrypter would know this is a Stat list, and
  would immediately send it to the section that
  deals with that, rather than going through
  the whole list of cases.

  Stat Lists:
    Most effects can probably work off of a 
 generic template, but each list will need unique
 variables, and in some cases more or less parameters

 We previously went over how these could be coded, with default ranges
 of 0-999 (3 digits in message code) and code inside each individual effect 
 to figure out how that should be used. 
 Default 3 Parameters, Extra code to be dynamic when necessary.

 Pitch shift for example: Octave, Transposition.
 Ring Modulation: Carrier Wave Shape, Root Note, Loudness of Modulation
 Audio Panning: Rate of Panning, Center Direction, Range of Panning (Like all the way left/right or keep the sound centered?)
*/



//Must handle various tasks

/* 
- Startup Handshake to ensure both devices are working properly
- Confirm messages are received
- Sending User Input
- Receiving requests for an effect's stat list
- Sending an effect's stat list
- Receiving and implementing changes to an effect's stat list
*/

String parseInput() {
  
}



//Read Serial data according to our preferences, return the received string to variable that calls this function
String readSerial() {
  String message;
  if (Serial.available() > 0) {
    if (Serial.find('/')) {
        message.concat(Serial.readStringUntil(';'));
        return message;
    }
  }
}



//Decode Messages
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


//Confirm Working Communication with UNO on Startup
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
  //Since UNO is user-facing, UNO will initiate Handshake and determine whether or not to startup as normal
  //Daisy's responsibility is to receive handshake, and send aknowledge, as well as any possible error codes
  // Acknowledge = "/A;"

  //Since all Daisy has to do is listen, if Daisy does not receive anything, send error code and initiate shut-down after a time (~10 sec?)
  // If UNO is receiving, error code will let UNO know that Daisy is not receving, and this can be displayed


/* There is a question of how long should the Daisy wait to receive input? 
How would we implement this in code without interrupting other processes? */




//Send effect stats to UNO
/*void sendStats() {
  //Should this name be more descriptive?
}*/

//Receive changes to statList
void receiveStats() {
  //Should probably be called in the message decoder switch cases
}
