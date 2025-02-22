//essential libraries
#include <ezButton.h>  //used for the joystick button(used for toggling joystick modes)
//these 3 used for radio transmission
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


// Joystick Pins
int VRY1 = A1;  //analog output in the y direction from the joystick for left track
int VRY2 = A2;  //analog output in the y direction from the joystick for the right track
int SW = 9;     //joystick button output
int SW2 = 10;
//pins: A1,2
ezButton button(SW);
ezButton button2(SW2);
bool press = 1;  //button state tracking

RF24 radio(8, 7);  // CE, CSN pins
//creates the radio object

const byte address[6] = "00001";  //same 5 char address as the receiver so they can communicate
int prevState;                    //used for button 1, checks if the previous state matches current state to toggle controller modes
struct SendData {
  int Y1;
  int Y2;
  bool Button1 = 1;
  bool Button2 = 1;
};
SendData Transmission;
void setup() {
  Serial.begin(9600);

  if (radio.begin()) {
    Serial.println("Radio.begin Succeeded!");
  } else {
    Serial.println("not able to begin radio");
  }
  radio.openWritingPipe(address);  //designates this as a transmitter
  radio.setPALevel(RF24_PA_MIN);   //power amplifier level - set based on distance between Tx and Rx components
  //change above min for sure in our case
  radio.stopListening();  //stops it from listening which designates it as transmitter

  button.setDebounceTime(50);  // set debounce time to 50 milliseconds
  button2.setDebounceTime(50);
}

void loop() {                          //code for test
  button.loop();                       // MUST call the loop() function first
  Transmission.Y1 = analogRead(VRY1);  //only Y input is needed, takes in left track
  Transmission.Y2 = analogRead(VRY2);  //only Y input is needed, takes in for right track
  if (button.isPressed()) {
    //TODO: One issue with this line is that the button doesn't want to switch to 0 unless you briefly hold it
    Transmission.Button1 = digitalRead(SW);
  }
  Transmission.Button2 = digitalRead(SW2);           //right switch - shoot button
  radio.write(&Transmission, sizeof(Transmission));  //sends the transmission up to 32 bytes at a time
  delay(10);
}
