//recieve both;

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg[1];
RF24 radio(9,53);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int LED_B = 48;
int LED_M = 49;
 
void setup(void){
	Serial.begin(9600);
	radio.begin();
	radio.openReadingPipe(1,pipe);
	radio.startListening();
	pinMode(LED_B, OUTPUT);
	pinMode(LED_M, OUTPUT);
}
 
void loop(void){
	if (radio.available()){
	   Serial.println("Radio Available");   
	   radio.read(msg, 1);
	   
	   Serial.println("Checking button and motion boards");
	   Serial.println(msg[0]);
	   
	   if (msg[0] == 111 || msg[0] == 222){
			Serial.println("temp recieved");
			if(msg[0] == 111){
				Serial.println("Temp below or eq 20C");
				Serial.println("Setting Yellow LED on");
				digitalWrite(LED_M, LOW);       //Red off
                digitalWrite(LED_B, HIGH);      //Yellow on
			}
			if(msg[0] == 222 ) {
				Serial.println("Temp above 20C");
				Serial.println("Setting Red LED on");
                digitalWrite(LED_B, LOW);           //Yellow on
				digitalWrite(LED_M, HIGH);          //Red off
			}
	   }
	}
	else {
	   Serial.println("No radio available");
	   digitalWrite(LED_B, LOW)
       digitalWrite(LED_M, LOW)
    }
}
