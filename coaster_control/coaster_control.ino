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

void setup() {
  pinMode(SOLENOID_0, OUTPUT);
  pinMode(SOLENOID_1, OUTPUT);
  pinMode(SOLENOID_2, OUTPUT);
  pinMode(SOLENOID_3, OUTPUT);
  
  pinMode(31, INPUT);  // sensor 0
  pinMode(33, INPUT);  // sensor 1
  pinMode(35, INPUT);  // sensor 2
  pinMode(37, INPUT);  // sensor 3

  zones = [1,0,0,1];
  update_sensors(*sensors);
  

  Serial.begin(9600);
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
