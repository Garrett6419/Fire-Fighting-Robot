#include <Servo.h>

#define ir_R A0 // Right IR sensor
#define ir_F A1 // Front IR sensor
#define ir_L A2 // Left IR sensor
#define smokeDetectorPin A4 // Smoke detector pin moved to A4
#define buzzerPin 12 // Buzzer pin

Servo myServo; // Create a Servo object
#define SERVO_PIN 3 // Use pin 3 for servo control

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(ir_R, INPUT);
  pinMode(ir_F, INPUT);
  pinMode(ir_L, INPUT);
  pinMode(smokeDetectorPin, INPUT); // Initialize smoke detector pin
  pinMode(buzzerPin, OUTPUT); // Initialize buzzer pin
  
  myServo.attach(SERVO_PIN); // Attach the servo to the specified pin
  myServo.write(90); // Start the servo at the center position (facing forward)
}

void loop() {
  int s1 = analogRead(ir_R);
  int s2 = analogRead(ir_F);
  int s3 = analogRead(ir_L);
  int smokeValue = digitalRead(smokeDetectorPin); // Read smoke detector value
  
  Serial.print("IR Right: ");
  Serial.print(s1);
  Serial.print("\tIR Front: ");
  Serial.print(s2);
  Serial.print("\tIR Left: ");
  Serial.print(s3);
  Serial.print("\tSmoke: ");
  Serial.println(smokeValue);
  delay(50);
  
  // Fire detection logic
  if (s2 < 350) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer when fire is detected
    if(s1 < 250) {
      myServo.write(45) ;// Point between pins 1 and 2
    }
    else if(s3 < 250) {
      myServo.write(135) ;// Point between pins 2 and 3
    }
    else {
      myServo.write(90); // Point servo to the front
    }
  } 
  else if (s1 < 250) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer when fire is detected
    myServo.write(0); // Point servo to the left
  } 
  else if (s3 < 250) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer when fire is detected
    myServo.write(180); // Point servo to the right
  } 
  // Smoke detection logic
  else if (smokeValue == HIGH) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer when smoke is detected
    myServo.write(90); // Point servo to the front (or any default position)
  } 
  else {
    digitalWrite(buzzerPin, LOW); // Deactivate buzzer when no fire or smoke is detected
    myServo.write(90); // Reset servo to center position
  }
  
  delay(10);
}