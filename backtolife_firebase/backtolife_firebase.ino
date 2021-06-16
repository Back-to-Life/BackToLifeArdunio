#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

//1. Firebase veritabanı adresini, Token bilgisini ve ağ adresi bilgilerinizi giriniz.
#define FIREBASE_HOST "realtime" // http:// veya https:// olmadan yazın
#define FIREBASE_AUTH "secretdb"
#define WIFI_SSID "wifi"
#define WIFI_PASSWORD "wifipassword"

//2. veritabanim adında bir firebase veritabanı nesnesi oluşturuyoruz
FirebaseData veritabanim;

int sensor = 13; // Digital pin D7

void setup()
{
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Ağ Bağlantısı Oluşturuluyor");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println("İnternete Bağlandı");
    Serial.println();
    //3. Firebase bağlantısı başlatılıyor
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    //4. Ağ bağlantısı kesilirse tekrar bağlanmasına izin veriyoruz
    Firebase.reconnectWiFi(true);
    pinMode(sensor, INPUT);
}

void loop()
{
    long state = digitalRead(sensor);
    if (state == HIGH)
    {
        Serial.println("Motion detected!");
        if (Firebase.setBool(veritabanim, "/ktu", true))
        {
            Serial.println("Başarılı bir şekilde firebase yazıldı interrupt");
            delay(10000);
        }
        else
        {
            Serial.println("Hata gerçekleşti sebep true yazamadı:");
            Serial.println(veritabanim.errorReason());
        }

        if (Firebase.setInt(veritabanim, "/howmanypush", howMuchCounter))
        {
            Serial.println("Başarılı bir şekilde firebase yazıldı counter yazildi");
        }
        else
        {
            Serial.println("Hata gerçekleşti sebep counter yazılmadı:");
            Serial.println(veritabanim.errorReason());
        }
        delay(60000);
        if (Firebase.setBool(veritabanim, "/ktu", false))
        {
            Serial.println("Başarılı bir şekilde resetlendi");
        }
        else
        {
            Serial.println("Hata gerçekleşti loop sorunu:");
            Serial.println(veritabanim.errorReason());
        }
    }
    else
    {
        Serial.println("No motion detected.");
        delay(3000);
    }
}