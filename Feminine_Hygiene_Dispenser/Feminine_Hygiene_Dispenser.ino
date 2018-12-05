/*
Written by Jordan Remar
*/
//#include <SPI.h> //SPI
#include <SoftwareSerial.h> //Include library for card reader serial communication

/*Include Local Header Files*/
#include "FHPD.h"
#include "pins.h"
#include "config.h"

/*Instances declarations*/
SoftwareSerial cardSerial(CARD_READER_RX_PIN,CARD_READER_TX_PIN); // RX, TX
FHPD dispenser = FHPD(); //declare dispenser object as global

/*Global Variable Declarations*/
int padstock = PAD_STOCK; //Variable to track stock of pads
int tamponstock = TAMPON_STOCK;// Variable to track stock of tampons
int tamponCol = 0; //stores last tampon column dispensed || 0->front column|1-> Back Column 
const byte numChars = 9;
char card1[numChars], //last card read
     card2[numChars], //last last card read
     card3[numChars]; //last last last card read
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
  Serial.begin(9600);   // Initiate a serial communication
  Serial.println("Feminine Hygiene Product Dispenser Initialized!");
  cardSerial.begin(9600);
  Serial.println("Serial Card Reader Initialized");

  //dispenser.initialize(); //run init function for dispenser 
  
}


void loop()
{
   int buttonState = analogRead(BUTTON_PIN);
    recvWithStartEndMarkers();
    Serial.println(card1);
    Serial.println(card2);
    Serial.println(card3);
    if(newData == true && buttonState>50) //Means card swiped and button pressed
    {
      if(buttonState<500)
      dispenser.dispTamponFrontCol();
      newData = false; //Clear card data 
      ;
      
    }



//  int buttonState = analogRead(BUTTON_PIN); // Read voltage input from Button pin (range is 0 to 1023)
  
  
 }

 void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = ';';
    char endMarker = '?';
    char rc;
 
    while (cardSerial.available() > 0 && newData == false) {
        rc = cardSerial.read();
        Serial.print("Serial Data Recieved");

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
                for(i=1;i<=numChars;i++)
                card3[i] = card2[i]; //Replace card data
                card2[i] = card1[i];
                card1[i]=receivedChars[i];
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
       
        }
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("Card number =");
        Serial.println(receivedChars);
        //newData = false;
    }
}



















