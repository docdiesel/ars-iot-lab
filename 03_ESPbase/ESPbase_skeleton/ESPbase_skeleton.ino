#include <Arduino.h>
#include <ESPBASE.h>

ESPBASE Esp;

void setup() {
  Serial.begin(115200);
  Esp.initialize();

  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(millis());

  ArduinoOTA.handle();        // OTA request handling
  server.handleClient();      //  WebServer requests handling
  customWatchdog = millis();  //  feed the DOG :)

  //**** Normal Skecth code here ...
}
