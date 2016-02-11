const int LED_PIN = 3;
const int POT_PIN = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pot_value = analogRead(POT_PIN);
  analogWrite(LED_PIN, pot_value / 4);
}
