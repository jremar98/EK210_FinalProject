//----------------//DRV8825 Pins//------------------//

#define M0_PIN 11 //Mode 0 pin
#define M1_PIN 10 //Mode 1 pin
#define M2_PIN 3 //Mode 2 pin
#define STEP_PIN 9 //Step pin
#define DIR_PIN 8 //Dir pin
#define PAD_STEPPER_EN_PIN 2//Pin for enable pin of Pad dispensing stepper
#define TAMPON_STEPPER_EN_PIN 12 //Pin for enable pin of Tampon dispensing stepper



//----------------//User interface Pins//---------------//
#define BUTTON_PIN A0 //Pin for buttons (one pin setup for analogRead)'
#define TAMPON_ADC 513
#define PAD_ADC 931


//----------------//Piezo Buzzer Pin//------------------//

//#define BUZZER_PIN 3


//----------------//Card Reader Pins//------------------//
#define CARD_READER_TX_PIN 4 //Might want to change these to different digital I/O pins if serial connection to computer doesnt work
#define CARD_READER_RX_PIN 5

//----------------//LED Pins//------------------//
//#define LOWBAT_LED_PIN 15
#define LOWPAD_LED_PIN 16
#define LOWTAMPON_LED_PIN 17

//----------------//IR PINS//------------------//
#define LOW_TAMPON_PIN 6
#define LOW_PAD_PIN 7


///////////////////////////////////////////////////////////
//--------------------User Parameters--------------------//
///////////////////////////////////////////////////////////


#define BUTTON_DEBOUNCE 500 //Debounce time for button inputs, used in order prevent the button from flippin shit due to small inconsistencies in press


///////////////////////////////////////////////////////////
//--------------------Stepper Parameters-----------------//
///////////////////////////////////////////////////////////

#define RPM 175 //Speed of stepper motor, 400->speedy boi
#define MOTOR_STEPS 200 //Steps per revolution of stepper motor -> NEMA 17: 1.8deg/step (at full steps)
#define MICROSTEPPING 1 //Set microstepping (1,2,4,8,16,32) of DRV8825 (pcb has pinouts for only MS1 and MS2, so 8 should work fine

//////////////////////////////////////////////////////////////
//--------------------Dispensing Parameters-----------------//
//////////////////////////////////////////////////////////////
#define PAD_ANGLE_NEEDED -120 // Angle needed for stepper to dispense 1 pad 
#define PAD_OVERSTEP -25//Angle overstep for pad dispense, used for clean dispensing 
#define TAMPON_FRONT_ANGLE_NEEDED 120 //Angle needed for stepper to dispense 1 tampon from front column
#define TAMPON_BACK_ANGLE_NEEDED -120 //Angle needed for stepper to dispense 1 tampon from back column
#define TAMPON_OVERSTEP 10//Angle overstep for clean tampon dispensing goodness (very niiice)
#define TAMPON_STOCK 3 //Number of Tampons Stocked, keeping at 3 for demo
#define PAD_STOCK 3 //Number of Pads Stocked 

#include <SoftwareSerial.h> //Include library for card reader serial communication
#include <DRV8825.h>//DRV8825 
/*Include Local Header Files*/


/*Instances declarations*/
SoftwareSerial cardSerial(CARD_READER_RX_PIN,CARD_READER_TX_PIN); // RX, TX
DRV8825 stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN, M0_PIN, M1_PIN, M2_PIN); //Initiallize DRV8825/NEMA17's (differentiating with enable pins, everything else is in parallel


/*Global Variable Declarations*/
int padstock = PAD_STOCK; //Variable to track stock of pads
int tamponstock = TAMPON_STOCK;// Variable to track stock of tampons
int tamponCol = 0; //stores last tampon column dispensed || 0->front column|1-> Back Column 
const byte numChars = 10;
char card1[numChars]={'n','o','c','a','r','d','d','a','t','\0'}; //last card read
char card2[numChars]= {'n','o','c','a','a','d','d','a','t','\0'};//last last card read
char card3[numChars]={'n','c','c','a','r','d','d','a','t','\0'}; //last last last card read
boolean newData = false;

