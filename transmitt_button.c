#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int msg[1];  
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int inputPin = 4;               // Button input
int val = 0;                    // variable for reading the pin status


void setup() {
	pinMode(inputPin, INPUT);     // declare sensor as input
	Serial.begin(9600);
	radio.begin();
	radio.openWritingPipe(pipe);
// }
 
void loop(){
	msg[0] = 111;
	val = digitalRead(inputPin);  // read input value
	if (val == HIGH) {            
		Serial.println("BBB: BUTTON Pushed");
		radio.write(msg, 1);	//send "message" to radio
	}
}