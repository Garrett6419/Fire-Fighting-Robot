#define ir_R A0 // Right IR sensor
#define ir_F A1 // Front IR sensor
#define ir_L A2 // Left IR sensor
#define smokeDetectorPin 11 // Smoke detector pin
#define buzzerPin 12 // Buzzer pin
#define fireIndicatorPin 2 // Pin for fire indicator LED
#define smokeIndicatorPin 3 // Pin for smoke indicator LED

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(ir_R, INPUT);
  pinMode(ir_F, INPUT);
  pinMode(ir_L, INPUT);
  pinMode(smokeDetectorPin, INPUT); // Initialize smoke detector pin
  pinMode(buzzerPin, OUTPUT); // Initialize buzzer pin
  pinMode(fireIndicatorPin, OUTPUT); // Initialize fire indicator LED pin
  pinMode(smokeIndicatorPin, OUTPUT); // Initialize smoke indicator LED pin
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
  if (s1 < 250 || s2 < 350 || s3 < 250) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer when fire is detected
    digitalWrite(fireIndicatorPin, HIGH); // Turn on fire indicator LED
  } 
  // Smoke detection logic
  else if (smokeValue == HIGH) {
    digitalWrite(buzzerPin, HIGH); // Activate buzzer when smoke is detected
    digitalWrite(smokeIndicatorPin, HIGH); // Turn on smoke indicator LED
  } 
  else {
    digitalWrite(buzzerPin, LOW); // Deactivate buzzer when no fire or smoke is detected
    digitalWrite(fireIndicatorPin, LOW); // Turn off fire indicator LED
    digitalWrite(smokeIndicatorPin, LOW); // Turn off smoke indicator LED
  }
  
  delay(10);
}