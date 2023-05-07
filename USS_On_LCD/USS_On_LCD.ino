//The purpose of this lab was to become familar with the ultra sonic sensor to allow us to calculate and measure the given distance 

#include <afstandssensor.h>
#include <LiquidCrystal.h>
//Pins for LCD display
LiquidCrystal lcd(2, 3, 4, 5, 11, 12);

// define pins numbers
const int trigPin = 7;
const int echoPin = 6;
// variables required for distance equation
long duration;
float distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
   lcd.begin(16, 2);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Turns ON trigPin for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // Turns trigPin back off
  // Reads the echoPin and returns value microseconds
  duration = pulseIn(echoPin, HIGH);
  // Equation the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(duration);
  //Displays distance in cm on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
  delay(200);
}
