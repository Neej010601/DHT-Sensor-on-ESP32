#define BLYNK_TEMPLATE_ID "TMPLw-5e-MvR" //from Blynk
#define BLYNK_DEVICE_NAME "Home Automation" //from Blynk
#define BLYNK_AUTH_TOKEN "_1LV0LXG7r6WjpPBZiZ3NvyCAraV2Iou" //from Blynk
#define BLYNK_PRINT Serial
 
 
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
 

char auth[] = BLYNK_AUTH_TOKEN;
 

char ssid[] = "Riyu_Kamboj";
char pass[] = "Rkamboj@123";
 
#define DHTPIN 4      //connect with GPIO4
#define DHTTYPE DHT11 //DHT11 sensor
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  int h = dht.readHumidity();
  int t = dht.readTemperature(); 
  if (isnan(h) || isnan(t)) { //isnan = is not a number
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V2, t); //Virtual Pin for Temp
  Blynk.virtualWrite(V3, h); //Virtual Pin for Humidity
}
 
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
dht.begin();
timer.setInterval(1000L, sendSensor);
}

void loop()
{
Blynk.run();
timer.run();
}