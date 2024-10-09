#include <ESP32Servo.h>  // Include the ESP32Servo library

// arbitrary pin definitions for pushbuttons (idk which ones we are using yet)
const int upButtonPin = 2;
const int downButtonPin = 3;
const int leftButtonPin = 4;
const int rightButtonPin = 5;

// Servos for X and Y axis
Servo servoX;  
Servo servoY;

// Servo pin definitions (arbitrary, idk which ones yet)
const int servoXPin = 13;
const int servoYPin = 14;

// Variables to store servo positions (0 to 180 degrees)
int posX = 90;  // Initial position for X servo (middle)
int posY = 90;  // Initial position for Y servo (middle)

// Step size for servo movement (adjust as needed)
const int stepSize = 5;

void setup() {
  // Attach servos to pins
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  // Set the initial position of both servos
  servoX.write(posX);
  servoY.write(posY);

  // Set pushbutton pins as inputs with pull-up resistors
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
}

void loop() {
  // Read the state of the buttons (LOW when pressed)
  bool upPressed = digitalRead(upButtonPin) == LOW;
  bool downPressed = digitalRead(downButtonPin) == LOW;
  bool leftPressed = digitalRead(leftButtonPin) == LOW;
  bool rightPressed = digitalRead(rightButtonPin) == LOW;

  // Control Y-axis (Up/Down) movement
  if (upPressed && posY < 180) {
    posY += stepSize;  // Move servoY up
  } 
  if (downPressed && posY > 0) {
    posY -= stepSize;  // Move servoY down
  }

  // Control X-axis (Left/Right) movement
  if (leftPressed && posX > 0) {
    posX -= stepSize;  // Move servoX left
  } 
  if (rightPressed && posX < 180) {
    posX += stepSize;  // Move servoX right
  }

  // Write the updated positions to the servos
  servoX.write(posX);
  servoY.write(posY);

  // Small delay to avoid excessive movement (adjust as needed)
  delay(100);
}
