# Communication Protocol for Inter-Device Communication

### To facilitate efficient and effective communication between the Arduino Uno and Daisy Seed devices, this protocol has been devised. Upon startup or a setting change of a pedal effect, the Daisy Seed will send a list of initialized or current parameters to the Uno so that the Uno may know what is currently being used and can perform operations to change settings and send this amended information back to the Daisy Seed.

## User Input

In this device package, User Input is received in a select few ways: Rotary Encoder, or Buttons. When the User interacts with a Rotary Encoder, they have 3 options. They may turn it clockwise, counter-clockwise, or push it as a button. These inputs will be read by the Daisy Seed and relayed to the Arduino Uno for UI navigation purposes. 

For the purpose of inter-device communication, certain codes will be assigned to User Input actions. Each Rotary Encoder will be assigned a number designation, from left to right, with the leftmost encoder being #1. To relay that a user has turned encoder 1 to the right, the code "1R" will be sent. Below are some examples, where "X" is used as a placeholder for the encoder's designated number.

Encoder turned to the Right: "XR"

Encoder turned to the Left: "XL"

Encoder push as a button: "XP"

These codes will be sent to the UNO so that it may map the User's position in the UI and use the input to enact setting changes in Front-End menus.

## Message Transmission

Coded messages like the ones above are transmitted using the UART channels on the UNO and Daisy Seed. To facilitate proper reception of such codes, and even error detection, special characters are added to the code to signal to the devices when they should start reading and stop reading the serial stream. A forward slash ("/") is used to start, and a semicolon (";") is used to end. For special cases of multiple codes being sent all at once, a comma (",") is used to separate them. Below is an example of a User Input from Encoder 1 being sent:

"/1R"

On the receiving side, the device will automatically remove the slash and semicolon when reading the message, and from there a series of switch cases determine what the message is and how it should be used.

## Audio Effect Info Lists

Each time the user opens a menu for an audio efect, the Daisy Seed must send a list to the UNO so that the UNO can know what the current audio effect's settings are, and so that it can perform arithmetic based on the User Input.

This list defines what parameters will be sent in the communique when opening the menu for a pedal effect:

P1_XXX	Initial Value for Parameter 1

P2_XXX	Initial Value for Parameter 2

P3_XXX	Initial Value for Parameter 3

MN1_XXX	Minimum Value for Parameter 1

MX1_XXX	Maximum Value for Parameter 1

MN2_XXX	Minimum Value for Parameter 2

MX2_XXX	Maximum Value for Parameter 2

MN3_XXX	Minimum Value for Parameter 3

MX3_XXX	Maximum Value for Parameter 3

##### *Note: Minimum and Maximum Value for Master Volume will always be 0 and 100 respectively and will not be sent because of this.

#####  Example:

Daisy Seed	-->	“/P1_XXX,P2_XXX,P3_XXX,MN1_XXX,MX1_XXX,
MN2_XXX,MX2_XXX,MN3_XXX,MX3_XXX;”

Arduino Uno	-->	“/Received;”	(For Error Handling Purposes)

Daisy Seed	-->	“/1R;”		(Upon setting change)

Arduino Uno:		Will perform calculations based on input (R = +1)

Arduino Uno	--> “/SET P1_XXX;”



