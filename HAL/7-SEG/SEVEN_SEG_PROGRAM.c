/***** Header files from LIB Folder ******/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/DATA_TYPES.h"

/***** Header files from own Folder ******/
#include "SEVEN_SEG_PRIVATE.h"
#include "SEVEN_SEG_INTERFACE.h"
#include "SEVEN_SEG_CONFGR.h"
/***** Header files from MCAL Layer ******/
#include "../../MCAL/DIO/DIO_INTERFACE.h"


//u8 Common_Anode_arr[16]={'ZERO','ONE','TWO','THREE','FOUR','FIVE','SiX','SEVEN','EIGHT','NINE','A','B','C','D','E','F'};
u8 Common_Anode_arr[16]= {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,A,B,C,D,E,F} ;

/******* Initialization of seven segment *******/

void SEGMENT_voidInitSegmentPort (u8 Copy_u8PORTnumber){


        switch(Copy_u8PORTnumber)
        {
            case PORTA : DIO_VoidSetPortDIrection(PORTA,OUTPUT); break;
            case PORTB : DIO_VoidSetPortDIrection(PORTB,OUTPUT); break;
            case PORTC : DIO_VoidSetPortDIrection(PORTC,OUTPUT); break;
            case PORTD : DIO_VoidSetPortDIrection(PORTD,OUTPUT); break;
            default:                                             break;
        }


}
void SEGMENT_voidPrintNumber (u8 Copy_u8PORTnumber,u8 Copy_u87SEG_Polaritiy,u8 Copy_u8Number){

    switch(Copy_u87SEG_Polaritiy)
    {
        case COMMON_ANODE : switch(Copy_u8PORTnumber)
                            {
                                    case PORTA : DIO_VoidSetPortValue(PORTA,Common_Anode_arr[Copy_u8Number]); break;
                                    case PORTB : DIO_VoidSetPortValue(PORTB,Common_Anode_arr[Copy_u8Number]); break;
                                    case PORTC : DIO_VoidSetPortValue(PORTC,Common_Anode_arr[Copy_u8Number]); break;
                                    case PORTD : DIO_VoidSetPortValue(PORTD,Common_Anode_arr[Copy_u8Number]); break;
                                    default:                                                                  break;
                            
                            }break;
        case COMMON_CATHODE : switch(Copy_u8PORTnumber)
                            {
                                    case PORTA : DIO_VoidSetPortValue(PORTA,~Common_Anode_arr[Copy_u8Number]); break;
                                    case PORTB : DIO_VoidSetPortValue(PORTB,~Common_Anode_arr[Copy_u8Number]); break;
                                    case PORTC : DIO_VoidSetPortValue(PORTC,~Common_Anode_arr[Copy_u8Number]); break;
                                    case PORTD : DIO_VoidSetPortValue(PORTD,~Common_Anode_arr[Copy_u8Number]); break;
                                    default:                                                                   break;
                            
                            }break;
        default:             break;

    }
}
