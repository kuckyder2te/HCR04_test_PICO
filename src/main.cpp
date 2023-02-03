#include <Arduino.h>
//#include <HC_SR04.h>
#include <HC_SR04.h>

#define PIN_ECHO 21
#define PIN_TRIGGER 22

HC_SR04<PIN_ECHO> sensor(PIN_TRIGGER);   // sensor with echo and trigger pin
//UltraSonicDistanceSensor distanceSensor(PIN_TRIGGER, PIN_ECHO);   // trigger / echo

int a = 0;

void setup() { 
  Serial.begin(115200); 
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);

  //sensor.beginAsync();  
  //sensor.startAsync(100000);        // start first measurement

  sensor.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);

  sensor.startMeasure();
  Serial.println(sensor.getDist_cm());

//  if (sensor.isFinished()) {
//     Serial.println(sensor.getDist_cm());
//     Serial.println(a++);
//     delay(1000);

//     sensor.startAsync(100000);
//   }
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
}


   
