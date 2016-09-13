#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int inputPin = 4;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
	pinMode(inputPin, INPUT);     // declare sensor as input
	Serial.begin(9600);
	radio.begin();
	radio.openWritingPipe(pipe);
}
 
void loop(){
	val = digitalRead(inputPin);  // read input value
	if (val == HIGH) {            // check if the input is HIGH
	   msg[0] = 222;
	   if (pirState == LOW) {
		// we have just turned on
		Serial.println("Motion detected!");
		// We only want to print on the output change, not state
		pirState = HIGH;
	   }
	}
	else {
	   msg[0] = 221;
	   if (pirState == HIGH){
		   // we have just turned of
		   Serial.println("Motion ended!");
		   // We only want to print on the output change, not state
		   pirState = LOW;
	   }  
	}
	radio.write(msg, 1);
}