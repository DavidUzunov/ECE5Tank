#include <ezButton.h>


int LaserPin; //button pin to shoot the laser

//Joystick Pins
int VRX; //analog output in the x direction from the joystick
int VRY; //analog output in the y direction from the joystick
int SW=2;     //joystick button output
//pins: A1,A2,12
int x,y,s;
ezButton button(SW);

void setup() {
  // put your setup code here, to run once:
  button.setDebounceTime(50);
  VRX=A1, VRY=A2;//analog pins
  SW=8;//digital pin
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT);
  

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  button.loop();
  x = analogRead(A1);
  y = analogRead(A2);
  s = button.getState();
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("; Y: ");
  Serial.println(y);
  if (button.isPressed())
    Serial.println("; Pressed!");
  
  
  delay(100);

}
