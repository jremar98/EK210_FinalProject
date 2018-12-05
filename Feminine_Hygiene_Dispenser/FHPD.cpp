/* 
 *  FHPD.cpp - functions for controlling a Arduino based feminine hygiene product dispenser
 *  Written by Jordan Remar, November 1, 2018
 */

 #include <Arduino.h>
 #include "FHPD.h"
 #include <DRV8825.h>//DRV8825 
 #include "config.h"
 #include "pins.h"

//Call format for DRV8825 Stepper Library (from LaurB9): DRV8825(short steps, short dir_pin, short step_pin, short mode0_pin, short mode1_pin, short mode2_pin);

DRV8825 stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN, M0_PIN, M1_PIN, M2_PIN); //Initiallize DRV8825/NEMA17's (differentiating with enable pins, everything else is in parallel

 
FHPD::FHPD()
{
  initialize(); //Run initialization function
}

void FHPD::initialize()
{
    
    stepper.begin(RPM); //Begin stepper
    stepper.enable(); //Turn On stepper
    digitalWrite(TAMPON_STEPPER_EN_PIN, HIGH); // Disable tampon DRV8825 and Stepper
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable Pad DRV8825 and Stepper

    
    /*--------------set pinmodes-----------------*/
    
}

void FHPD::dispPad() 
{
    stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to defined 
    digitalWrite(TAMPON_STEPPER_EN_PIN, HIGH); // Disable tampon DRV8825 and Stepper
    digitalWrite(PAD_STEPPER_EN_PIN, LOW); // Enable Pad DRV8825 and Stepper
    
    stepper.rotate(PAD_ANGLE_NEEDED-PAD_OVERSTEP);    // reverse revolution
    delay(50);// let the dust settle
    stepper.rotate(PAD_OVERSTEP);//Clear overstep
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
    Serial.println("Dispensed Pad");
  }  

void FHPD::dispTamponFrontCol() //Dispense tampon from front column
{
    stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to defined 
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable tampon DRV8825 and Stepper
    digitalWrite(TAMPON_STEPPER_EN_PIN, LOW); // Enable Pad DRV8825 and Stepper
    
    stepper.rotate(TAMPON_FRONT_ANGLE_NEEDED+TAMPON_OVERSTEP);    // dispense tampon 
    stepper.rotate(-TAMPON_OVERSTEP); //Clear out overstep angle
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
    Serial.println("Dispensed Tampon from front column");
}


void FHPD::dispTamponBackCol()
{
    stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to defined 
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable tampon DRV8825 and Stepper
    digitalWrite(TAMPON_STEPPER_EN_PIN, LOW); // Enable Pad DRV8825 and Stepper
    
    stepper.rotate(TAMPON_BACK_ANGLE_NEEDED+TAMPON_OVERSTEP);    // dispense tampon 
    delay(50);// let the dust settle
    stepper.rotate(-TAMPON_OVERSTEP); //Clear out overstep angle
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
    Serial.println("Dispensed Tampon from back column");
}

bool FHPD::buttonPressCheck() //IRRELEVANT, DON'T USE
{
  
  int buttonState = digitalRead(BUTTON_PIN);
  if(buttonState == HIGH)
  {
    return 1;
  }
  else 
  {
    return 0;
  }
  
}

void FHPD::runDebug()
{

    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
    digitalWrite(TAMPON_STEPPER_EN_PIN, HIGH);
    Serial.println("Microstepping set to 1:8");
    stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to 1:8
    delay(1000);


    Serial.println("Rotating Pad Stepper");
    Serial.println("Turning on Motor");
    digitalWrite(PAD_STEPPER_EN_PIN, LOW); // Enable DRV8825 and Stepper
    stepper.rotate(PAD_ANGLE_NEEDED);     // forward revolution
    Serial.println("Turning off Motor");
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
    

    delay(2000);
    Serial.println("Rotating stepper CW");
    Serial.println("Turning on Motor");
    digitalWrite(TAMPON_STEPPER_EN_PIN, LOW); // Enable DRV8825 and Stepper
    delay(1000);
    stepper.rotate(TAMPON_FRONT_ANGLE_NEEDED);    // reverse revolution
    Serial.println("Turning off Motor");
    digitalWrite(TAMPON_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
    delay(2000);

}

