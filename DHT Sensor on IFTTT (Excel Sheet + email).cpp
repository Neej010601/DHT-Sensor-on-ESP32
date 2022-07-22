#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4
//our sensor is DHT11 type
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid ="Neej";
const char* pass= "124567890";

String server = "https://maker.ifttt.com";
String eventName= "test_sensor" ;
String eventName30= "test_sensor30" ;
String IFTTT_Key= "bbdasdbiqdbqihdfwbdikfbwivfiwgdbowidbweuivfiuwvfuiwfv";
String IFTTT_Url= "https://maker.ifttt.com/trigger/test_sensor/with/key/bbdasdbiqdbqihdfwbdikfbwivfiwgdbowidbweuivfiuwvfuiwfv";
String IFTTT_Key30= "bbdasdbiqdbqihdfwbdikfbwivfiwgdbowidbweuivfiuwvfuiwfv";
String IFTTT_Url30= "https://maker.ifttt.com/trigger/test_sensor30/with/key/bbdasdbiqdbqihdfwbdikfbwivfiwgdbowidbweuivfiuwvfuiwfv";
int value1;
int value2;

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.println(" ");
  }
  Serial.println("Connected....");
}

void sendDataToSheet(void){
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1" + String((int)value1) + "?value2" + String((int)value2);
  Serial.println(url);
  HTTPClient http;
  http.begin(url); //HTTP
  Serial.print("[HTTP] Get...\n");
  // start connection and send HTTP header
  int httpCode =http.GET();
    // httpCode will be negative on error
  if (httpCode > 0){
    Serial.printf("[HTTP] Get..... Code: %d\n", httpCode);
   // file found at server
  if (httpCode==HTTP_CODE_OK){
    String payload=http.getString();
    Serial.println(payload);

  }
  }
  else{
    Serial.printf("[HTTP] GET.... failed, error : %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}
void sendDataToSheet30(void){
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1" + String((int)value1) + "?value2" + String((int)value2);
  Serial.println(url);
  HTTPClient http;
  http.begin(url); //HTTP
  Serial.print("[HTTP] Get...\n");
  // start connection and send HTTP header
  int httpCode =http.GET();
    // httpCode will be negative on error
  if (httpCode > 0){
    Serial.printf("[HTTP] Get..... Code: %d\n", httpCode);
   // file found at server
  if (httpCode==HTTP_CODE_OK){
    String payload=http.getString();
    Serial.println(payload);

  }
  }
  else{
    Serial.printf("[HTTP] GET.... failed, error : %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}
void loop() {
  value1 =dht.readHumidity();
  value2= dht.readTemperature();
  if(value2 > 29){
    sendDataToSheet30();
    sendDataToSheet();
  }
  else{
    sendDataToSheet();
  }
  Serial.println("Values are: ");
  Serial.println(value1);
  Serial.println(" ");
  Serial.println(value2);
  delay(1000);
}