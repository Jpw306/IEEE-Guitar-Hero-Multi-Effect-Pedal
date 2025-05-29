#include "DaisyDuino.h"
#include "_Communication.h"

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

 Ex: --> "/U1R;"
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

//Confirm Working Communication with UNO on Startup
bool Handshake() {
  //Since UNO is user-facing, UNO will initiate Handshake and determine whether or not to startup as normal
  //Daisy's responsibility is to receive handshake, and send aknowledge, as well as any possible error codes
  // Acknowledge = "/A;"

  //Since all Daisy has to do is listen, if Daisy does not receive anything, send error code and initiate shut-down after a time (~10 sec?)
  // If UNO is receiving, error code will let UNO know that Daisy is not receving, and this can be displayed
}

/* There is a question of how long should the Daisy wait to receive input? 
How would we implement this in code without interrupting other processes? */


//Will this return type work?
//Read Serial data according to our preferences, return the received string to variable that calls this function
String readSerial() {

}


//Send effect stats to UNO
void sendStats( stats_to_send) {
  //Should this name be more descriptive?
}

//Receive changes to statList
void receiveStats() {
  //Should probably be called in the message decoder switch cases
}
