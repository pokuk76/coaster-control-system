

const int buttonPin = 8;     // the number of the pushbutton pin
const int solenoidOnePin = 9;      // the number of the solenoid pin
const int solenoidTwoPin = 10;


int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  pinMode(solenoidOnePin, OUTPUT);
  pinMode(solenoidTwoPin, OUTPUT);
  
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
    digitalWrite(solenoidOnePin, HIGH);
    digitalWrite(solenoidTwoPin, HIGH);
    Serial.println("Button pushed");
    Serial.println();
  } else {
    // turn LED off:
    digitalWrite(solenoidOnePin, LOW);
    digitalWrite(solenoidTwoPin, LOW);
    Serial.println("Button NOT pushed");
    Serial.println();
  }
}
