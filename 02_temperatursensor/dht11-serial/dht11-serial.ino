
// Temp. & Luftfeuchte auf serieller Schnittstelle ausgeben

#include "DHT.h"

#define DHTTYPE DHT11

// DHT Sensor –Dx laut Aufdruck auf NodeMCU
uint8_t DHTPin = D2; 
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;

//#########################################
void setup() {
  Serial.begin(115200);     // Serielle Schnittstelle starten
  delay(100);
  
  pinMode(DHTPin, INPUT);   // GPIO Pin auf Input schalten
  dht.begin();              // starte DHT
}

//#########################################
void loop(){
  Serial.print("\nTemperatur: "); Serial.println(dht.readTemperature());
  Serial.print("Luftfeuchte: ");  Serial.println(dht.readHumidity());
  delay(5000);
}
