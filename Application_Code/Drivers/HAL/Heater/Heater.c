/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup Heater
 * Heater module driver
 * @{
 * \file Cooler_Program.c
 * \brief this file contains contains implementation for the Heater module
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

#include "Heater.h"


/* functions declaration */

void Heater_voidInit(u8 local_u8HeaterPin)
{
	DIO_voidSetPinMode(local_u8HeaterPin, DIO_PIN_OUTPUT);
}

void Heater_voidTurnOn(u8 local_u8HeaterPin)
{
	DIO_voidSetPinValue(local_u8HeaterPin);
}

void Heater_voidTurnOff(u8 local_u8HeaterPin)
{
	DIO_voidClearPinValue(local_u8HeaterPin);
}
