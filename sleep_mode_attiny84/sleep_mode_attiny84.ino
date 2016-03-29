#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/power.h>

const int switchPin                     = 1;
const int statusLED                     = 7;

void setup() {

    pinMode(switchPin, INPUT);
    digitalWrite(switchPin, HIGH);
    pinMode(statusLED, OUTPUT);

    // Flash quick sequence so we know setup has started
    for (int k = 0; k < 10; k = k + 1) {
        if (k % 2 == 0) {
            digitalWrite(statusLED, HIGH);
        } else {
            digitalWrite(statusLED, LOW);
        }
        delay(250);
    }

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void enterSleep(void)
{
  sleep_enable();
  sleep_cpu();
}

void loop() {
    enterSleep();
    digitalWrite(statusLED, HIGH);
    delay(1000);
    digitalWrite(statusLED, LOW);
}
