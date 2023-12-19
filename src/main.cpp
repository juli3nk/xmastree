#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFiManager.h>

#include "animations.h"
#include "server.h"

WiFiManager wifiManager;

void setup() {
  // Serial for debugging
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(3000);
  Serial.println("\n Starting");

  bool res;
  res = wifiManager.autoConnect("XmasTree", "xt191225");
  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  }

  // Initialize mDNS
  if (!MDNS.begin("xmastree")) {
    Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }

  setupServer();

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", API_PORT);
}

void loop() {
  handleAPIClient();

  // Refresh animation
  AnimationUpdate();
}
