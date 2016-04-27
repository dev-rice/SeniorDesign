#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>

// Utility macros
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC

void setup() {
  // put your setup code here, to run once:
  adc_disable();
}

void loop() {
  // put your main code here, to run repeatedly:
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}
