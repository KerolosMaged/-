/***** Header files from LIB Folder ******/
#include "../../LIB/BIT_MATH.H"
#include "../../LIB/DATA_TYPES.H"

/***** Header files from own Folder ******/
#include "LED_INTERFACE.h"
#include "LED_PRIVATE.h"
#include "LED_CONFGR.h"
/***** Header files from MCAL Layer ******/
#include "../../MCAL/DIO/DIO_INTERFACE.h"

/******************** Intialization modules **********************/
void LED_VoidInit_Led_Pin(u8 Copy_u8PORTnumber,u8 Copy_u8PINnumber){
 
   if ((Copy_u8PORTnumber > PORTD)||(Copy_u8PINnumber > PIN7))
   {
      //nothing
   }
   else
   {
      DIO_VoidSetPinDirection(Copy_u8PORTnumber,Copy_u8PINnumber,OUTPUT);
   }   
}

void LED_VoidInit_8Leds_Port(u8 Copy_u8PORTnumber){

   if ((Copy_u8PORTnumber > PORTD))
   {
      //nothing
   }
   else
   {
      DIO_VoidSetPortDirection(Copy_u8PORTnumber,OUTPUT);
   } 
}
/******************************************************************/

/*********************** status modules *************************/
void LED_VoidStatus_Led_Pin(u8 Copy_u8PORTnumber,u8 Copy_u8PINnumber,u8 Copy_u8Status){
   if ((Copy_u8PORTnumber > PORTD)||(Copy_u8PINnumber > PIN7))
   {
      //nothing
   }
   else
   {
        switch(Copy_u8Status)
        {
            case ON  :   DIO_VoidSetPinValue ( Copy_u8PORTnumber, Copy_u8PINnumber, HIGH );     break;
            case OFF :   DIO_VoidSetPinValue ( Copy_u8PORTnumber, Copy_u8PINnumber, LOW  );     break;
            default  :                                                                          break;
        }
   }
}

void LED_VoidStatus_8Leds_Port(u8 Copy_u8PORTnumber,u8 Copy_u8Status){
   if ((Copy_u8PORTnumber > PORTD))
   {
      //nothing
   }
   else
   {
        switch(Copy_u8Status)
        {
            case ON  :   DIO_VoidSetPortValue ( Copy_u8PORTnumber,  HIGH );     break;
            case OFF :   DIO_VoidSetPortValue ( Copy_u8PORTnumber,  LOW  );     break;
            default  :                                                         break;
        }
   }
}

/******************************************************************/

/*********************** Toggle modules *************************/

void led_VoidToggle_Led_pin(u8 Copy_u8PORTnumber,u8 Copy_u8PINnumber){
   if ((Copy_u8PORTnumber > PORTD)||(Copy_u8PINnumber > PIN7))
   {
      //nothing
   }
   else
   {
      DIO_VoidTogglePinValue(Copy_u8PORTnumber,Copy_u8PINnumber);
   }  
}


void led_VoidToggle_8Leds_Port(u8 Copy_u8PORTnumber){

   if ((Copy_u8PORTnumber > PORTD))
   {
      //nothing
   }
   else
   {
      DIO_VoidTogglePortValue(Copy_u8PORTnumber);
   } 
}

/****************************************************************/
