/***** Header files from LIB Folder ******/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/DATA_TYPES.h"
#include <util/delay.h>

/***** Header files from own Folder ******/
#include "LCD_CONFGR.h"
#include "LCD_PRIVATE.h"
#include "LCD_INTERFACE.h"
/***** Header files from MCAL Layer ******/
#include "../../MCAL/DIO/DIO_INTERFACE.h"



/*!!!!!!!! PLEASE CHANGE number OF PORTS AND BITS IN CONFGR FILE!!!!!!!!!*/




void LCD_voidInit (void){
    /* Control Pins Directions */
    DIO_VoidSetPortDIrection( LCD_DATA_PORT , OUTPUT);//




    DIO_VoidSetPinDirection(LCD_CONTROL_PORT,RS_PIN,OUTPUT);
    DIO_VoidSetPinDirection(LCD_CONTROL_PORT,RW_PIN,OUTPUT);
    DIO_VoidSetPinDirection(LCD_CONTROL_PORT,E_PIN,OUTPUT);

    _delay_ms(35);    //TIMER0_delay_ms(35);

    /* Send Command Function Set */
    LCD_VoidWriteCommand ( FS_8BIT_2LINES_5x10 );//
    _delay_ms(1);     // TIMER0_delay_ms(1);

    /* Send Command Display ON-OFF Control */
    LCD_VoidWriteCommand ( DIS_ON_Blinking_CURSER );
    _delay_ms(1);     //TIMER0_delay_ms(1);

    /* Send Command Display Clear */
    LCD_VoidWriteCommand ( DIS_CLEAR );
    _delay_ms(2);     //TIMER0_delay_ms(2);

    /* Send Command Entry Mode */
    LCD_VoidWriteCommand ( ENTRY_MODE_INCREASE_NO_SHIFT );
    _delay_ms(1);     //TIMER0_delay_ms(1);

}

void LCD_VoidWriteCommand(u8 Copy_u8command){

   
   DIO_VoidSetPortValue(LCD_DATA_PORT,Copy_u8command); //
   



   DIO_VoidSetPinValue(LCD_CONTROL_PORT,RS_PIN,LOW);
   
   DIO_VoidSetPinValue(LCD_CONTROL_PORT,RW_PIN,LOW);

   DIO_VoidSetPinValue(LCD_CONTROL_PORT,E_PIN,HIGH);
   _delay_ms(2);
   DIO_VoidSetPinValue(LCD_CONTROL_PORT,E_PIN,LOW);


}

void LCD_VoidWriteChar(u8 Copy_u8char)
{
    // Send data
    DIO_VoidSetPortValue(LCD_DATA_PORT, Copy_u8char);



    // RS = 1 (Data)
    DIO_VoidSetPinValue(LCD_CONTROL_PORT, RS_PIN, HIGH);

    // RW = 0 (Write)
    DIO_VoidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);


    // Pulse E
    DIO_VoidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
    _delay_us(1); // Short delay
    DIO_VoidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);

    _delay_ms(2); // Wait for LCD to finish writing
}



void LCD_VoidWriteString(u8 *Copy_u8arr){
   u8 i=0;
   while (Copy_u8arr[i] != '\0' )
    {
        LCD_VoidWriteChar ( Copy_u8arr[i] );
        i++;
    }
}

void LCD_VoidWrite_u32Number ( u32 Copy_u32number){
    u8 Arr[20] ; // {1,2,5}
    u8 i=0 ;    
    while ( Copy_u32number > 0 )        // assume number = 521
    {                                   // iteration_0      // iteration_1  // iteration_2
        Arr[i] = Copy_u32number % 10 ;  // 521%10 = 1       // 52%10 = 2    // 5%10 = 5
        Copy_u32number /= 10 ;          // 521/10 = 52      // 52/10 = 5    // 5/10 = 0
        i++;                            // i = 1            // i = 2        // i = 3
    }
    //i=3 ;
    i--;
    //i=2 ;
    for( s16 j=i ; j>=0 ; j--)
    {   // {1,2,5} - {'1','2','5'}
        LCD_VoidWriteChar ( Arr[j] + '0' );
    }
}

void LCD_VoidGoTo_XY(u8 Copy_u8line,u8 Copy_position){

   if((Copy_u8line > 2)||(Copy_position > 15))
   {
      //nothing to do
   }
   else
   {
      switch(Copy_u8line)
      {
         case LINE_1 : LCD_VoidWriteCommand( 0X80 + Copy_position ); break;
         case LINE_2 : LCD_VoidWriteCommand( 0XC0 + Copy_position ); break;
         default:                                                    break;
      }
   }
}

void LCD_VoidDrawPattern(u8 Copy_u8pattern_number, u8 *Copy_u8arr_pattern){
    
    LCD_VoidWriteCommand(0x40 + (Copy_u8pattern_number * 8));
  
    for(u8 i = 0; i < 8; i++){
        LCD_VoidWriteChar(Copy_u8arr_pattern[i]);
    }
}

void LCD_VoidWritePattern(u8 Copy_u8pattern,u8 Copy_u8line,u8 Copy_position){
   
   LCD_VoidGoTo_XY( Copy_u8line, Copy_position);
   LCD_VoidWriteChar(Copy_u8pattern);
}

void LCD_VoidClearDisplay(void){
  
   LCD_VoidWriteCommand(DIS_CLEAR);
}

void LCD_VoidShiftLeft(void){
   LCD_VoidWriteCommand(ENTRY_MODE_INCREASE_LEFT_SHIFT);
}

void LCD_VoidShiftRight(void){
   LCD_VoidWriteCommand(ENTRY_MODE_DECREASE_RIGHT_SHIFT);
}

void LCD_VoidClearGrid(u8 Copy_u8line,u8 Copy_position){
   LCD_VoidGoTo_XY( Copy_u8line, Copy_position);
   LCD_VoidWriteChar(' ');

}

void LCD_VoidClearLine(u8 Copy_u8line){
   for(u8 i = 0 ; i<16 ; i++ )
   {
      LCD_VoidGoTo_XY( Copy_u8line, i);
      LCD_VoidWriteChar(' ');
   }
}


void LCD_VoidWriteFloatNumber(f32 num) {
    char buffer[16];
    dtostrf(num, 1, 2, buffer);  
    LCD_VoidWriteString((u8*)buffer);
}
