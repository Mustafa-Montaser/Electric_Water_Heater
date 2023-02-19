/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup SensorLM35
 * SensorLM35 module driver
 * @{
 * \file SensorLM35_Program.c
 * \brief this file contains contains implementation for the SensorLM35 module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */

/* Header files includes */

#include "../../LIB/StdTypes.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include "../../MCAL/ADC/ADC_Config.h"
#include "../../MCAL/ADC/ADC_Interface.h"


/* functions definition */


void SensorLM35_voidInit()
{
	ADC_voidInit();
}


u8 SensorLM35_u16ReadTemp(u8 local_u8Pin)
{
	u8 local_u16Temp = 0;
	if(local_u8Pin == DIO_PA7)
	{
		local_u16Temp = (u8)(ADC_u16Read(ADC_CH7) / 10);
	}
	return local_u16Temp;
}
