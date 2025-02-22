//essential libraries
#include <ezButton.h>//used for the joystick button(used for toggling joystick modes)
//these 3 used for radio transmission
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


// Joystick Pins
int VRY1=A1; //analog output in the y direction from the joystick for left track
int VRY2=A2;//analog output in the y direction from the joystick for the right track
int SW=9;  //joystick button output
//pins: A1,2
int y;//y data var
ezButton button(SW);


RF24 radio(8, 7); // CE, CSN pins
//creates the radio object

const byte address[6] = "00001";//same 5 char address as the receiver so they can communicate

struct SendData{
  int Y1;
  int Y2;
  int B1;
  int B2;
};
SendData Transmission;
void setup() {
  Serial.begin(9600);

  if(radio.begin()){
    Serial.println("Radio.begin Succeeded!");
  }
  else{
    Serial.println("not able to begin radio");
  }
  radio.openWritingPipe(address);//designates this as a transmitter
  radio.setPALevel(RF24_PA_MIN);//power amplifier level - set based on distance between Tx and Rx components
  //change above min for sure in our case
  radio.stopListening();//stops it from listening which designates it as transmitter
}

void loop() {//code for test
  Transmission.Y1 = analogRead(VRY1);//only Y input is needed, takes in left track
  Transmission.Y2 = analogRead(VRY2);//only Y input is needed, takes in for right track
  Transmission.B1 = digitalRead(SW);//left switch - toggle state switch
  Transmission.B1 = digitalRead(SW2);//right switch - shoot button
  radio.write(&Transmission, sizeof(Transmission));//sends the transmission up to 32 bytes at a time
  delay(10);
}
