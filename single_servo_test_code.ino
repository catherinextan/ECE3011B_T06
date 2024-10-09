#include <ESP32Servo.h>  // Include the ESP32Servo library

Servo myServo;  // Create a Servo object

int servoPin = 13;  // Define the pin connected to the servo signal (you can change this to your pin)
int delayTime = 1000;  // Delay time between movements (in milliseconds)

void setup() {
  myServo.attach(servoPin);  // Attach the servo to the defined pin
}

void loop() {
  // Rotate 90 degrees clockwise
  myServo.write(90);  // Move to 90 degrees position
  delay(delayTime);   // Wait for 1 second

  // Rotate back to the neutral position (0 degrees)
  myServo.write(0);  // Move to 0 degrees position
  delay(delayTime);  // Wait for 1 second

  // Rotate 90 degrees anti-clockwise
  myServo.write(180);  // Move to 180 degrees (if your servo can rotate that much)
  delay(delayTime);    // Wait for 1 second
}
