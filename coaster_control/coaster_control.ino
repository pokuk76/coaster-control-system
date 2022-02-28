/*
 * Loading - Zone 0 
 * Lift hill - Zone 1
 * Drop - Zone 2
 * Unloading - Zone 3
 */

int sensors[4];
int zones[4];


const int SOLENOID_0 = 10;
const int SOLENOID_1 = 11;
const int SOLENOID_2 = 12;
const int SOLENOID_3 = 13;

// Sensor really refers to the IR transmitter and receiver acting in tandem (so their output)
const int SENSOR_0 = 4; // sensor 0
const int SENSOR_1 = 5; // sensor 1
const int SENSOR_2 = 6; // sensor 2
const int SENSOR_3 = 7; // sensor 3

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

  zones = [1,0,0,1]; // initial state of sensors
  update_sensors(*sensors);
  

  Serial.begin(9600);
}

int emergencyStop() {
  digitalWrite(SOLENOID_0, LOW);
  digitalWrite(SOLENOID_1, LOW);
  digitalWrite(SOLENOID_2, LOW);
  digitalWrite(SOLENOID_3, LOW);
  
  while (true) {
    Serial.println("Emergency Stop Forever");
  }
}

// So do we want to just continuously read sensors OR do we want to wait until a state change in one of the sensors?
int sensorInterrupt() {

}
}
int update_zones(int *zones, int **sensor_readings){
  //
}

int update_sensors(int *sensors) {
  
}

void loop() {
  if (zone1 and zone3) {
    if (sensor_1 and sensor_3) {
      release_breaks;
    }
  }
  if (zone0 and zone2) {
    if (sensor0 and sensor2) {
      release_breaks;
    }
  }
  else {
    just_shutdown;
  }
}
