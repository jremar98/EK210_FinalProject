
///////////////////////////////////////////////////////////
//--------------------User Parameters--------------------//
///////////////////////////////////////////////////////////


#define BUTTON_DEBOUNCE 500 //Debounce time for button inputs, used in order prevent the button from flippin shit due to small inconsistencies in press


///////////////////////////////////////////////////////////
//--------------------Stepper Parameters-----------------//
///////////////////////////////////////////////////////////

#define RPM 200 //Speed of stepper motor, 400->speedy boi
#define MOTOR_STEPS 200 //Steps per revolution of stepper motor -> NEMA 17: 1.8deg/step (at full steps)
#define MICROSTEPPING 8 //Set microstepping (1,2,4,8,16,32) of DRV8825 (pcb has pinouts for only MS1 and MS2, so 8 should work fine

//////////////////////////////////////////////////////////////
//--------------------Dispensing Parameters-----------------//
//////////////////////////////////////////////////////////////
#define PAD_ANGLE_NEEDED -120 // Angle needed for stepper to dispense 1 pad 
#define PAD_OVERSTEP 45//Angle overstep for pad dispense, used for clean dispensing 
#define TAMPON_FRONT_ANGLE_NEEDED 180 //Angle needed for stepper to dispense 1 tampon from front column
#define TAMPON_BACK_ANGLE_NEEDED 180 //Angle needed for stepper to dispense 1 tampon from back column
#define TAMPON_OVERSTEP 10//Angle overstep for clean tampon dispensing goodness (very niiice)
#define TAMPON_STOCK 3 //Number of Tampons Stocked, keeping at 3 for demo
#define PAD_STOCK 3 //Number of Pads Stocked 




