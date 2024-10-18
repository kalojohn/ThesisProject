#include <ESP8266WiFi.h>
//#include <ESPAsyncWebServer.h>
//#include <ArduinoJson.h>
// #include <ESP_Mail_Client.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>
#include <Ticker.h>

bool distAlert = false;
bool weightAlert = false;
bool tempAlert = false;
bool weightLossAlert = false;

// Your WiFi credentials
//const char* ssid = "ARROW-011daf";
//const char* password = "kalogiannaras!!";

// Your WiFi credentials
const char* ssid = "iPhone-Panos";
const char* password = "543210123";

void Wifi_init()
{
  // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi, IP address: " + WiFi.localIP().toString());
}

void setup() {

    serialCom_init();
    Wifi_init();
    //webServer_init();
    timers_init();
}


void loop() {
  if (distAlert)
  {
    sendMessage("Caution! Somebody is present.");
    distAlert = false;
  }

  if (weightAlert)
  {
    sendMessage("You should collect the water soon! More than 90% capacity reached.");
    weightAlert = false;
  }

  if (weightLossAlert)
  {
    sendMessage("Caution! We are losing water. Check for leakage or theft!");
    weightLossAlert = false;
  }

  if (tempAlert)
  {
    sendMessage("Danger that water might freeze!");
    tempAlert = false;
  }

}


