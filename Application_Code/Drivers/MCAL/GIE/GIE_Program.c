/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup MCAL
 * This group contain MCAL drivers
 * @{
 * \addtogroup GIE
 * Global Interrupt Enabling module driver
 * @{
 * \file GIE_Program.c
 * \brief this file contains contains implementation for the GIE module
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

#include "GIE_Interface.h"
#include "GIE_Private.h"


/* functions definition */


void GIE_voidEnableGlobalINT()
{
	SET_BIT(GIE_SREG, GIE_SREG_I);
}



void GIE_voidDisableGlobalINT()
{
	CLR_BIT(GIE_SREG, GIE_SREG_I);
}


