//----------------//DRV8825 Pins//------------------//

#define M0_PIN 4 //Mode 0 pin
#define M1_PIN 5 //Mode 1 pin
#define M2_PIN 6 //Mode 2 pin
#define STEP_PIN 7 //Step pin
#define DIR_PIN 8 //Dir pin
#define PAD_STEPPER_EN_PIN 3//Pin for enable pin of Pad dispensing stepper
#define TAMPON_STEPPER_EN_PIN 10 //Pin for enable pin of Tampon dispensing stepper



//----------------//User interface Pins//---------------//
#define BUTTON_PIN A0 //Pin for buttons (one pin setup for analogRead)


//----------------//Piezo Buzzer Pin//------------------//

//#define BUZZER_PIN 3


//----------------//Card Reader Pins//------------------//
#define CARD_READER_TX_PIN 6 //Might want to change these to different digital I/O pins if serial connection to computer doesnt work
#define CARD_READER_RX_PIN 7

//----------------//LED Pins//------------------//
//#define LOWBAT_LED_PIN 15
#define LOWPAD_LED_PIN 16
#define LOWTAMPON_LED_PIN 17


