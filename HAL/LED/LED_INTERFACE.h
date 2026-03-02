#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

/********* Intialization modules ***********/

void LED_VoidInit_Led_Pin(u8 Copy_u8PORTnumber,u8 Copy_u8PINnumber);

void LED_VoidInit_8Leds_Port(u8 Copy_u8PORTnumber);

/******************************************/

/*=================================================================================*/

/*************** status modules **************/

void LED_VoidStatus_Led_Pin(u8 Copy_u8PORTnumber,u8 Copy_u8PINnumber,u8 Copy_u8Status);
void LED_VoidStatus_8Leds_Port(u8 Copy_u8PORTnumber,u8 Copy_u8Status);

/*********************************************/

/*=================================================================================*/

/************* Toggle modules *************/

void led_VoidToggle_Led_pin(u8 Copy_u8PORTnumber,u8 Copy_u8PINnumber);
void led_VoidToggle_8Leds_Port(u8 Copy_u8PORTnumber);

/******************************************/


#endif