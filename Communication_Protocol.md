# Communication Protocol for Inter-Device Communication

## To facilitate efficient and effective communication between the Arduino Uno and Daisy Seed devices, this protocol has been devised. Upon startup or a setting change of a pedal effect, the Daisy Seed will send a list of initialized or current parameters to the Uno so that the Uno may know what is currently being used and can perform operations to change settings and send this amended information back to the Daisy Seed.

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



