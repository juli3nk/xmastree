#include <ArduinoJson.h>
#include <Preferences.h>
#include <WebServer.h>

#include "animations.h"
#include "server.h"

// JSON data buffer
StaticJsonDocument<250> jsonDocument;
char buffer[250];

// Web server running on port 80
WebServer Server(API_PORT);

// Setup
void setupServer() {
  Serial.printf("Listening on TCP port: %u\n", API_PORT);

  // API Server event hooks
  Server.onNotFound(handleNotFound);
  Server.on("/on", HTTP_GET, handleOn);
  //Server.on("/off", HTTP_GET, handleOff);
  Server.on("/status", HTTP_GET, handleStatus);
  Server.on("/set", HTTP_POST, handleSet);
  Server.on("/prev", HTTP_GET, handlePrevAnimation);
  Server.on("/next", HTTP_GET, handleNextAnimation);

  // start server
  Server.begin();
}

// API
void handleAPIClient() {
  Server.handleClient();
}

void sendFailReply(const char* msg) {
  StaticJsonDocument<JSON_ERROR_SIZE> doc;
  char stringBuffer[JSON_ERROR_SIZE];

  doc["success"] = false;
  doc["message"] = msg;

  serializeJson(doc, stringBuffer, JSON_ERROR_SIZE);
  doc.clear();

  Server.send(400, "text/json", String(stringBuffer));
}

void handleNotFound() {
    Server.send(404, "text/plain", "Page Not Found");
}

void handleOn() {
  SetStatus(1);

  Preferences preferences;

  preferences.begin("xmastree", false);
  unsigned int animationMode = preferences.getUInt("mode", 1);
  preferences.end();

  ChangeAnimation(animationMode);

  jsonDocument.clear();
  jsonDocument["status"] = "on";
  serializeJson(jsonDocument, buffer);

  Server.send(200, "application/json", buffer);
}

/*
void handleOff() {
  SetStatus(0);

  SwitchOff();

  jsonDocument.clear();
  jsonDocument["status"] = "off";
  serializeJson(jsonDocument, buffer);

  Server.send(200, "application/json", buffer);
}
*/
void handleStatus() {
  jsonDocument.clear();
  jsonDocument["status"] = GetStatus();
  jsonDocument["mode"] = GetMode();
  serializeJson(jsonDocument, buffer);

  Server.send(200, "application/json", buffer);
}

void handleSet() {
  if (Server.hasArg("mode") == false) {
    //handle error here
  }
  String body = Server.arg("mode");
  deserializeJson(jsonDocument, body);

  int mode = jsonDocument["mode"];

  ChangeAnimation(mode);

  // Respond to the client
  jsonDocument.clear();
  jsonDocument["mode"] = mode;
  serializeJson(jsonDocument, buffer);

  Server.send(200, "application/json", buffer);
}

void handlePrevAnimation() {
  ChangePrevAnimation();

  jsonDocument.clear();
  jsonDocument["mode"] = GetMode();
  serializeJson(jsonDocument, buffer);

  Server.send(200, "application/json", buffer);
}

void handleNextAnimation() {
  ChangeNextAnimation();

  jsonDocument.clear();
  jsonDocument["mode"] = GetMode();
  serializeJson(jsonDocument, buffer);

  Server.send(200, "application/json", buffer);
}
