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
  void dispTamponFrontCol(); //Dispense Tampon front column
  void dispTamponBackCol(); //Dispense Tampon back column (prolly can clean this up to make one tampon dispense function with int argument for angle)
  bool buttonPressCheck();//Determine whether button has been pressed
  void runDebug(); //Debug to run stepper without trigger
  void readCard(); //do this later, for now just throwing it in the void loop
  void initialize(); //Initialize all hardware

  private:
  
  
}


#endif
;
