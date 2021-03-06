recieve both;

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg[1];
RF24 radio(9,53);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int LED1 = 48;
int LED2 = 49;
 
void setup(void){
	Serial.begin(9600);
	radio.begin();
	radio.openReadingPipe(1,pipe);
	radio.startListening();
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
}
 
void loop(void){
	if (radio.available()){
		Serial.println("Radio Available");   
		Serial.println("Checking button");
		radio.read(msg, 1);
		Serial.println(msg[0]);
		if(msg[0] == 111){
			Serial.println("Recieved from button board");
			Serial.println("Setting led 48 on");
			digitalWrite(LED1, HIGH);
		}
		else {
			Serial.println("no button push");
			digitalWrite(LED1, LOW);
			digitalWrite(LED2, LOW);
			Serial.println("Turn off");
		}	
	}
	else {
	   Serial.println("No radio available");
	}
}