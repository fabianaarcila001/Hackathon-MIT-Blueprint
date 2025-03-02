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

    Serial.println("Waiting for 'end' command from Python...");
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

// 🔥 Light Show Function
void triggerlightshow() {
    int repetitions = 10;

    deepPulses();
    horrorSting();
    playTone(50, 1500);

    setWhiteLEDs(HIGH);
    for (int value = 0; value <= 255; value += FadeAmount) {
        setRedLEDs(value);
        delay(30);
    }

    setWhiteLEDs(LOW);
    for (int value = 255; value >= 0; value -= FadeAmount) {
        setRedLEDs(value);
        delay(30);
    }

    setRedLEDs(LOW);
    setWhiteLEDs(LOW);
    delay(500);

    for (int i = 0; i < repetitions; i++) {
        setRedLEDs(HIGH);
        setWhiteLEDs(LOW);
        playTone(200, 300);
        delay(500);

        setRedLEDs(LOW);
        setWhiteLEDs(HIGH);
        playTone(400, 300);
        delay(500);
    }

    setRedLEDs(LOW);
    setWhiteLEDs(LOW);
}

// ✅ Sound Functions
void playTone(int frequency, int duration) {
    tone(BUZZER_PIN, frequency, duration);
    delay(duration * 1.3);
}

void horrorSting() {
    for (int freq = 800; freq > 100; freq -= 50) {
        playTone(freq, 100);
    }
}

void deepPulses() {
    for (int i = 0; i < 3; i++) {
        playTone(60, 500);
        delay(200);
    }
}

// ✅ LED Functions
void setRedLEDs(int brightness) {
    for (int i = 0; i < 6; i++) {
        analogWrite(red.LED[i], brightness);
    }
}

void setWhiteLEDs(int state) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(white.LED[i], state);
    }
}
