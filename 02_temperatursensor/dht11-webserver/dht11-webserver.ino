//
// Einfacher Sketch, um mit DHT-Sensor Temp. & Luftfeuchte zu messen
//
// Zum Verwenden vorab über Sketch/Include Libraries/Manage Libraries die
// DHT sensor library installieren
//

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

//==== config section ====

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define myPIN  D2

/*Put your SSID & Password*/
const char* ssid     = "YOURWLAN";  // Enter SSID here
const char* password = "********";  //Enter Password here

//==== code section ====

// define webserver object
ESP8266WebServer server(80);

// DHT Sensor
uint8_t DHTPin = myPIN;
               
// initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

// global variables for values from sensor
float Temperature;
float Humidity;

//---- setup section ----
void setup() {
  Serial.begin(115200);
  delay(100);

  // setup connection to read from sensor  
  pinMode(DHTPin, INPUT);
  dht.begin();              

  //connect to your local wi-fi network
  Serial.println("Connecting to wlan");
  WiFi.begin(ssid, password);

  // wait for wifi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connection establshed.");

  // init web server; define path and the function that handles it
  server.on("/",     handle_root);
  server.on("/html", handle_html);
  server.on("/json", handle_json);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.print("HTTP server started on IP: ");
  Serial.println(WiFi.localIP() );
}

//---- main loop ----
void loop() {
  server.handleClient();
}


//---- functions ----
void handle_root() {
  server.send(200, "text/html", gen_root()); 
}

void read_sensor() {
  Temperature = dht.readTemperature(); // read temperature
  Humidity    = dht.readHumidity();    // read humidity 
  Serial.print("\nTemperatur: "); Serial.println(Temperature);
  Serial.print("Luftfeuchte: ");  Serial.println(Humidity);
}

void handle_html() {
  read_sensor();
  server.send(200, "text/html", gen_html(Temperature,Humidity)); 
}

void handle_json() {
  read_sensor();
  server.send(200, "application/javascript", gen_json(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String gen_root(){
  String root_html = "<!DOCTYPE html> <html>\n";
  root_html += "<head><title>DHT sensor data</title></head>\n";;
  root_html += "<body><h3>Read sensor data from DHT11</h3><ul>";
  root_html += "<li><a href='/html'>html</a></li>";
  root_html += "<li><a href='/json'>json</a></li>";
  root_html += "</ul></body></html>";
  return root_html;
}
// send html page (on '/')
String gen_html(float Temperaturestat,float Humiditystat){
  String my_html = "<!DOCTYPE html> <html>\n";
  my_html += "<head><title>DHT sensor data</title></head>\n";
  my_html += "<body><h3>DHT sensor data:</h3>\n<ul>";
  
  my_html += "<li>Temperatur: ";
  my_html += (int)Temperaturestat;
  my_html += "&deg;C</li>";
  my_html += "<li>Humidity: ";
  my_html += (int)Humiditystat;
  my_html +=  "%</li>";
  
  my_html += "</ul></body></html>\n";
  return my_html;
}

// send json (on '/json')
String gen_json(float Temperaturestat,float Humiditystat){
  String my_json = "{";
  my_json       += "\n  \"temperature_c\": ";
  my_json       += (int)Temperaturestat;
  my_json       += ",\n  \"humidity_pct\": ";
  my_json       += (int)Humiditystat;
  my_json       += "\n}\n";
  return my_json;
}
