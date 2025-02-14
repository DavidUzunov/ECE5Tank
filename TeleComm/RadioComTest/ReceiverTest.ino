//Essential libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN pins

const byte address[6] = "00001";//match address byte on transmitter and receiver

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);//the receiver gets designated as a receiver on the same address
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {//checks if there is data that can be read
    char text[32] = "";//can read up to 32 bytes
    radio.read(&text, sizeof(text));//takes the transmission and pastes into the variable
    Serial.println(text);
  }
}
