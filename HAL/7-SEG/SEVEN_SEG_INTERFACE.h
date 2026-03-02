#ifndef SEVEN_SEG_INTERFACE_H
#define SEVEN_SEG_INTERFACE_H

/**** Marcos for the type of seven segment****/
#define COMMON_ANODE  0
#define COMMON_CATHODE 1
/*********************************************/

/******* Initialization of seven segment *******/

void SEGMENT_voidInitSegmentPort (u8 Copy_u8PORTnumber);
void SEGMENT_voidPrintNumber (u8 Copy_u8PORTnumber,u8 Copy_u87SEGPolaritiy,u8 Copy_u8Number);

#endif