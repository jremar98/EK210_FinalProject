/*
Written by Jordan Remar
*/
#include <SPI.h> //SPI

/*Include Local Header Files*/
#include "FHPD.h"
#include "pins.h"
#include "config.h"

FHPD dispenser = FHPD(); //declare dispenser object as global



void setup()
{
  
  Serial.begin(9600);   // Initiate a serial communication

}


void loop()
{
  bool buttonStatus = dispenser.buttonPressCheck();
  if(buttonStatus == 1)
  {
    dispenser.dispPad();
  }
  
 }



