char receivedChars[numChars];

void setup()
{
  #ifdef PADBUTTON_PIN
      pinMode(PADBUTTON_PIN,INPUT); //declare button pin as input
      Serial.println("Start");
      #else
      //Serial.println("Warning, Pad Dispense Button Not defined!");
      #endif

    #ifdef TAMPONBUTTON_PIN
      pinMode(TAMPONBUTTON_PIN,OUTPUT);
      #else
      //Serial.println("Warning, Tampon Dispense Button Not defined!");
      #endif
      
    #ifdef BUZZER_PIN
      pinMode(BUZZER_PIN, OUTPUT);
      #endif

    #ifdef LOWBAT_LED_PIN
      pinMode(LOWBAT_LED_PIN,OUTPUT);
      #else
      //Serial.println("Warning, Low Battery LED pin Not Defined!");
      #endif
      
    #ifdef LOWPAD_LED_PIN
      pinMode(LOWPAD_LED_PIN,OUTPUT);
      #else
      //Serial.println("Warning, Low pad LED pin Not Defined!");
      #endif

    #ifdef LOWTAMPON_LED_PIN
      pinMode(LOWTAMPON_LED_PIN,OUTPUT);
      #else
      //Serial.println("Warning, Low Tampon LED pin Not Defined!");
      #endif

    #ifdef PAD_STEPPER_EN_PIN
      pinMode(PAD_STEPPER_EN_PIN, OUTPUT);
      #else
      //Serial.print("WARNING: PAD EN PIN NOT DEFINED, THERE WILL BE NO CONTROL OVER STEPPER DIFFERENTIATION!!");
      #endif


    stepper.begin(RPM); //Begin stepper
    //stepper.enable(); //Turn On stepper
    stepper.setMicrostep(MICROSTEPPING);
    digitalWrite(TAMPON_STEPPER_EN_PIN, HIGH); // Disable tampon DRV8825 and Stepper
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable Pad DRV8825 and Stepper

  Serial.begin(9600);   // Initiate a serial communication
  Serial.println("Feminine Hygiene Product Dispenser Initialized!");
  cardSerial.begin(9600);
  Serial.println("Serial Card Reader Initialized");

  //dispenser.initialize(); //run init function for dispenser 
}
void loop()
{

  
  
    recvWithStartEndMarkers();
    showNewData();
    //Serial.println(newData);
    
    if(newData == true )//&& buttonState>50 //Means card swiped and button pressed
    {
      Serial.print("Swipe count over? ");
      int swipeOverload = checkSwipeCount();
      Serial.println(swipeOverload);
      if(checkSwipeCount() == true)
      {
        Serial.println("No more swipes:(");
        newData=false;
      }
      
      else
      {
        int buttonState = analogRead(BUTTON_PIN);
        Serial.print("Button ADC = ");
        Serial.println(buttonState);
        while(analogRead(BUTTON_PIN)<=200) //wait untill button pressed
        {
//        buttonState = analogRead(BUTTON_PIN);
//        Serial.print("Button ADC = ");
//        Serial.println(buttonState);
        }
        
        
        if(analogRead(BUTTON_PIN)<=(PAD_ADC+100)&&analogRead(BUTTON_PIN)>=(TAMPON_ADC+100))//If ADC for pad button read (with room for error)
        {
        Serial.print("Pad Button ADC = ");
        Serial.println(buttonState);
        stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to defined 
        digitalWrite(TAMPON_STEPPER_EN_PIN, HIGH); // Disable tampon DRV8825 and Stepper
        digitalWrite(PAD_STEPPER_EN_PIN, LOW); // Enable Pad DRV8825 and Stepper
        
        stepper.rotate(-150);    // reverse revolution
        stepper.rotate(+30);//Clear overstep
        digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
        Serial.println("Dispensed Pad");
        newData = false; //Clear card data 
        }
        if(analogRead(BUTTON_PIN)>=(TAMPON_ADC-100)&&analogRead(BUTTON_PIN)<(PAD_ADC-100))//TAMPON button pressed
        {
          Serial.print("Tampon Button ADC = ");
          Serial.println(buttonState);
          if(tamponCol==0) //means last tampon dispensed from front col
            {
            dispTamponBackCol();
            newData = false; //Clear card data 
            tamponCol=1;
            }

            else //means last tampon dispensed from back col
            {
             dispTamponFrontCol(); 
             newData = false;
             tamponCol=0;
             
            }
        }
  }
}
}
/* 
 *  FHPD.cpp - functions for controlling a Arduino based feminine hygiene product dispenser
 *  Written by Jordan Remar, November 1, 2018
 */



