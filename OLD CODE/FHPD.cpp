/* 
 *  FHPD.cpp - functions for controlling a Arduino based feminine hygiene product dispenser
 *  Written by Jordan Remar, November 1, 2018
 */

 #include <Arduino.h>
 #include "FHPD.h"
 #include <DRV8825.h>//DRV8825 
 #include "config.h"
 #include "pins.h"

DRV8825 stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN, ENABLE_PIN, M0_PIN, M1_PIN, M2_PIN); //Initiallize DRV8825/NEMA17

 
FHPD::FHPD()
{
  initialize(); //Run initialization function
}

void FHPD::initialize()
{
    
    stepper.begin(RPM); //Begin stepper
    stepper.enable(); //Turn On stepper
    digitalWrite(ENABLE_PIN,HIGH); // Disable DRV8825 and Stepper 

    
    /*--------------set pinmodes-----------------*/
    #ifdef PADBUTTON_PIN
      pinMode(PADBUTTON_PIN,INPUT); //declare button pin as input
      #else
      Serial.println("Warning, Pad Dispense Button Not defined!");
      #endif

    #ifdef TAMPONBUTTON_PIN
      pinMode(TAMPONBUTTON_PIN,OUTPUT);
      #else
      Serial.println("Warning, Tampon Dispense Button Not defined!");
      #endif
      
    #ifdef BUZZER_PIN
      pinMode(BUZZER_PIN, OUTPUT);
      #endif

    #ifdef LOWBAT_LED_PIN
      pinMode(LOWBAT_LED_PIN,OUTPUT);
      #else
      Serial.println("Warning, Low Battery LED pin Not Defined!");
      #endif
      
    #ifdef LOWPAD_LED_PIN
      pinMode(LOWPAD_LED_PIN,OUTPUT);
      #else
      Serial.println("Warning, Low pad LED pin Not Defined!");
      #endif

    #ifdef LOWTAMPON_LED_PIN
      pinMode(LOWTAMPON_LED_PIN,OUTPUT);
      #else
      Serial.println("Warning, Low Tampon LED pin Not Defined!");
      #endif

    Serial.println("Initialization Complete");
    
}

void FHPD::dispPad() 
{
    stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to defined 
    digitalWrite(ENABLE_PIN, LOW); // Enable DRV8825 and Stepper
    stepper.rotate(-PAD_ANGLE_NEEDED-PAD_OVERSTEP);    // reverse revolution
    stepper.rotate(PAD_OVERSTEP); //Rotate stepper to angle needed (and remove offset)
    digitalWrite(ENABLE_PIN, HIGH); // Disable DRV8825 and Stepper
    Serial.println("Dispensed Pad");
  }  

void FHPD::dispTampon()
{
  //Place Holder for now...
}

bool FHPD::buttonPressCheck()
{
  
  int buttonState = digitalRead(PADBUTTON_PIN); //Check for button press
  if(buttonState == HIGH) //If Button pressed
  {
    return 1; 
  }
  else 
  {
    return 0;
  }
  
}

void FHPD::runStepperDebug() //Run for debugging of stepper motor by bypassing controls
{

    digitalWrite(ENABLE_PIN, LOW); // Disable DRV8825 and Stepper
    Serial.println("Microstepping set to 1:8");
    stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to 1:8
    delay(1000);

    Serial.println("Rotating stepper CCW");
    Serial.println("Turning on Motor");
    digitalWrite(ENABLE_PIN, LOW); // Enable DRV8825 and Stepper
    stepper.rotate(PAD_ANGLE_NEEDED);     // forward revolution
    Serial.println("Turning off Motor");
    digitalWrite(ENABLE_PIN, HIGH); // Disable DRV8825 and Stepper


    delay(2000);
    Serial.println("Rotating stepper CW");
    Serial.println("Turning on Motor");
    digitalWrite(ENABLE_PIN, LOW); // Enable DRV8825 and Stepper
    delay(1000);
    stepper.rotate(PAD_ANGLE_NEEDED);    // reverse revolution
    Serial.println("Turning off Motor");
    digitalWrite(ENABLE_PIN, HIGH); // Disable DRV8825 and Stepper
    delay(2000);

}

