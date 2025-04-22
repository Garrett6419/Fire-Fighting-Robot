#include <Servo.h>

Servo myServo; // Create a Servo object

#define SERVO_PIN 3 // Use pin 9 for servo control

void setup() {
  myServo.attach(SERVO_PIN); // Attach the servo to the specified pin
  myServo.write(90); // Move to the center position (90 degrees)
  delay(1000); // Wait for the servo to reach the position
}

void loop() {
  myServo.write(0); // Move to 0 degrees (left)
  delay(1000); // Wait for 1 second
  myServo.write(180); // Move to 180 degrees (right)
  delay(1000); // Wait for 1 second
  myServo.write(90); // Move back to 90 degrees (center)
  delay(1000); // Wait for 1 second
}