#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <dht.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

float msg[1];  
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int status = -2;

void setup() {
	Serial.begin(9600);
	radio.begin();
	radio.openWritingPipe(pipe);
	radio.stopListening ();
}
 
void loop(){
        msg[0] = dht.readTemperature();	
        Serial.println(msg[0]);
    	status = radio.write(msg, 4);
        Serial.println(status);
        delay(200);
}
