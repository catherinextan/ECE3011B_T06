/****************************************************************************
 This is a script to show simple opening graphics for Tilted tunnels. A STEAM
 Robot designed and built for ECE 3011. 

 This script is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Written by Shyra LaGarde,
 with contributions from TA Finn.
 ***************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SDA 21
#define SCL 22

#define OLED_RESET -1 // Reset pin
#define SCREEN_ADDRESS 0x3C // 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUZZER_PIN 4  // GPIO pin connected to the buzzer

// Define tone frequencies and durations for the enhanced Labyrinth-inspired melody
int frequencies[] = {294, 349, 392, 349, 330, 294, 247, 294, 392, 330, 294, 349};  // Lower, haunting notes in Hz
int durations[] = {600, 400, 500, 400, 600, 700, 500, 600, 500, 400, 700, 800};    // Varied durations in ms

// Function to play a tone at a specific frequency and duration
void playTone(int pin, int frequency, int duration) {
    int delayTime = 1000000 / (frequency * 2);  // Calculate delay between toggles for the frequency
    int cycles = frequency * duration / 1000;   // Calculate number of cycles for the duration

    for (int i = 0; i < cycles; i++) {
        digitalWrite(pin, HIGH);    // Turn buzzer on
        delayMicroseconds(delayTime);
        digitalWrite(pin, LOW);     // Turn buzzer off
        delayMicroseconds(delayTime);
    }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(SDA, SCL);
  //pinMode(BUZZER_PIN, OUTPUT);


  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}


void loop() {
  // Clear the display and start animations in a loop
  display.clearDisplay();

  testdrawline();
  testdrawstyles();
  testfillrect();
  testfillcircle();
  testfillroundrect();
  testfilltriangle();
  testscrolltext();

  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  // Play the enhanced Labyrinth-inspired melody
  for (int i = 0; i < sizeof(frequencies) / sizeof(frequencies[0]); i++) {
      playTone(BUZZER_PIN, frequencies[i], durations[i]);
      delay(150);  // Slightly longer pause between notes
  }
  delay(1500); // Longer pause before repeating the melody
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Welcome to"));

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Tilted"));
  display.println(F("Tunnels"));

  display.display();
  delay(2000);
}

void testdrawline() {
  int16_t i;
  display.clearDisplay(); // Clear display buffer

  for (i = 0; i < display.width(); i += 4) {
    display.drawLine(0, 0, i, display.height() - 1, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for (i = 0; i < display.height(); i += 4) {
    display.drawLine(0, 0, display.width() - 1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for (i = 0; i < display.width(); i += 4) {
    display.drawLine(0, display.height() - 1, i, 0, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for (i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(0, display.height() - 1, display.width() - 1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for (i = display.width() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, i, 0, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for (i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, 0, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for (i = 0; i < display.height(); i += 4) {
    display.drawLine(display.width() - 1, 0, 0, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for (i = 0; i < display.width(); i += 4) {
    display.drawLine(display.width() - 1, 0, i, display.height() - 1, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(1000); // Pause for 1 second
}

void testfillrect(void) {
  display.clearDisplay();

  for (int16_t i = 0; i < display.height() / 2; i += 3) {
    display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }
  delay(1500);
}

void testfillcircle(void) {
  display.clearDisplay();

  for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 3) {
    display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(1500);
}

void testfillroundrect(void) {
  display.clearDisplay();

  for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
    display.fillRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
                          display.height() / 4, SSD1306_INVERSE);
    display.display();
    delay(1);
  }

  delay(1500);
}

void testfilltriangle(void) {
  display.clearDisplay();

  for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 5) {
    display.fillTriangle(
      display.width() / 2, display.height() / 2 - i,
      display.width() / 2 - i, display.height() / 2 + i,
      display.width() / 2 + i, display.height() / 2 + i, SSD1306_INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("Dont Fall"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}
