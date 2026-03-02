#include "DATA_TYPES.h"
#ifndef BIT_MATH_H
#define BIT_MATH_H

/******** Marcos for operations *********/
#define SET_BIT(register,bit)      register|= (1<<bit)
#define CLEAR_BIT(register,bit)    register&= ~(1<<bit)
#define TOGGLE_BIT(register,bit)   register^= (1<<bit)
#define READ_BIT(register,bit)     register& (1<<bit)

/****************************************/



/**************BIT FIELD*****************/
typedef struct{
  u8 b0 : 1;
  u8 b1 : 1;
  u8 b2 : 1;
  u8 b3 : 1;
  u8 b4 : 1;
  u8 b5 : 1;
  u8 b6 : 1;
  u8 b7 : 1;

}BITS;


typedef union{
  BITS bits;
  u8 byte;
}Register;


/****************************************/
#endif