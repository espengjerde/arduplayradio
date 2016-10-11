//recieve both;

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <MySensor.h>

int msg[1];
RF24 radio(9,53);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int LED_B = 48;
int LED_M = 49;

MySensor gw; 


void setup(void){
//	Serial.begin(9600);
    gw.begin(incomingMessage, Auto, true);
	radio.begin();
	radio.openReadingPipe(1,pipe);
	radio.startListening();
	pinMode(LED_B, OUTPUT);
	pinMode(LED_M, OUTPUT);

}
 
void loop(void){
	if (radio.available()){
//	   Serial.println("Radio Available");   
	   radio.read(msg, 1);
	   
//	   Serial.println("Checking button and motion boards");
//	   Serial.println(msg[0]);
	   
	   if (msg[0] == 111 || msg[0] == 222){
//			Serial.println("message recieved");
			if(msg[0] == 111){
//				Serial.println("Recieved from button board");
//				Serial.println("Setting Button LED on");
				digitalWrite(LED_B, HIGH);
			}
			if(msg[0] == 222 ) {
//				Serial.println("Recieved from motion detector");
//				Serial.println("Setting Motion LED on");
				digitalWrite(LED_M, HIGH);
			}
	   }
	   else {
//			Serial.println("No motion or button push");
			if(msg[0] == 221){
				digitalWrite(LED_M, LOW);
				Serial.println("Turn off Motion LED");
			}
			if(msg[0] == 100){
				digitalWrite(LED_B, LOW);
//				Serial.println("Turn off Button LED");
			}
	   }
	}
	else {
//	   Serial.println("No radio available");
	}
}
