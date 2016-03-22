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
  
  for (int i = 0; i < 10; ++i) {
    digitalWrite(debug_pin, LOW);
    delay(100);
    digitalWrite(debug_pin, HIGH);
    delay(200);
  }


}



void loop() {
    for(int i = 0; i < 7; ++i) {
      digitalWrite(led_pins[i], LOW); 
    }
    delay(1000);
    for(int i = 0; i < 7; ++i) {
      digitalWrite(led_pins[i], HIGH); 
    }
    delay(10);
   
}
