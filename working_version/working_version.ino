int led_pins[] = {13, 12};

long last_detection_time;
bool detected = false;
bool first = true;

// PIR Constants
const int PIR_PIN = 2;
const int MIN_TIME_BETWEEN_DETECTIONS_S = 5;
const int STARTUP_TIME_S = 5;

// LED Constants
const int NUM_LEDS = 2;
const int LED_FLASH_TIME_MS = 100;

// Solar Panel Constants
const int SOLAR_INPUT_PIN = 4;
const float DARK_THRESH = 1.0;

// Debug LED Constants
const int DEBUG_LED_PIN = 4;

void setup() {
    // Initialize all our output pins
    for (int i = 0; i < NUM_LEDS; ++i) {
        pinMode(led_pins[i], OUTPUT);
    }
    pinMode(DEBUG_LED_PIN, OUTPUT);

    for (int i = 0; i < NUM_LEDS; ++i) {
        digitalWrite(led_pins[i], LOW);
    }

    // Turn the debug LED off at the start
    digitalWrite(DEBUG_LED_PIN, LOW);

    // Initialize last detection time
    last_detection_time = millis();

    // Wait for the PIR to boot up and attach an interrupt for it
    delay(secondsToMillis(STARTUP_TIME_S));
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), onPIRFallingSignal, FALLING);

}

void loop() {
    if (isNighttime()) {
        // Turn the Debug LED on when it is time to detect again
        if (isReadyToDetectAgain(last_detection_time)) {
            digitalWrite(DEBUG_LED_PIN, HIGH);
        } else {
            digitalWrite(DEBUG_LED_PIN, LOW);
        }

        // If we detected an animal, flash the LED
        if (detected) {
            detected = false;
            flashLED();
        }
    } else {
        // Turn the Debug LED off if it is daytime
        digitalWrite(DEBUG_LED_PIN, LOW);
    }
}

void flashLED() {
    // Turn on the LEDs for LED_FLASH_TIME_MS
    for (int i = 0; i < NUM_LEDS; ++i) {
        digitalWrite(led_pins[i], HIGH);
    }
    delay(LED_FLASH_TIME_MS);

    // Then turn them off
    for (int i = 0; i < NUM_LEDS; ++i) {
        digitalWrite(led_pins[i], LOW);
    }
}

bool isNighttime() {
    // Read the solar panel adc value
    int solar_adc = analogRead(SOLAR_INPUT_PIN);
    // Convert into a voltage
    float solar_voltage = 5.0 * solar_adc / 1024.0;

    return solar_voltage < DARK_THRESH;
}

float secondsToMillis(float seconds) {
    return seconds * 1000.0;
}

bool isReadyToDetectAgain(long last_detection_time) {
    return (millis() - last_detection_time) > secondsToMillis(MIN_TIME_BETWEEN_DETECTIONS_S);
}

void onPIRFallingSignal() {
    if (isReadyToDetectAgain(last_detection_time)) {
        detected = true;
        last_detection_time = millis();
    }

    // Ignore the first detection
    if (first) {
        first = false;
        detected = false;
    }

}
