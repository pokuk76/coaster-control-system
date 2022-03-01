/* Loop Approach
 *  
 * Loading - Zone 0 
 * Lift hill - Zone 1
 * Drop - Zone 2
 * Unloading - Zone 3
 * 
 * Let's just represent this as a bit pattern with zone 0 being the LSB, zone 3 being the MSB
 * Only valid states (after initial state of 1001) are 1010 (10) and 0101 (5)
 */

char sensors[5];
char zones[5];

const int SOLENOID_0 = 6;
const int SOLENOID_1 = 10;
const int SOLENOID_2 = 11;
const int SOLENOID_3 = 9;

// Sensor really refers to the IR transmitter and receiver acting in tandem (so their output)
// const int SENSOR_0 = 4; // sensor 0
// const int SENSOR_1 = 5; // sensor 1
// const int SENSOR_2 = 6; // sensor 2
// const int SENSOR_3 = 7; // sensor 3

const int threshold = 64;

int initial_state = 1;

int sensor0;
int sensor1;
int sensor2;
int sensor3;

int something = 0;
void setup() {
  pinMode(SOLENOID_0, OUTPUT);
  pinMode(SOLENOID_1, OUTPUT);
  pinMode(SOLENOID_2, OUTPUT);
  pinMode(SOLENOID_3, OUTPUT);
  
  pinMode(A0, INPUT); // sensor 0
  pinMode(A1, INPUT); // sensor 1
  pinMode(A2, INPUT); // sensor 2
  pinMode(A3, INPUT); // sensor 3

//  attachInterrupt(digitalPinToInterrupt(2), emergencyStop, RISING); 
//  attachInterrupt(digitalPinToInterrupt(3), sensorInterrupt, FALLING); 

  strcpy(sensors, "1001");
  strcpy(zones, "1001");
  // update_sensors(*sensors);
  

  Serial.begin(9600);
}

void emergencyStop() {
  digitalWrite(SOLENOID_0, LOW);
  digitalWrite(SOLENOID_1, LOW);
  digitalWrite(SOLENOID_2, LOW);
  digitalWrite(SOLENOID_3, LOW);

  // Currently staying in the while loop, no recovery from an emergency stop
  // TODO: Add an emergency state and set it so maybe we can return control to loop()
  while (true) {
    Serial.print("Emergency zones: ");
    Serial.println(zones);
    Serial.println("Emergency Stop Forever");
  }
}

// So do we want to just continuously read sensors OR do we want to wait until a state change in one of the sensors?
void sensorInterrupt() {

}

void update_zones(){
  // The zones are kind of like the previous/current state of the sensors?
  if (strcmp(sensors, "1010") == 0) {
    initial_state = 0;
    strcpy(zones, "1010");    
  }  
  else if (strcmp(sensors, "0101") == 0) {
    initial_state = 0;
    strcpy(zones, "0101");
  }
  else if (!initial_state && strcmp(sensors, "1001")) {
    emergencyStop();
  }
  else if (strcmp(sensors, "1001") == 0) {
    emergencyStop();
  }
  else {
    return;
  }
}

void update_sensors() {

  sensor3 = analogRead(A3);
  sensor2 = analogRead(A2);
  sensor1 = analogRead(A1);
  sensor0 = analogRead(A0);  
  

  Serial.print("Sensor 0: ");
  Serial.print(sensor0);
  Serial.print(" | Sensor 1: ");
  Serial.print(sensor1);
  Serial.print(" | Sensor 2: ");
  Serial.print(sensor2);
  Serial.print(" | Sensor 3: ");
  Serial.println(sensor3);

  if (sensor0 > threshold)
    sensors[0] = '0';
  else
    sensors[0] = '1';

  if (sensor1 > threshold)
    sensors[1] = '0';
  else
    sensors[1] = '1';

  if (sensor2 > threshold)
    sensors[2] = '0';
  else
    sensors[2] = '1';

  if (sensor3 > threshold)
    sensors[3] = '0';
  else
    sensors[3] = '1';

  sensors[4] = '\0';

  update_zones();
}

void loop() {

  Serial.print("Current sensors state: ");
  Serial.println(sensors);
  Serial.print("Current zone state: ");
  Serial.println(zones);
  Serial.print("Initial state: ");
  Serial.println(initial_state);
  

//  digitalWrite(SOLENOID_0, HIGH); // I'm actually not too sure which solenoids correspond to which breaks
//  // TODO: Figure out order of solenoids, sensors, and coaster cars 
//  digitalWrite(SOLENOID_1, HIGH);
//  delay(1000);
//  digitalWrite(SOLENOID_0, LOW);
//  digitalWrite(SOLENOID_1, LOW);
//  delay(1000);
//  
//  digitalWrite(SOLENOID_2, LOW);
//  
//  digitalWrite(SOLENOID_3, LOW);
  
  if (initial_state) {
    if (strcmp(zones, "1001") != 0) {
      // TODO: figure out how best to handle
      Serial.println("stop in initial state check");
      emergencyStop();
    } else {
      Serial.println("Currently about to release breaks..");
      // release break to get to "1010"
      digitalWrite(SOLENOID_0, HIGH); // I'm actually not too sure which solenoids correspond to which breaks
      // TODO: Figure out order of solenoids, sensors, and coaster cars 
      digitalWrite(SOLENOID_1, LOW);
      digitalWrite(SOLENOID_2, LOW);
      digitalWrite(SOLENOID_3, LOW);
    }
  }
  else if (strcmp(zones,"0101")) {
    // release breaks to get to "0101"
    // Try to release the "forward" car first as a bit of a safety measure
    digitalWrite(SOLENOID_0, LOW);
    digitalWrite(SOLENOID_2, LOW);
    digitalWrite(SOLENOID_1, HIGH); // Not sure which solenoids correspond to which breaks
    digitalWrite(SOLENOID_3, HIGH);
  }
  else if (strcmp(zones, "1010")) {
    // release break to get to "1010"
    // Try to release the "forward" car first as a bit of a safety measure
    digitalWrite(SOLENOID_1, LOW);
    digitalWrite(SOLENOID_3, LOW);
    digitalWrite(SOLENOID_0, HIGH); // Not sure which solenoids correspond to which breaks
    digitalWrite(SOLENOID_2, HIGH);
  }
  else {
    // add code to handle error gracefully and allow system to recover 
    // Just shutting down for now
    Serial.println("stop in else block");
    emergencyStop();
  }
  update_sensors();
}
