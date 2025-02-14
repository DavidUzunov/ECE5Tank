// Motor A
int enA = 9;
int bacA = 8;
int forA = 7;

// Motor B
int enB = 6;
int bacB = 4;
int forB = 5;

// Function Declarations
void forward(int&, int&);
void back(int&, int&);
void stop();

void setup(){
  // Set Up Pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(forA, OUTPUT);
  pinMode(bacA, OUTPUT);
  pinMode(bacB, OUTPUT);
  pinMode(forB, OUTPUT);

  // Turn Motors Off
  digitalWrite(forA, LOW);
  digitalWrite(bacA, LOW);
  digitalWrite(bacB, LOW);
  digitalWrite(forB, LOW);
}

void loop(){
  forward(forB, bacB);
  delay(1000);
  back(forB, bacB);
  delay(1000);
  
}

void forward(int& pin1, int& pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void back(int& pin1, int& pin2) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

void stop() {
  digitalWrite(bacA, LOW);
  digitalWrite(bacA, LOW);
  digitalWrite(forB, LOW);
  digitalWrite(bacB, LOW);
}
