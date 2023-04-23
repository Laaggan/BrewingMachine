#include <DS18B20.h>

DS18B20 ds(2);

float operatingTemperature = 26.0;
float burnerOnPin = 3;
float temperatureReachedPin = 4;
float currentTemperature;
bool operatingTemperatureReached = false;
bool burnerOn = false;
long int time;
long int latestSwitch;
int oneMinute = 6000;

void setup() {
  Serial.begin(9600);
  pinMode(burnerOnPin, OUTPUT);
  digitalWrite(burnerOnPin, LOW);
  pinMode(temperatureReachedPin, OUTPUT);
  digitalWrite(temperatureReachedPin, LOW);
  time = millis();
  latestSwitch = 0;
}

void loop() {
 while (ds.selectNext()) {
    Serial.println(ds.getTempC());
    currentTemperature = ds.getTempC();
  }
  time = millis();

  burnerOn = currentTemperature < operatingTemperature;
  operatingTemperatureReached = currentTemperature >= operatingTemperature;

  if (operatingTemperatureReached){
    digitalWrite(temperatureReachedPin, HIGH);
  }
  else{
    digitalWrite(temperatureReachedPin, LOW);
  }

  // if (burnerOn && time - latestSwitch > oneMinute){
  if (burnerOn){
    digitalWrite(burnerOnPin, HIGH);
    latestSwitch = time;
  }
  else{
    digitalWrite(burnerOnPin, LOW);
  }
}