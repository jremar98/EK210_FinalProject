/*config.h file for Feminine hygiene product dispenser
 * Change definintions here to configure software
 * 
 * Written by Jordan Remar, November 23,2018
 * 
 */


///////////////////////////////////////////////////////////
//--------------------User Parameters--------------------//
///////////////////////////////////////////////////////////

#define BUTTON_DEBOUNCE 500 //Debounce time for buttons to prevent button bounce 


///////////////////////////////////////////////////////////
//--------------------Stepper Parameters-----------------//
///////////////////////////////////////////////////////////

#define RPM 200 //Speed of stepper motor 
#define MOTOR_STEPS 200 //Steps per revolution of stepper motor -> NEMA 17: 1.8deg/step (at full steps)
#define MICROSTEPPING 8 //Set microstepping (1,2,4,8,16,32) of DRV8825

//////////////////////////////////////////////////////////////
//--------------------Dispensing Parameters-----------------//
//////////////////////////////////////////////////////////////
#define PAD_ANGLE_NEEDED -120 // Angle needed for stepper to dispense 1 pad 
#define PAD_OVERSTEP 45//Angle overstep for pad dispense, used for clean dispensing
#define TAMPON_ANGLE_NEEDED 0 //Angle needed for stepper to dispense 1 tampon (Still undetermined)





