#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <dht.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

struct msg_t {
  float temperature;
  float humidity;
};
msg_t msg;

void setup() {
	Serial.begin(9600);
	radio.begin();
	radio.openWritingPipe(pipe);
	radio.stopListening ();
}
 
void loop(){
        float temp = dht.readTemperature();	
        float hum = dht.readHumidity();
        msg (msg_t){temp,hum};
        Serial.println(msg);
        radio.write(&msg, sizeof(msg);
}
