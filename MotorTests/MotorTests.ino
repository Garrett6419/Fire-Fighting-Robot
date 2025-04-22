#define enA 10 // Enable1 L298 Pin
#define in1 9  // Motor1 L298 Pin (Left Motor)
#define in2 8  // Motor1 L298 Pin (Left Motor)
#define enB 5  // Enable2 L298 Pin
#define in3 7  // Motor2 L298 Pin (Right Motor)
#define in4 6  // Motor2 L298 Pin (Right Motor)

void setup() {
  // Initialize motor control pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  // Start the motor test
  Serial.begin(9600);
  Serial.println("Starting Motor Test...");
  
  // Test Forward
  Serial.println("Going Forward") ;
  moveForward();
  delay(1000); // Move forward for 1 second
  stopMotors();
  delay(500); // Wait for half a second

  // Test Backward
  Serial.println("Going Backward") ;
  moveBackward();
  delay(1000); // Move backward for 1 second
  stopMotors();
  delay(500); // Wait for half a second

  // Test Turn Right
  Serial.println("Going Right") ;
  turnRight();
  delay(1000); // Turn right for 1 second
  stopMotors();
  delay(500); // Wait for half a second

  // Test Turn Left
  Serial.println("Going Left") ;
  turnLeft();
  delay(1000); // Turn left for 1 second
  stopMotors();
  delay(500); // Wait for half a second

  // Stop all motors
  stopMotors();
  Serial.println("Motor Test Completed.");
}

void loop() {
  Serial.println("Starting Motor Test...");
  
  // Test Forward
  Serial.println("Going Forward") ;
  moveForward();
  delay(1000); // Move forward for 1 second
  stopMotors();
  delay(500); // Wait for half a second

  // Test Backward
  Serial.println("Going Backward") ;
  moveBackward();
  delay(1000); // Move backward for 1 second
  stopMotors();
  delay(500); // Wait for half a second

  // Stop all motors
  stopMotors();
}

void moveForward() {
  analogWrite(enA, 255); // Full speed for left motor
  analogWrite(enB, 255); // Full speed for right motor
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  analogWrite(enA, 255); // Full speed for left motor
  analogWrite(enB, 255); // Full speed for right motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  analogWrite(enA, 255); // Full speed for left motor
  analogWrite(enB, 255); // Full speed for right motor
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  analogWrite(enA, 255); // Full speed for left motor
  analogWrite(enB, 255); // Full speed for right motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}