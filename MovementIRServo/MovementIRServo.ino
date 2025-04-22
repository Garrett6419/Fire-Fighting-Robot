#include <Servo.h>

#define ir_R A0 // Right IR sensor
#define ir_F A1 // Front IR sensor
#define ir_L A2 // Left IR sensor
#define smokeDetectorPin A4 // Smoke detector pin moved to A4
#define buzzerPin 12 // Buzzer pin

#define enA 10 // Enable1 L298 Pin
#define in1 9  // Motor1 L298 Pin (Left Motor)
#define in2 8  // Motor1 L298 Pin (Left Motor)
#define enB 5  // Enable2 L298 Pin
#define in3 7  // Motor2 L298 Pin (Right Motor)
#define in4 6  // Motor2 L298 Pin (Right Motor)

Servo myServo; // Create a Servo object
#define SERVO_PIN 3 // Use pin 3 for servo control

// Define distance thresholds
const int CLOSE_DISTANCE_THRESHOLD = 50; // Adjust this value based on your IR sensor's range
const int FAR_DISTANCE_THRESHOLD = 100; // Adjust this value based on your IR sensor's range

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(ir_R, INPUT);
  pinMode(ir_F, INPUT);
  pinMode(ir_L, INPUT);
  pinMode(smokeDetectorPin, INPUT); // Initialize smoke detector pin
  pinMode(buzzerPin, OUTPUT); // Initialize buzzer pin
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
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
      myServo.write(45); // Point between pins 1 and 2
      moveLeft(); // Move left
    }
    else if(s3 < 250) {
      myServo.write(135); // Point between pins 2 and 3
      moveRight(); // Move right
    }
    else {
      myServo.write(90); // Point servo to the front
      maintainDistance(s2); // Maintain distance from the front
    }
  } 
  else if (s1 < 250) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer when fire is detected
    myServo.write(0); // Point servo to the left
    moveLeft(); // Move left
  } 
  else if (s3 < 250) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer when fire is detected
    myServo.write(180); // Point servo to the right
    moveRight(); // Move right
  } 
  // Smoke detection logic
  else if (smokeValue == HIGH) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer when smoke is detected
    myServo.write(90); // Point servo to the front (or any default position)
    stopMotors(); // Stop the motors
  } 
  else {
    digitalWrite(buzzerPin, LOW); // Deactivate buzzer when no fire or smoke is detected
    myServo.write(90); // Reset servo to center position
    stopMotors(); // Stop the motors
  }
  
  delay(10);
}

void maintainDistance(int frontSensorValue) {
  if (frontSensorValue < CLOSE_DISTANCE_THRESHOLD) {
    // Too close, stop or move back
    stopMotors();
  } else if (frontSensorValue > FAR_DISTANCE_THRESHOLD) {
    // Too far, move forward
    moveForward();
  } else {
    // Within the desired range, maintain current speed
    moveForward();
  }
}

void moveForward() {
  analogWrite(enA, 255); // Full speed for left motor
  analogWrite(enB, 255); // Full speed for right motor
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveLeft() {
  analogWrite(enA, 255); // Full speed for left motor
  analogWrite(enB, 255); // Full speed for right motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveRight() {
  analogWrite(enA, 255); // Full speed for left motor
  analogWrite(enB, 255); // Full speed for right motor
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}