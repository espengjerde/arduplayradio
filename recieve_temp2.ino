//recieve both;

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
float msg;
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
	   status = radio.read(msg, 4); 
	   Serial.println("Reading temperature");
       Serial.println(status);
	   Serial.println(msg);
       digitalWrite(LED_M, LOW);
       digitalWrite(LED_B, LOW);   
    
    if(msg < 15.0){
        Serial.print("YELLOW");
        digitalWrite(LED_M,LOW);
        digitalWrite(LED_B,HIGH);
        delay(500);
        return;
    }
    if(msg < 20.0){
        Serial.print("YELLOW_AND_RED");
        digitalWrite(LED_M,HIGH);
        digitalWrite(LED_B,HIGH);
        delay(500);
        return;
    }
    if(msg > 35.0){
        Serial.print("RED");
        digitalWrite(LED_M,HIGH);
        digitalWrite(LED_B,LOW);
        delay(500);
        return;
    }
  }
}
