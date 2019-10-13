#include <Arduino.h>
#include <ESPBASE.h>

ESPBASE Esp;

void setup() {
  Serial.begin(115200);
  Esp.initialize();

  // put your setup code here, to run once:
  server.on ( "/fnord", send_fnord_html );
}

void loop() {
  // ESPbase code first
  ArduinoOTA.handle();        // OTA request handling
  server.handleClient();      // WebServer requests handling
  customWatchdog = millis();  // feed the DOG :)

  // custom code here
}

void send_fnord_html(){
  String myhtml = "";
  myhtml += "<html><body>Don't see the <i>fnord</i>!</body></html>";
  server.send( 200, "text/html", myhtml);
  Serial.println("Fnord!");
}
