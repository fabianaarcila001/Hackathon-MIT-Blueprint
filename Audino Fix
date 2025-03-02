#include <Arduino.h>

// Joystick Pins
int x_pin = A0;
int y_pin = A1;
int sw_pin = 2;

// LED Structs
typedef struct {
    int LED[6];
} RedLED;

typedef struct {
    int LED[4];
} WhiteLED;

// Assign LED Pins
RedLED red = {{13, 12, 11, 10, 9, 8}};
WhiteLED white = {{7, 6, 5, 4}};

// Sound & Light Control
#define BUZZER_PIN 3
int Brightness = 0;
int FadeAmount = 5;
bool ENDGAME = false;

// Function Prototypes
void playTone(int frequency, int duration);
void horrorSting();
void deepPulses();
void setRedLEDs(int brightness);
void setWhiteLEDs(int state);
void triggerlightshow();

void setup() {
    Serial.begin(9600);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(x_pin, INPUT);
    pinMode(y_pin, INPUT);
    pinMode(sw_pin, INPUT_PULLUP);

    // Initialize LED Pins
    for (int i = 0; i < 6; i++) pinMode(red.LED[i], OUTPUT);
    for (int i = 0; i < 4; i++) pinMode(white.LED[i], OUTPUT);

    Serial.println("Waiting for 'end' command...");
}

void loop() {
    if (Serial.available() > 0) {
        String userInput = Serial.readStringUntil('\n');
        userInput.trim();
        userInput.toLowerCase();

        Serial.print("Received: ");
        Serial.println(userInput);

        if (userInput.equals("end")) {
            ENDGAME = true;
            Serial.println("ENDGAME mode activated! Light show starting...");
        }
    }

    if (ENDGAME) {
        triggerlightshow();
        ENDGAME = false;
        Serial.println("Light show completed!");
    }
}

// Light Show with Parallel Sound
void triggerlightshow() {
    int repetitions = 10;

    // Start LED Fade-In and Play Sound Simultaneously
    setWhiteLEDs(HIGH);
    for (int value = 0; value <= 255; value += FadeAmount) {
        setRedLEDs(value);
        tone(BUZZER_PIN, 200 + value, 20);  // Increasing pitch
        delay(30);
    }

    // Start LED Fade-Out and Lower Sound
    setWhiteLEDs(LOW);
    for (int value = 255; value >= 0; value -= FadeAmount) {
        setRedLEDs(value);
        tone(BUZZER_PIN, 400 - value, 20);  // Decreasing pitch
        delay(30);
    }

    setRedLEDs(LOW);
    setWhiteLEDs(LOW);
    delay(500);
    noTone(BUZZER_PIN);  // Stop sound

    // Step 2: Flashing LEDs in Parallel with Beeps
    for (int i = 0; i < repetitions; i++) {
        setRedLEDs(HIGH);
        setWhiteLEDs(LOW);
        tone(BUZZER_PIN, 600, 100);  // High-pitched beep
        delay(500);

        setRedLEDs(LOW);
        setWhiteLEDs(HIGH);
        tone(BUZZER_PIN, 300, 100);  // Lower-pitched beep
        delay(500);
    }

    setRedLEDs(LOW);
    setWhiteLEDs(LOW);
    noTone(BUZZER_PIN);
}

//Function to Play Sound
void playTone(int frequency, int duration) {
    tone(BUZZER_PIN, frequency, duration);
}

// Function for Eerie Horror Sound
void horrorSting() {
    for (int freq = 800; freq > 100; freq -= 50) {
        playTone(freq, 50);
        delay(30);
    }
}

//Function for Deep Pulses
void deepPulses() {
    for (int i = 0; i < 3; i++) {
        playTone(60, 500);
        delay(200);
    }
}

//Function to Control Red LEDs
void setRedLEDs(int brightness) {
    for (int i = 0; i < 6; i++) {
        analogWrite(red.LED[i], brightness);
    }
}

//Function to Control White LEDs
void setWhiteLEDs(int state) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(white.LED[i], state);
    }
}
