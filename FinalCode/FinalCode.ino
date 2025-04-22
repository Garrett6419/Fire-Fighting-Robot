#define enA   10  // Enable1 L298 Pin enA
#define in1   9   // Motor1 L298 Pin in1
#define in2   8   // Motor1 L298 Pin in2
#define in3   7   // Motor2 L298 Pin in3
#define in4   6   // Motor2 L298 Pin in4
#define enB   5   // Enable2 L298 Pin enB
#define ir_R   A0  // Right fire sensor
#define ir_F   A1  // Front fire sensor
#define ir_L   A2  // Left fire sensor
#define smokeDetector A4 // Smoke detector pin
#define servo   3   // Servo motor pin
#define pump    11  // Pump pin
#define buzzer   4  // Buzzer pin

int Speed = 255; // 0-255
int PumpPower = 140; // 0-255
int s1, s2, s3, smokeDetected;

void setup() {
    Serial.begin(9600); 
    pinMode(ir_R, INPUT); 
    pinMode(ir_F, INPUT); 
    pinMode(ir_L, INPUT); 
    pinMode(smokeDetector, INPUT); 
    pinMode(enA, OUTPUT); 
    pinMode(in1, OUTPUT); 
    pinMode(in2, OUTPUT); 
    pinMode(in3, OUTPUT); 
    pinMode(in4, OUTPUT); 
    pinMode(enB, OUTPUT); 
    pinMode(servo, OUTPUT); 
    pinMode(pump, OUTPUT); 
    pinMode(buzzer, OUTPUT); 

    // Initialize servo position
    for (int angle = 90; angle <= 140; angle += 5) {
        servoPulse(servo, angle);
    }
    for (int angle = 140; angle >= 40; angle -= 5) {
        servoPulse(servo, angle);
    }
    for (int angle = 40; angle <= 95; angle += 5) {
        servoPulse(servo, angle);
    }
    analogWrite(enA, Speed); 
    analogWrite(enB, Speed); 
    delay(500);
}

void loop() {
    s1 = analogRead(ir_R);
    s2 = analogRead(ir_F);
    s3 = analogRead(ir_L);
    smokeDetected = analogRead(smokeDetector);

    // Check for smoke detection
    if (smokeDetected < 250) {
        digitalWrite(buzzer, HIGH); // Activate buzzer
        circleForSmoke(); // Circle for 30 seconds
    } else {
        digitalWrite(buzzer, LOW); // Deactivate buzzer
    }

    //=============================================================
    // Auto Control
    //=============================================================
    Serial.print(s1);
    Serial.print("\t");
    Serial.print(s2);
    Serial.print("\t");
    Serial.println(s3);
    delay(50);

    if (s1 < 250) {
        Stop();
        digitalWrite(pump, HIGH);
        analogWrite(pump, PumpPower); 
        activateServo();
    } else if (s2 < 350) {
        Stop();
        digitalWrite(pump, HIGH);
        analogWrite(pump, PumpPower); 
        activateServo();
    } else if (s3 < 250) {
        Stop();
        digitalWrite(pump, HIGH);
        analogWrite(pump, PumpPower);
        activateServo();
    } else if (s1 >= 251 && s1 <= 700) {
        digitalWrite(pump, LOW);
        backword();
        delay(100);
        turnRight();
        delay(200);
    } else if (s2 >= 251 && s2 <= 800) {
        digitalWrite(pump, LOW);
        forword();
    } else if (s3 >= 251 && s3 <= 700) {
        digitalWrite(pump, LOW);
        backword();
        delay(100);
        turnLeft();
        delay(200);
    } else {
        digitalWrite(pump, LOW);
        Stop();
    }
    delay(10);
}

void circleForSmoke() {
    unsigned long startTime = millis();
    while (millis() - startTime < 30000) { // Circle for 30 seconds
        turnRight();
        delay(100);
        turnLeft();
        delay(100);
    }
    Stop(); 
}

void activateServo() {
    for (int angle = 90; angle >= 40; angle -= 3) {
        servoPulse(servo, angle);
    }
    for (int angle = 40; angle <= 90; angle += 3) {
        servoPulse(servo, angle);
    }
}

void servoPulse(int pin, int angle) {
    int pwm = (angle * 11) + 500; // Convert angle to microseconds
    digitalWrite(pin, HIGH);
    delayMicroseconds(pwm);
    digitalWrite(pin, LOW);
    delay(50); // Refresh cycle of servo
}

void forword() {
    digitalWrite(in1, HIGH); // Right Motor forward Pin
    digitalWrite(in2, LOW); // Right Motor backward Pin
    digitalWrite(in3, LOW); // Left Motor backward Pin
    digitalWrite(in4, HIGH); // Left Motor forward Pin
}

void backword() {
    digitalWrite(in1, LOW); // Right Motor forward Pin
    digitalWrite(in2, HIGH); // Right Motor backward Pin
    digitalWrite(in3, HIGH); // Left Motor backward Pin
    digitalWrite(in4, LOW); // Left Motor forward Pin
}

void turnRight() {
    digitalWrite(in1, LOW); // Right Motor forward Pin
    digitalWrite(in2, HIGH); // Right Motor backward Pin
    digitalWrite(in3, LOW); // Left Motor backward Pin
    digitalWrite(in4, HIGH); // Left Motor forward Pin
}

void turnLeft() {
    digitalWrite(in1, HIGH); // Right Motor forward Pin
    digitalWrite(in2, LOW); // Right Motor backward Pin
    digitalWrite(in3, HIGH); // Left Motor backward Pin
    digitalWrite(in4, LOW); // Left Motor forward Pin
}

void Stop() {
    digitalWrite(in1, LOW); // Right Motor forward Pin
    digitalWrite(in2, LOW); // Right Motor backward Pin
    digitalWrite(in3, LOW); // Left Motor backward Pin
    digitalWrite(in4, LOW); // Left Motor forward Pin
}