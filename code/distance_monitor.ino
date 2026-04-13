// distance_monitor.ino
// Arduino Distance Monitoring System using Ultrasonic Sensor + I2C LCD + LEDs

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup (change 0x27 to 0x3F if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic sensor pins
int trigPin = 9;
int echoPin = 10;

// LED pins
int greenLED = 2;
int yellowLED = 3;
int redLED = 4;

// Function to smooth distance readings (average of 5)
long getDistance() {
  long total = 0;

  for (int i = 0; i < 5; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034 / 2;

    total += distance;
    delay(10);
  }

  return total / 5;
}

void setup() {
  // Sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LED pins
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // LCD setup
  lcd.init();
  lcd.backlight();
}

void loop() {
  int distance = getDistance();

  // LED logic
  if (distance > 50) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  } 
  else if (distance > 20) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
  } 
  else {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
  }

  // LCD display (clean formatting)
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm   "); // clears leftover characters

  lcd.setCursor(0, 1);

  if (distance > 50) {
    lcd.print("Status: SAFE   ");
  } 
  else if (distance > 20) {
    lcd.print("Status: MID    ");
  } 
  else {
    lcd.print("Status: CLOSE  ");
  }

  delay(200);
}
