/*The goal for this lab was was to combine the DHT11 temperature sensor and the Ultrasonic
sensor to provide a more accurate reading*/

#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 8      // the DHT11 data pin
#define DHTTYPE DHT11 // the DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);
//Define the echo pin
#define echoPin 6 
//define the triPin
#define trigPin 7      
#define maxDistance 100 
// Pins for LCD display
LiquidCrystal lcd(2, 3, 4, 5, 11, 12);
void setup() {
  Serial.begin(9600);
  //Defining trigPin and echoPin pinModes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //setting up the LCD
  dht.begin();
  lcd.begin(16, 2);
}
void loop() {
  //variables for the DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // measure distance using Ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Variables for the Ultrasonic sensor
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
// equation for the compensated distance based on temperature and humidity
    float compensatedDistance = distance / (1 + 0.00016 * temperature + 0.00039 * humidity);
    //Print the Distance to Serial Monitor 
    Serial.print("Distance (cm): ");
    Serial.print(compensatedDistance);
    //Print the temperature to Serial Monitor
    Serial.print(", Temperature (C): ");
    Serial.print(temperature);
    //Print the humdity to Serial Monitor
    Serial.print(", Humidity (%): ");
    Serial.println(humidity);
    //set the LCD
  lcd.setCursor(0, 0);
  //Display the distance in cm on the LCD
  lcd.print("Distance: ");
  lcd.print(compensatedDistance);
  lcd.print("cm");
  delay(500);
  }