//Call format for DRV8825 Stepper Library (from LaurB9): DRV8825(short steps, short dir_pin, short step_pin, short mode0_pin, short mode1_pin, short mode2_pin);

 void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = ';';
    char endMarker = '?';
    char rc;
 
    while (cardSerial.available() > 0 && newData == false) {
        rc = cardSerial.read();
        Serial.println("Data Recieved");
        

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
                int i;
                for(i=0;i<numChars;i++)
                {
                card3[i] = card2[i]; //Replace card data
                card2[i] = card1[i];
                card1[i] = receivedChars[i];
                }
                Serial.print("Recieved chars = ");
                Serial.println(receivedChars);
                


            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
       
        }
    }
}

void showNewData() {
    if (newData == true) {
            Serial.print("Card number 1 =");
            Serial.println(card1);
            Serial.print("Card number 2 =");
            Serial.println(card2);
            Serial.print("Card number 3 =");
            Serial.println(card3);
        //newData = false;
    }
}

 


void dispPad() 
{
    //stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to defined 
    digitalWrite(TAMPON_STEPPER_EN_PIN, HIGH); // Disable tampon DRV8825 and Stepper
    digitalWrite(PAD_STEPPER_EN_PIN, LOW); // Enable Pad DRV8825 and Stepper
    
    stepper.rotate(-150);    // reverse revolution
    stepper.rotate(+30);//Clear overstep
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
    Serial.println("Dispensed Pad");
  }  

void dispTamponFrontCol() //Dispense tampon from front column
{
    stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to defined 
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable tampon DRV8825 and Stepper
    digitalWrite(TAMPON_STEPPER_EN_PIN, LOW); // Enable Pad DRV8825 and Stepper
    
    stepper.rotate(TAMPON_FRONT_ANGLE_NEEDED+TAMPON_OVERSTEP);    // dispense tampon 
    stepper.rotate(-TAMPON_OVERSTEP); //Clear out overstep angle
    digitalWrite(TAMPON_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
    Serial.println("Dispensed Tampon from front column");
}


void dispTamponBackCol()
{
    stepper.setMicrostep(MICROSTEPPING);   // Set microstep mode to defined 
    digitalWrite(PAD_STEPPER_EN_PIN, HIGH); // Disable tampon DRV8825 and Stepper
    digitalWrite(TAMPON_STEPPER_EN_PIN, LOW); // Enable Pad DRV8825 and Stepper
    
    stepper.rotate(TAMPON_BACK_ANGLE_NEEDED+TAMPON_OVERSTEP);    // dispense tampon 
    delay(50);// let the dust settle
    stepper.rotate(-TAMPON_OVERSTEP); //Clear out overstep angle
    digitalWrite(TAMPON_STEPPER_EN_PIN, HIGH); // Disable DRV8825 and Stepper
    Serial.println("Dispensed Tampon from back column");
}

bool buttonPressCheck() //IRRELEVANT, DON'T USE
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

void runDebug()
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

boolean checkSwipeCount(){
     int n;
     

     // test each element to be the same. if not, return false
     for (n=0;n<numChars;n++) 
     {
      if (card1[n]==card2[n]&&card2[n]==card3[n]&&card3[n]==card1[n]) 
      {
       
      }
      else 
      {
        return false;
      }
      
     }

     //ok, if we have not returned yet, they are equal :)
     return true;
}

