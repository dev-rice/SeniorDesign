const int SENSOR_PIN = 2;
const int LED_PIN = 4;
const int LED_DEBUG_PIN = 13;
const int POT_PIN = 0;

bool state;
long last_detection_time;
int number_of_detections;

void setup() {
    // put your setup code here, to run once:
    state = false;
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_DEBUG_PIN, OUTPUT);
    Serial.begin(9600);

    pinMode(SENSOR_PIN, INPUT_PULLUP);

    Serial.println("Initializing Motion Sensor");
    last_detection_time = millis();
    //delay(10000);

    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), blink, FALLING);
    Serial.println("Finished initialization");

    number_of_detections = 0;
}

float secondsToMillis(float seconds) {
    return seconds * 1000.0;
}


void loop() {
    // put your main code here, to run repeatedly:

    if (isReadyToDetectAgain(last_detection_time)) {
        digitalWrite(LED_DEBUG_PIN, HIGH);
    } else {
        digitalWrite(LED_DEBUG_PIN, LOW);
    }

    if (millis() - last_detection_time > 500) {
        digitalWrite(LED_PIN, LOW);
    } else {
        int pot_value = analogRead(POT_PIN);
        analogWrite(LED_PIN, pot_value / 4);
    }
}

bool isReadyToDetectAgain(long last_detection_time) {
    return (millis() - last_detection_time) > secondsToMillis(0.25);
}

void blink() {
    if (isReadyToDetectAgain(last_detection_time)) {
        number_of_detections++;
        Serial.print(number_of_detections);
        Serial.println(" DETECTED!!!");
        state = true;
        last_detection_time = millis();
    }

}
