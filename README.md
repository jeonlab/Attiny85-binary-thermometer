# Attiny85-binary-thermometer
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
