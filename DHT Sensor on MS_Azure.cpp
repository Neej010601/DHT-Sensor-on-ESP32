#include <Arduino.h>
#include <WiFi.h>
#include "DHT.h"
#include "AzureIoTHub.h" //IOT Hub library
#include "Esp32MQTTClient.h" //ESP IoT Library
#define Interval 2000
#define DID "Esp32device"  //DID from Cloud
#define msg_length 256 //msg lenght
#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid ="Neej";  //ssid of WiFi
const char* password= "1234567890"; //Password

int msgCount = 1; //count starts from 1

static const char* connectionString = "dgqufgirhqoduvuadfygqiudgqikbcjvxzufu7t1278e361285616t08r0"; //connection string from cloud
const char *msgData = "{\"DID\":\"%s\", \"msgId\":\"%d\",\"Temperature\":\"%f\",\"Humidity\":\"%f\"}"; //data read

static bool hasWifi = false; //initially not connected
static bool msgSending = true;
static unit64_t send_interval_ms; //delay

static void InitWifi(){
  //for setup the connection.
  Serial.println("Connecting...");
  WiFi.begin(ssid, password);
  while (WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.println(.);
  }
  hasWifi= true;
  Serial.println("WiFi Connected...");
  Serial.println("IP Address: ");
  Serial.print(WiFi.localIP());
}

static void SendConfirmationCallBack(IOTHUB_CLIENT_CONFIRMATION_Result result){
  //get the call back from cloud that device has been connected.
  if (result== IOTHUB_CLIENT_CONFIRMATION_OK){
    Serial.println("Send Confirmation Call Back Finished")
  }
}
void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("ESP32 Device.");
  Serial.println("Initializing...");
  Serial.println("> WiFi");
  hasWifi = false;
  InitWifi();
  if (!==hasWifi){
    return;
  }
  Serial.println("> IoTHub");
  //get the call back from cloud that setup has been done and ready for get the data.
  Esp32MQTTClient_Init((const unit8_t*)connectionString);
  Esp32MQTTClient_SetSendConfirmationCallback(SendConfirmationCallBack);
  send_interval_ms =millis();
}

void loop() {
  if (hasWifi){
    if (msgSending && (int) (millis() - send_interval_ms) >= Interval){
      char msgPayload(msg_length);
      float humidity= dht.readHumidity;
      float temperature =dht.readTemperature;
      snprintf(msgPayload, msg_length, msgData, DID, msgCount++, temperature,humidity); //The snprintf() function formats and stores a series of characters and values in the array buffer. 
      Serial.println(msgPayload);
      EVENT_INSTANCE* message = Esp32MQTTClient_Event_Generate(messagePayload, MESSAGE);
      Esp32MQTTClient_SendEventInstance(message);
      send_interval_ms = millis();
    }
  }
  delay(10);
}
