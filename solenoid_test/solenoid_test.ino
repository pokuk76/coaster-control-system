

const int buttonPin = 8;     // the number of the pushbutton pin
const int solenoid0Pin = 6;      // the number of the solenoid pin
const int solenoid1Pin = 9;
const int solenoid2Pin = 10;
const int solenoid3Pin = 11;


int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
//  pinMode(solenoid0Pin, OUTPUT);
//  pinMode(solenoid1Pin, OUTPUT);
  pinMode(solenoid2Pin, OUTPUT);
//  pinMode(solenoid3Pin, OUTPUT);
  
  pinMode(buttonPin, INPUT);  // i guess button
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
//    digitalWrite(solenoid0Pin, HIGH);
//    digitalWrite(solenoid1Pin, HIGH);
    digitalWrite(solenoid2Pin, HIGH);
//    digitalWrite(solenoid3Pin, HIGH);
    Serial.println("Button pushed");
    Serial.println();
  } else {
    // turn LED off:
//    digitalWrite(solenoid0Pin, LOW);
//    digitalWrite(solenoid1Pin, LOW);
    digitalWrite(solenoid2Pin, LOW);
//    digitalWrite(solenoid3Pin, LOW);
    Serial.println("Button NOT pushed");
    Serial.println();
  }
//  digitalWrite(solenoid0Pin, HIGH);
//  digitalWrite(solenoid1Pin, HIGH);
//  digitalWrite(solenoid2Pin, HIGH);
//  digitalWrite(solenoid3Pin, HIGH);
//  delay(5);
//  digitalWrite(solenoid0Pin, LOW);
//  digitalWrite(solenoid1Pin, LOW);
//  digitalWrite(solenoid2Pin, LOW);
//  digitalWrite(solenoid3Pin, LOW);
//  delay(15);
}
