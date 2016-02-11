const int SENSOR_PIN = 2;
const int LED_PIN = 3;
const int POT_PIN = 0;

bool state;
long last_detection_time;
int number_of_detections;

void setup() {
    // put your setup code here, to run once:
    state = false;
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);

    Serial.println("Initializing Motion Sensor");
    delay(2000);

    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), blink, FALLING);
    Serial.println("Finished initialization");
    last_detection_time = millis();
    number_of_detections = 0;
}

float secondsToMillis(float seconds) {
    return seconds * 1000.0;
}


void loop() {
    // put your main code here, to run repeatedly:

    if (millis() - last_detection_time > 500) {
        digitalWrite(LED_PIN, LOW);
    } else {
        int pot_value = analogRead(POT_PIN);
        analogWrite(LED_PIN, pot_value / 4);
    }
}

void blink() {
    if (millis() - last_detection_time > secondsToMillis(2)) {
        number_of_detections++;
        Serial.print(number_of_detections);
        Serial.println(" DETECTED!!!");
        state = true;
        last_detection_time = millis();
    }

}
