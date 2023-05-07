//The goal of this lab was to familiarize ourselves with the DHT11 temperature sensor and learn to display it's values on an LCD

// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include <afstandssensor.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
#define DHTPIN 7     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT11     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);
AfstandsSensor afstandssensor(6, 5);  

uint32_t delayMS;


//Pins for LCD display
LiquidCrystal lcd(2, 3, 4, 5, 11, 12);
//Custom degree symbol used for LCD
byte customChar[8] = {
	0b01100,
	0b10010,
	0b10010,
	0b01100,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

void setup() {
  //custom character created 
lcd.createChar(0,customChar);
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Delay between sensor readings
  delayMS = sensor.min_delay / 1000;
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  

}

void loop() {


  // Get temperature event and print value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float temp = event.temperature;
  if (isnan(event.temperature)) {
    //Indication if there is an error
    Serial.println(F("Error reading temperature!"));
  }
  else {
    //Print the temprature 
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.print(F("°C"));
    Serial.print(F("\t"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    //Indication if there is an error
    Serial.println(F("Error reading humidity!"));
  }
  else {
    //Print the Humidity 
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.print(F("%"));
    Serial.print(F("\t"));
  }

 
//Display the Humidity on the 0,0 of the screen 
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Humidity ");
lcd.print(event.relative_humidity);
lcd.print("%");
//Display the Temprature on the 0,1 of the screen 
lcd.setCursor(0,1);
lcd.print("Temp: ");
lcd.print(temp);
lcd.print("C");
//Display custom character
lcd.write(byte(0));


}
