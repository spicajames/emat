#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

int relePin = 2; // GPIO2

WiFiManager wifiManager;

void configModeCallback (WiFiManager *myWiFiManager) {
        digitalWrite(relePin, LOW);
        Serial.println("Entered config mode");
        Serial.println(WiFi.softAPIP());
        Serial.println(myWiFiManager->getConfigPortalSSID());
}


void setup() {
        Serial.begin(115200);
        pinMode(relePin, OUTPUT);
        digitalWrite(relePin, LOW);

        //reset settings - for testing
        //wifiManager.resetSettings();

        //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
        wifiManager.setAPCallback(configModeCallback);

        //fetches ssid and pass and tries to connect
        //if it does not connect it starts an access point with the specified name
        //here  "AutoConnectAP"
        //and goes into a blocking loop awaiting configuration

        //wifiManager.setTimeout(60);
        Serial.print("Trying to connect to: ");
        Serial.println(wifiManager.getConfigPortalSSID());
        String ssid = "ESP" + String(ESP.getChipId());
        if(!wifiManager.autoConnect(ssid.c_str(), "passhere")) {
                Serial.println("failed to connect and hit timeout");
                //reset and try again, or maybe put it to deep sleep
                //ESP.reset();
                //delay(1000);
        }
}

void loop() {
        Serial.print("Status:");
        Serial.println(WiFi.status());
        if(WiFi.status() != WL_CONNECTED ) {
                digitalWrite(relePin, HIGH);
        }
        if(WiFi.status() == WL_CONNECTED ) {
                digitalWrite(relePin, LOW);
        }
        delay(1000);
}
