/* ATtiny85V Binary Flashing Thermometer
 *  
 *  Jinseok Jeon (JeonLab)
 *  http://jeonlab.wordpress.com
 *  
 *  This is a modified version of the Flashing Thermometer that is originally
 *  made by David Johnson-Davies - http://www.technoblogy.com/show?ZSX
 *  
 *  David's brilliant original version
 *    - Power saving by utilizing sleep mode of ATtiny85V
 *    - Negabinary to show negative temperature in celcius
 *    
 *  My modified version
 *    - Specially designed 2 BJT transistor auto power off circuit (disconnect battery)
 *    - Normal binary system: less digits & easy to convert
 *    - For negative temperature: both LEDs blinks briefly before flashing positive number
 *    
 *  Hardware: 
 *    - ATtiny85V: 1 MHz internal oscillator, BOD disabled
 *    - 2x LEDs
 *    - 1x PNP TR (2N3906), 1x NPN TR (2N3904)
 *    - 3x 1k resistors
 *    - 1x 0.1uF cap
 *    - 1x push button switch
 *    
 *  CC BY 4.0
 *  Licensed under a Creative Commons Attribution 4.0 International license:
 *  http://creativecommons.org/licenses/by/4.0/
*/

#include <avr/sleep.h>

const int red = 0;        // PB0
const int green = 1;      // PB1
const int pwrTR = 2;      // PB2

int Temp;

// Read temperature **********************************************
int ReadADC() {
  ADCSRA = ADCSRA | 1 << ADEN;             // Enable ADC
  set_sleep_mode(SLEEP_MODE_ADC);
  sleep_enable();
  sleep_cpu();                             // Go into ADC noise reduction mode
  int low, high;
  low = ADCL;
  high = ADCH;
  return (high << 8 | low);
}

ISR(ADC_vect) {  //   ADC conversion complete
}

// Flash 10-bit integer value, skipping leading zeros
void Flash (unsigned int value) {
  int i = 9, colour;
  boolean b, show = false;
  do {
    b = value >> i & 1;
    if (show || b || (i == 0)) {
      if (value >> i & 1) colour = red; else colour = green;
      digitalWrite(colour, HIGH);
      delay(15);                              // 15ms flash
      digitalWrite(colour, LOW);
      delay(400);                             // 400ms gap
      show = true;
    }
    i--;
  } while (i >= 0);
}

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(pwrTR, OUTPUT);
  digitalWrite(pwrTR, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  // Set up ADC for temperature
  ADMUX = 0 << REFS2 | 2 << REFS0 | 15 << MUX0; // temperature and 1.1V reference
  ADCSRA = 1 << ADEN | 1 << ADIE | 3 << ADPS0; // enable ADC, interrupt, 125kHz ADC clock
  delay(1000);
  Temp = (ReadADC() * 31 - 8837) / 33;
  // If the temperature is below 0degC, both LEDs blinks for 400ms
  if (Temp < 0) {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    delay(400);
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    delay(400);
    Temp = -Temp;
  }
  Flash(Temp);
  digitalWrite(pwrTR, LOW);
}

void loop() {
}
