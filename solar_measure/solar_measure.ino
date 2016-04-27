// Hook up positive battery terminal to A0
const int BATTERY_INPUT_PIN = 0;

// Sampling Period in milliseconds
const int SAMPLE_TIME_MS = 1000;

// Keep track of time
unsigned long current_time = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int battery_adc = analogRead(BATTERY_INPUT_PIN);
  float battery_voltage = 5.0 * battery_adc / 1024.0;

  Serial.print(current_time);
  Serial.print("\t");
  Serial.println(battery_voltage);

  current_time += SAMPLE_TIME_MS;
  
  delay(SAMPLE_TIME_MS);
  
}
