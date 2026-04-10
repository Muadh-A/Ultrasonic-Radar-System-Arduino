#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal LCD(10, 6, 5, 4, 3, 2);

int trigPin = 8;
int echoPin = 9;
float pingTime;
float targetDistance;

Servo myServo;
int servoPin = 11;
int servoAngle = 0;
int servoStep = 10;
bool increasing = true;

const float speedOfSound_cm_s = 34300.0;

unsigned long lastMeasureTime = 0;
const int measureInterval = 1000; // 1 second between measurements

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  LCD.begin(16, 2);
  LCD.setCursor(0, 0);
  LCD.print("Target Distance:");

  myServo.attach(servoPin);
  myServo.write(servoAngle);
}

void loop() {
  // Move servo one step
  myServo.write(servoAngle);

  // Only measure and send data every 1 second
  unsigned long now = millis();
  if (now - lastMeasureTime >= measureInterval) {
    lastMeasureTime = now;

    // Take distance measurement
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    pingTime = pulseIn(echoPin, HIGH);
    pingTime = pingTime / 1000000.0;
    targetDistance = (pingTime / 2.0) * speedOfSound_cm_s;

    // Send to UI
    Serial.print(servoAngle);
    Serial.print(",");
    Serial.println(targetDistance);

    // Update LCD
    LCD.setCursor(0, 1);
    LCD.print("                ");
    LCD.setCursor(0, 1);
    LCD.print(targetDistance);
    LCD.print(" cm");

    // Advance servo angle
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
  }

  delay(10); // small delay to not hammer the CPU
}
