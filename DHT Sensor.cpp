#include <Arduino.h>
#include "DHT.h" //library for DHT

#define DHTPIN 2 //sensor connected on GPIO2 of module 
#define DHTTYPE DHT22 //sensor type DHT22

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000); //delay before starting.
  float h= dht.readHumidity(); //for humidity.
  float t= dht.readTemperature(); //for temperature in celcuis
  float f= dht.readTemperature(true); //true shows in °F
  if (isnan(h) || isnan(t) || isnan(f)){   //isnan means is not a number.
  Serial.println("Failed to Fetch the data.");
  return;
}
//print the data.
Serial.print("Humidity= ");
Serial.print(h);
Serial.print("%");
Serial.print("Temperature= ");
Serial.print(t);
Serial.print("°C");
Serial.print(f);
Serial.print("°F");
}
