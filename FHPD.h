/*FPHD.h - Library for feminine hygiene product dispenser. 
 * Created by Jordan Remar, November 1,2018
 * Released under MIT License
 */

#ifndef FHPD_h
#define FHPD_h

#include "arduino.h"

class FHPD
{
  public:
  FHPD(); //Class Constructor
  void dispPad(); //Dispense Pad
  void dispTampon(); //Dispense Tampon
  bool buttonPressCheck();//Determine whether button has been pressed
  void runDebug(); //Debug to run stepper without trigger
  

  private:
  void initialize(); //Initialize all hardware
  
}


#endif
;
