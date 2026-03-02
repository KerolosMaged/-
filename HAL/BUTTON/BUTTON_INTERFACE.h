#ifndef BUTTON_INTERFACE_H
#define	BUTTON_INTERFACE_H



/******** Initialization ********/
void BUTTON_VoidInit_Button_Pin(u8 Copy_u8PORTnumber ,u8 Copy_u8PINnumber,u8 Copy_u8pullupStatus);  // INITAL PIN
void BUTTON_VoidInit_8Buttons_Port(u8 Copy_u8PORTnumber,u8 Copy_u8pullupStatus);    // INITAL PORT


/****** Functions for Button work *******/
u8 BUTTON_u8Get_Button_Pin(u8 Copy_u8PORTnumber ,u8 Copy_u8PINnumber);
u8 BUTTON_u8Get_8Button_Port(u8 Copy_u8PORTnumber);

#endif	

