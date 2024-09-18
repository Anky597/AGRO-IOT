#define BLYNK_TEMPLATE_ID    "Replace your BLYNK_TEMPLATE_ID here"
#define BLYNK_TEMPLATE_NAME  "Replace your BLYNK_TEMPLATE_NAME here"
#define BLYNK_AUTH_TOKEN     "Replace your BLYNK_AUTH_TOKEN here"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wifi Name";
char pass[] = "Wifi Password";

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
const int soilMoisturePin = 35; // Analog pin for the soil moisture sensor
const int waterLevelPin = 34;   // Analog pin for the water level sensor
const int pumpPin = 5;  // Pin connected to the DC pump on ESP32
int pumpState = LOW;    // Initialize pumpState to LOW (off)
int pumpMode = 0;       // 0 for automatic, 1 for manual
int waterLevel = 0;     // Water level indicator value
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // Interval in milliseconds
float mappedSoilMoisture = 0; // Declare mappedSoilMoisture as a global variable

// Constants for soil moisture thresholds
const int SOIL_MOISTURE_LOW = 50;  
const int SOIL_MOISTURE_HIGH = 50; 

void setup() {
  Serial.begin(115200);
  pinMode(pumpPin, OUTPUT);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V6, LOW); // Initialize the mode button to automatic mode
  Blynk.virtualWrite(V5, LOW); // Initialize the pump button to OFF
}

BLYNK_WRITE(V5) { // Manual control for pump
  if (pumpMode == 1) { // Check if the mode is manual
    pumpState = param.asInt(); // Read the state of the pump button
    digitalWrite(pumpPin, pumpState); // Turn the pump on or off based on button state
  }
}

BLYNK_WRITE(V6) { // Change mode between automatic and manual
  pumpMode = param.asInt(); // Read the state of the mode button
}

void loop() {
  Blynk.run();
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (pumpMode == 0) {
      int soilSensorValue = analogRead(soilMoisturePin);
      Serial.println(soilSensorValue);
      mappedSoilMoisture = map(soilSensorValue, 1023, 2750, 100, 0); // Update mappedSoilMoisture
      autoControlPump(mappedSoilMoisture); // Automatically control the pump if in automatic mode
    }

    waterLevel = analogRead(waterLevelPin);
    Serial.println(waterLevel);
    if (waterLevel < 450) {
      waterLevel = 0;
    } else {
      waterLevel = map(waterLevel, 1200, 1600, 0, 100); // Map water level to 0-100
    }

    readAndSendSensorData();
    Blynk.virtualWrite(V7, waterLevel); // Send water level to Blynk
  }
}

void autoControlPump(float mappedSoilMoisture) {
  if (waterLevel < 30) {
    pumpState = LOW;
  } else if (mappedSoilMoisture <= SOIL_MOISTURE_LOW) {
    pumpState = HIGH;
  } else if (mappedSoilMoisture >= SOIL_MOISTURE_HIGH) {
    pumpState = LOW;
  }

  digitalWrite(pumpPin, pumpState); // Update the pump state
  if (pumpMode == 0) {
    Blynk.virtualWrite(V5, pumpState); // Update the pump button status on Blynk
  }
}

void readAndSendSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (!isnan(humidity) && !isnan(temperature)) {
    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);
    Serial.println(temperature);
    Serial.println(humidity);
  } else {
    Serial.println(F("Failed to read from DHT sensor!"));
  }

  if (pumpMode == 0) {
    Blynk.virtualWrite(V4, mappedSoilMoisture); // Update mappedSoilMoisture on Blynk
  }
}
