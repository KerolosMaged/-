/***** Header files from LIB Folder ******/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/DATA_TYPES.h"
#include <util/delay.h>

/***** Header files from own Folder ******/
#include "BUTTON_CONFRG.h"
#include "BUTTON_PRIVATE.h"
#include "BUTTON_INTERFACE.h"
/***** Header files from MCAL Layer ******/
#include "../../MCAL/DIO/DIO_INTERFACE.h"

void BUTTON_VoidInit_Button_Pin(u8 Copy_u8PORTnumber ,u8 Copy_u8PINnumber,u8 Copy_u8pullupStatus){

    DIO_VoidSetPinDirection (Copy_u8PORTnumber,Copy_u8PINnumber,INPUT);
    DIO_VoidConfgr_Pull_up_pin ( Copy_u8PORTnumber ,Copy_u8PINnumber ,Copy_u8pullupStatus);
    
}

void BUTTON_VoidInit_8Buttons_Port(u8 Copy_u8PORTnumber ,u8 Copy_u8pullupStatus) {

    DIO_VoidSetPortDIrection (Copy_u8PORTnumber,INPUT);
    DIO_VoidConfgr_Pull_up_port(Copy_u8PORTnumber,Copy_u8pullupStatus);
    
 }

u8 BUTTON_u8Get_Button_Pin(u8 Copy_u8PORTnumber ,u8 Copy_u8PINnumber){
    
    u8 Local_Varible;
    
    Local_Varible = DIO_u8GetPinValue( Copy_u8PORTnumber , Copy_u8PINnumber );
    
    return Local_Varible;
}

u8 BUTTON_u8Get_8Button_Port(u8 Copy_u8PORTnumber){
    u8 Local_Varible;
    Local_Varible = DIO_u8GetPortValue(Copy_u8PORTnumber);
    return Local_Varible;

}
