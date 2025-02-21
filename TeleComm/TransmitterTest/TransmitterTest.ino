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
  int transmission[2];//test transmission with joystick data
  bool t2;//button transmission
  y = analogRead(VRY1);//only Y input is needed, takes in right track
  transmission[0] = y;
  y = analogRead(VRY2);//only Y input is needed, takes in for right track
  transmission[1] = y;
  radio.write(&transmission, sizeof(transmission));//sends the transmission up to 32 bytes at a time
  
  if(digitalRead(SW)!=HIGH){//if the button is pressed, send a transmission for the button
    t2 = digitalRead(SW);
    Serial.println("Button Pressed!");
    radio.write(&t2, sizeof(t2));//sends the transmission up to 32 bytes at a time
  }
  delay(10);
}
