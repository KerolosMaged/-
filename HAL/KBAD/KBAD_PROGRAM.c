/***** Header files from LIB Folder ******/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/DATA_TYPES.h"
#include <util/delay.h>

/***** Header files from own Folder ******/
#include "KBAD_INTERFACE.h"
#include "KBAD_PRIVATE.h"
#include "KBAD_CONFGR.h"

/***** Header files from MCAL Layer ******/
#include "../../MCAL/DIO/DIO_INTERFACE.h"

/***** Global Variables ******/
u8 KBAD_Au8ColumnsArr[KBAD_COLUMNS_NUM] = { KBAD_CO_PIN , KBAD_C1_PIN , KBAD_C2_PIN , KBAD_C3_PIN };
u8 KBAD_Au8RowsArr[KBAD_ROWS_NUM]       = { KBAD_RO_PIN , KBAD_R1_PIN , KBAD_R2_PIN , KBAD_R3_PIN };
u8 KBAD_Au8KeysArr[KBAD_ROWS_NUM][KBAD_COLUMNS_NUM] = KPAD_KEYS;

/******************************************
 * Function: KBAD_VoidInit
 * Description: Initialize keypad directions and pull-ups
 ******************************************/
void KBAD_VoidInit(void)
{
    // Set columns as output
    DIO_VoidSetPinDirection(KBAD_PORT, KBAD_CO_PIN, OUTPUT);
    DIO_VoidSetPinDirection(KBAD_PORT, KBAD_C1_PIN, OUTPUT);
    DIO_VoidSetPinDirection(KBAD_PORT, KBAD_C2_PIN, OUTPUT);
    DIO_VoidSetPinDirection(KBAD_PORT, KBAD_C3_PIN, OUTPUT);

    // Set rows as input
    DIO_VoidSetPinDirection(KBAD_PORT, KBAD_RO_PIN, INPUT);
    DIO_VoidSetPinDirection(KBAD_PORT, KBAD_R1_PIN, INPUT);
    DIO_VoidSetPinDirection(KBAD_PORT, KBAD_R2_PIN, INPUT);
    DIO_VoidSetPinDirection(KBAD_PORT, KBAD_R3_PIN, INPUT);

    // Activate pull-up resistors on rows
    DIO_VoidConfgr_Pull_up_pin(KBAD_PORT, KBAD_RO_PIN, ON);
    DIO_VoidConfgr_Pull_up_pin(KBAD_PORT, KBAD_R1_PIN, ON);
    DIO_VoidConfgr_Pull_up_pin(KBAD_PORT, KBAD_R2_PIN, ON);
    DIO_VoidConfgr_Pull_up_pin(KBAD_PORT, KBAD_R3_PIN, ON);

    // Deactivate columns (set HIGH)
    DIO_VoidSetPinValue(KBAD_PORT, KBAD_CO_PIN, HIGH);
    DIO_VoidSetPinValue(KBAD_PORT, KBAD_C1_PIN, HIGH);
    DIO_VoidSetPinValue(KBAD_PORT, KBAD_C2_PIN, HIGH);
    DIO_VoidSetPinValue(KBAD_PORT, KBAD_C3_PIN, HIGH);
}

/******************************************
 * Function: KBAD_u8GetPressedKey
 * Description: Scan keypad and return pressed key
 * Returns: u8 (0xFF if no key pressed)
 ******************************************/
u8 KBAD_u8GetPressedKey(void)
{
    u8 Local_u8ColIter, Local_u8RowIter;
    u8 Local_u8PinVal;
    u8 Local_u8PressedKey = 0xFF; // default no key pressed
    u8 Local_u8Flag = 0;

    for (Local_u8ColIter = 0; Local_u8ColIter < KBAD_COLUMNS_NUM; Local_u8ColIter++)
    {
        // Activate one column at a time
        DIO_VoidSetPinValue(KBAD_PORT, KBAD_Au8ColumnsArr[Local_u8ColIter], LOW);

        // Small delay to settle signals (debouncing)
        _delay_ms(5);

        for (Local_u8RowIter = 0; Local_u8RowIter < KBAD_ROWS_NUM; Local_u8RowIter++)
        {
            Local_u8PinVal = DIO_u8GetPinValue(KBAD_PORT, KBAD_Au8RowsArr[Local_u8RowIter]);

            // If key is pressed
            if (Local_u8PinVal == 0)
            {
                // Wait until key is released (debouncing)
                while (DIO_u8GetPinValue(KBAD_PORT, KBAD_Au8RowsArr[Local_u8RowIter]) == 0)
                {
                    _delay_ms(10);
                }

                // Get corresponding key value
                Local_u8PressedKey = KBAD_Au8KeysArr[Local_u8RowIter][Local_u8ColIter];
                Local_u8Flag = 1;
                break;
            }
        }

        // Deactivate current column
        DIO_VoidSetPinValue(KBAD_PORT, KBAD_Au8ColumnsArr[Local_u8ColIter], HIGH);

        if (Local_u8Flag == 1)
        {
            break;
        }
    }

    return Local_u8PressedKey;
}
