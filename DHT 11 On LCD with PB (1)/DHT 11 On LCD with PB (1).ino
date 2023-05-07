//The goal of this lab was to learn how to alternate through different variables displayed on the LCD with the use of a push button


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
#define DHTPIN 2     // Digital pin connected to the DHT sensor 
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


////Pins for LCD display
LiquidCrystal lcd(2, 3, 4, 5, 11, 12);
// create our custom character 
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
//variables for the push button 
int PBState = LOW;
int lastButtonState;
int currentButtonState;

void setup() {
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
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
pinMode(1, INPUT_PULLUP);
currentButtonState = digitalRead(3);
}

void loop() {
  // varible to hold the count of the displayed screen 
lastButtonState    = currentButtonState;      // save the previous button state
currentButtonState = digitalRead(3);

// every time the button is pressed the button state goes up 1
if(lastButtonState == 1 && currentButtonState == 0) {
    PBState = PBState + 1;
  // reset the counter everytime PBState goes above 2 
if (PBState>2){
  PBState = 0;
}
  }

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float temp = event.temperature;
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.print(F("°C"));
    Serial.print(F("\t"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.print(F("%"));
    Serial.print(F("\t"));
  }
Serial.println(PBState);
  lcd.setCursor(0, 0);
  //if the PBState is 0 it will diplay the humidity on the LCD 
if (PBState == 0){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Humidity ");
lcd.print(event.relative_humidity);
lcd.print("%");
}
  //if the PBState is 1 it will diplay the temperature in celsius on the LCD 
if (PBState==1){
lcd.clear();
lcd.print("Temp: ");
lcd.print(temp);
lcd.print("C");
lcd.write(byte(0));
}
  //if the PBState is 2 it will diplay the temperature in farenheit on the LCD 
if(PBState==2){
lcd.clear();
float tempf = ((9/5)*temp)+32;
lcd.print("Temp: ");
lcd.print(tempf);
lcd.print("F");
lcd.write(byte(0));
}


}
