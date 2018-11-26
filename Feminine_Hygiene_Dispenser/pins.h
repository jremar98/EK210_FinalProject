
/*pins.h for pin configuration of Feminine hygiene product dispenser
 * change pin definitions for Arduino here
 * Uncomment pins to enable them
 * NOTE: Digital 0 & 1 Reserved for TX RX i/o operations only
 * 
 * Written by Jordan Remar, November 23, 2018
 */


/*------------------------------------------------------------------------------*/
/*------------------------------//DRV8825 Pins//--------------------------------*/
/*Microstepping Jumper settings (https://www.pololu.com/product/2133) (should be handled by drv8825.h 
      MODE0   MODE1   MODE2   Microstep Resolution
        Low   Low   Low   Full step
        High  Low   Low   Half step
        Low   High  Low   1/4 step
        High  High  Low   1/8 step
        Low   Low   High  1/16 step
        High  Low   High  1/32 step
        Low   High  High  1/32 step
        High  High  High  1/32 step
*/

#define M0_PIN 4 //Mode 0 pin (for microstepping)
#define M1_PIN 5 //Mode 1 pin (for microstepping)
#define M2_PIN 6 //Mode 2 pin (for microstepping)
#define STEP_PIN 7 //Step pin
#define DIR_PIN 8 //Dir pin
#define ENABLE_PIN 2 //En pin to enable stepper (Low-> Enable || High -> Disable)

/*------------------------------------------------------------------------------*/
/*---------------------------//User interface Pins//----------------------------*/
/*------------------------------------------------------------------------------*/
#define PADBUTTON_PIN 3 //Pin for pad dispense button
#define TAMPONBUTTON_PIN -1//Pin for Tampon dispense button


/*------------------------------------------------------------------------------*/
/*-------RS232 Interface pins using MAX203 RS232 ->TTL level shifter----------- */
/*------------------------------------------------------------------------------*/
#define TXPIN 0 
#define RXPIN 1 

/*------------------------------------------------------------------------------*/
/*---------------------------User interface pins------------------------------- */
/*------------------------------------------------------------------------------*/
//#define BUZZER_PIN 3
//#define LOWBAT_LED_PIN 15 
//#define LOWPAD_LED_PIN 16
//#define LOWTAMPON_LED_PIN 17


