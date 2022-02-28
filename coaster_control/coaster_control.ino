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

char sensors[4];
char zones[4];

const int SOLENOID_0 = 10;
const int SOLENOID_1 = 11;
const int SOLENOID_2 = 12;
const int SOLENOID_3 = 13;

// Sensor really refers to the IR transmitter and receiver acting in tandem (so their output)
const int SENSOR_0 = 4; // sensor 0
const int SENSOR_1 = 5; // sensor 1
const int SENSOR_2 = 6; // sensor 2
const int SENSOR_3 = 7; // sensor 3

int initial_state = 1;

void setup() {
  pinMode(SOLENOID_0, OUTPUT);
  pinMode(SOLENOID_1, OUTPUT);
  pinMode(SOLENOID_2, OUTPUT);
  pinMode(SOLENOID_3, OUTPUT);
  
  pinMode(SENSOR_0, INPUT);
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(SENSOR_3, INPUT);

  attachInterrupt(digitalPinToInterrupt(2), emergencyStop, RISING); 
  attachInterrupt(digitalPinToInterrupt(3), sensorInterrupt, FALLING); 

  // zones = "1001"; 
  // update_sensors(*sensors);

  Serial.begin(9600);
}

int emergencyStop() {
  digitalWrite(SOLENOID_0, LOW);
  digitalWrite(SOLENOID_1, LOW);
  digitalWrite(SOLENOID_2, LOW);
  digitalWrite(SOLENOID_3, LOW);

  // Currently staying in the while loop, no recovery from an emergency stop
  // TODO: Add an emergency state and set it so maybe we can return control to loop()
  while (true) {
    Serial.println("Emergency Stop Forever");
  }
}

// So do we want to just continuously read sensors OR do we want to wait until a state change in one of the sensors?
int sensorInterrupt() {

}

}
int update_zones(){
  // The zones are kind of like the previous/current state of the sensors?
  zones = sensors;
}

int update_sensors() {
  int sensor0 = digitalRead(SENSOR_0);
  int sensor1 = digitalRead(SENSOR_1);
  int sensor2 = digitalRead(SENSOR_2);
  int sensor3 = digitalRead(SENSOR_3);

  if (sensor0 == 0)
    sensors[0] = '0';
  else
    sensors[0] = '1';

  if (sensor1 == 0)
    sensor[1] = '0';
  else
    sensor[1] = '1';

  if (sensor2 == 2)
    sensor[2] = '0';
  else
    sensor[2] = '1';

  if (sensor3 == 0)
    sensor[3] = '0';
  else
    sensors[3] = '1';

  update_zones();
}

void loop() {
  update_sensors();
  
  if (initial_state) {
    if (!zones.equals("1001")) {
      // TODO: figure out how best to handle
      emergencyStop();
    } else {
      // release break to get to "1010"
      digitalWrite(SOLENOID_0); // I'm actually not too sure which solenoids correspond to which breaks
      // TODO: Figure out order of solenoids, sensors, and coaster cars 
    }
  }
  if (zones.equals("1010")) {
    // release breaks to get to "0101"
    // Try to release the "forward" car first as a bit of a safety measure
    digitalWrite(SOLENOID_1); // Not sure which solenoids correspond to which breaks
    digitalWrite(SOLENOID_3);
  }
  if (zones.equals("0101")) {
    // release break to get to "1010"
    // Try to release the "forward" car first as a bit of a safety measure
    digitalWrite(SOLENOID_0); // Not sure which solenoids correspond to which breaks
    digitalWrite(SOLENOID_2);
  }
  else {
    // add code to handle error gracefully and allow system to recover 
    // Just shutting down for now
    emergencyStop();
  }
}
