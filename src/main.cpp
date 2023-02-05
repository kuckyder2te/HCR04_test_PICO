/*
  Test Sketch for sonic sensor HCSR04
  and Sensor DHT22


  Name: HCSR_tset_PICO
  Autor: Wilhelm Kuckelsberg
  Date: 05-02-2023
*/

#include <Arduino.h>
#include <HC_SR04.h>
#include <DHT.h>
#include <DHT_U.h>

#define PIN_ECHO 21
#define PIN_TRIGGER 22

#define DHTPIN 6
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

HC_SR04<PIN_ECHO> sensor(PIN_TRIGGER);   // sensor with echo and trigger pin

DHT dht(DHTPIN, DHTTYPE);

void setup() { 
  Serial2.begin(115200); 
  Serial2.print(__DATE__);
  Serial2.print(" ");
  Serial2.println(__TIME__);

  sensor.beginAsync();  
  sensor.startAsync(100000);        // start first measurement

  dht.begin();  

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);

    if (sensor.isFinished()) {
      Serial2.println(sensor.getDist_cm());
      sensor.startAsync(100000);
    }

    float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial2.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial2.print(F("Humidity: "));
  Serial2.print(h);
  Serial2.print(F("%  Temperature: "));
  Serial2.print(t);
  Serial2.print(F("°C "));
  Serial2.print(f);
  Serial2.print(F("°F  Heat index: "));
  Serial2.print(hic);
  Serial2.print(F("°C "));
  Serial2.print(hif);
  Serial2.println(F("°F"));

  digitalWrite(LED_BUILTIN, LOW);
}


   
