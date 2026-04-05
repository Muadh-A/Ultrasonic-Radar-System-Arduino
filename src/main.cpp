#include <Arduino.h>
#include <LiquidCrystal.h> // Load Liquid Crystal Library
#include <Servo.h>

LiquidCrystal LCD(10, 6, 5, 4, 3, 2); // LCD object

int trigPin = 8;      // Trigger pin
int echoPin = 9;      // Echo pin
float pingTime;       // Time for ping to travel to target and back
float targetDistance; // Distance to target in cm

// ----- Servo Setup -----
Servo myServo;
int servoPin = 11;       // Servo control pin
int servoAngle = 0;      // Current angle
int servoStep = 1;       // Angle step for smooth movement
bool increasing = true;   // Direction flag

const float speedOfSound_cm_s = 34300.0; // Speed of sound in cm/s

void setup() {
  Serial.begin(9600);

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LCD setup
  LCD.begin(16, 2);
  LCD.setCursor(0, 0);
  LCD.print("Target Distance:");

  // Servo
  myServo.attach(servoPin);
  myServo.write(servoAngle);
}

void loop() {
  // Ultrasonic sensor measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);      // Allow sensor to settle
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);     // Trigger pulse
  digitalWrite(trigPin, LOW);

  // Read echo time in microseconds
  pingTime = pulseIn(echoPin, HIGH); 
  pingTime = pingTime / 1000000.0; // Convert to seconds

  // Calculate distance in cm
  targetDistance = (pingTime / 2.0) * speedOfSound_cm_s;
  Serial.println(targetDistance); // Debug

  // Display on LCD
  LCD.setCursor(0, 1);
  LCD.print("                "); // Clear row
  LCD.setCursor(0, 1);
  LCD.print(targetDistance); 
  LCD.print(" cm");

  // Servo sweep
  myServo.write(servoAngle);

  if (increasing) {
    servoAngle += servoStep;
    if (servoAngle >= 180) {
      servoAngle = 180;
      increasing = false;
    }
  } else {
    servoAngle -= servoStep;
    if (servoAngle <= 0) {
      servoAngle = 0;
      increasing = true;
    }
  }
  delay(15); // Delay controls sweep speed (smaller = faster)
}