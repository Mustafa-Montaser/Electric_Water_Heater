/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup LED
 * LED module driver
 * @{
 * \file Cooler_Program.c
 * \brief this file contains contains implementation for the LED module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


/* Header files includes */

#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include "LED_Interface.h"



/* functions definitions */

void LED_voidInit(u8 local_u8LedPin)
{
	DIO_voidSetPinMode(local_u8LedPin, DIO_PIN_OUTPUT);
}

void LED_voidTurnOn(u8 local_u8LedPin)
{
	DIO_voidWritePinValue(local_u8LedPin, DIO_PIN_HIGH);
}

void LED_voidTurnOff(u8 local_u8LedPin)
{
	DIO_voidWritePinValue(local_u8LedPin, DIO_PIN_LOW);
}

void LED_voidToggle(u8 local_u8LedPin)
{
	DIO_voidTogglePinValue(local_u8LedPin);
}
