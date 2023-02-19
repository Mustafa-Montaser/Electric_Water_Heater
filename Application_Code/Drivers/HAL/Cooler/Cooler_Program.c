/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup Cooler
 * Cooler module driver
 * @{
 * \file Cooler_Program.c
 * \brief this file contains contains implementation for the cooler module
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

#include "../../MCAl/DIO/DIO_Interface.h"

#include "Cooler_Interface.h"


/* functions definition */

void Cooler_voidInit(u8 local_u8CoolerPin)
{
	DIO_voidSetPinMode(local_u8CoolerPin, DIO_PIN_OUTPUT);
}

void Cooler_voidTurnOn(u8 local_u8CoolerPin)
{
	DIO_voidSetPinValue(local_u8CoolerPin);
}

void Cooler_voidTurnOff(u8 local_u8CoolerPin)
{
	DIO_voidClearPinValue(local_u8CoolerPin);
}
