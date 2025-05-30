/*Communication Protocol for Arduino UNO with Daisy Seed.
This file will need to be incorporated into a master file for 
the UNO when it is complete. This file focuses on defining
and optimizing a UNO side comm protocol in coordination with
a Daisy Seed side comm protocol.*/

//For startup handshake purposes, may be deleted later
//bool handshakeSuccess = false;

//Function declarations, will need to be moved to .h file
String readSerial();
void serialEcho(String echo);
void decodeInput();

//Setup Code to run before Main Loop
void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

/*Rather than directly drawing grapchics from Comm protocol, 
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
  readSerial();
}


//Check for Serial Communications, Return received message
String readSerial() {
  String message;
  if (Serial.available() > 0) {
    if (Serial.find('/')) {
        message.concat(Serial.readStringUntil(';'));
        return message;
    }
  }
}


//Establish Connection with Daisy Seed
void estConn() {
  // To be called in void setup()
  //Logo can be shown on screen while UNO tries to establish
  //connection with DS, will wait a bit then try 3 times to 
  //connect.

  // Send a start code, wait for a response from DS
  // If no response, wait then try again
  // On 3rd fail, tell Graphics Protocol to display error message
  // If valid response, continue as normal

  //Message Container
  String ConnMessage = "";

  //try 3 times to establish connection
  for (int i = 3; i > 0; i--) {
    delay(1000); //Wait 1 second
    Serial.print("/H;");  //Send Handshake
    
    int j = 1000; //Try to receive Acknowledge a few times
    while (j > 0) {
      ConnMessage = readSerial();
      if (ConnMessage != "") {
        decodeM(); 
      } else {j--;}
      //since decodeM will handle the content of the message, 
      //this function doesn't need to return anything.
    }
  }
  // If nothing received after 3 tries, call function
  //in error section of decodeM
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


