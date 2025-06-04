#include "DaisyDuino.h"

//Parse User Input into message format
String parseInput();

//Check for Serial Communications, Return received message
String readSerial();

//Decode Messages
void decodeM(String message);

//Establish Connection with Ardunio UNO
void estConn();


//Send effect stats to UNO
void sendStats(stats_to_send);

//Receive changes to statList
void receiveStats();