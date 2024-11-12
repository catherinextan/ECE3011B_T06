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
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
    // Play the enhanced Labyrinth-inspired melody
    for (int i = 0; i < sizeof(frequencies) / sizeof(frequencies[0]); i++) {
        playTone(BUZZER_PIN, frequencies[i], durations[i]);
        delay(150);  // Slightly longer pause between notes
    }
    delay(1500); // Longer pause before repeating the melody
}
