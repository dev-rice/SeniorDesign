int led_pins[] = {13, 12, 11, 10, 8, 9, 3};
int debug_pin = 4;
int num_leds = 0;
int potentiometer_pin = 4;
int sensor_pin = 2;

int number_of_detections = 0;
long last_detection_time;
bool state = false;

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  for (int i = 0; i < 7; ++i) {
    pinMode(led_pins[i], OUTPUT);
  }
  pinMode(debug_pin, OUTPUT);

  for (int i = 0; i < 7; ++i) {
    digitalWrite(led_pins[i], LOW);
  }

  digitalWrite(debug_pin, LOW);

  last_detection_time = millis();
  
  Serial.println("Initializing Motion Sensor");
  delay(10000);
  attachInterrupt(digitalPinToInterrupt(sensor_pin), blink, FALLING);

  Serial.println("Finished initialization");
  
}



void loop() {
  int pot_value = analogRead(potentiometer_pin);
  num_leds = (pot_value / 170) + 1;

  if (isReadyToDetectAgain(last_detection_time)) {
    digitalWrite(debug_pin, HIGH);
  } else {
    digitalWrite(debug_pin, LOW);
  }

  if (state) {
    state = false;
    for (int i = 0; i < num_leds; ++i) {
      digitalWrite(led_pins[i], HIGH);
    }
    digitalWrite(debug_pin, HIGH);

    delay(50);

    for (int i = 0; i < num_leds; ++i) {
      digitalWrite(led_pins[i], LOW);
    }
    digitalWrite(debug_pin, LOW);

    delay(2000);
  }

   
}

float secondsToMillis(float seconds) {
    return seconds * 1000.0;
}

bool isReadyToDetectAgain(long last_detection_time) {
    return (millis() - last_detection_time) > secondsToMillis(10);
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
