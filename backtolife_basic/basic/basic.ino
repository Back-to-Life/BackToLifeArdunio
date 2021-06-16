#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Arduino.h>
#include "FirebaseJson.h"

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID "backtolife"
#define WIFI_PASSWORD "..."

FirebaseData firebaseData;

String path = "/";
FirebaseJson json;

void setup()
{

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println();
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  if (!Firebase.beginStream(firebaseData, path))
  {
    Serial.println("REASON " + firebaseData.errorReason());
    Serial.println();
  }
}

void loop()
{
  //Firebase.setInt(firebaseData,path+"/data",1);
}
