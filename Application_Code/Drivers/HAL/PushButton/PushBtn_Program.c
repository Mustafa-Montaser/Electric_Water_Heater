/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup PushButton
 * PushButton module driver
 * @{
 * \file BushBtn_Program.c
 * \brief this file contains contains implementation for the PushButton module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


/* header files includes */

#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include "../../MCAL/ExtInt/EXT_INT_Interface.h"

#include "PushBtn_Config.h"
#include "PushBtn_Interface.h"


/* functions definitions */

void PushBtn_voidInit(u8 local_u8PushBtnPin, u8 local_u8InterruptState, void (*ptr_callBack) (void))
{
	switch(local_u8InterruptState)
	{
		case PUSH_BTN_INTERRUPT_EN:
			ExtInt_voidInit();
			switch(local_u8PushBtnPin)
			{
				case DIO_PD2: ExtInt_voidEnableInt0(); ExtInt_SetCallBack0(ptr_callBack); break;
				case DIO_PD3: ExtInt_voidEnableInt1(); ExtInt_SetCallBack1(ptr_callBack); break;
				case DIO_PB2: ExtInt_voidEnableInt2(); ExtInt_SetCallBack2(ptr_callBack); break;
				default: break;
			}
			break;
		case PUSH_BTN_INTERRUPT_DIS:
			DIO_voidSetPinMode(local_u8PushBtnPin, DIO_PIN_INPUT);
			#if PUSH_BTN_CONNECTION == PUSH_BTN_PULL_UP
				DIO_voidSetPinValue(loclocal_u8PushBtnPin);
			#endif
			break;
	}
}


void PushBtn_voidEnable(u8 local_u8PushBtnPin)
{
	switch(local_u8PushBtnPin)
	{
		case DIO_PD2: ExtInt_voidEnableInt0(); break;
		case DIO_PD3: ExtInt_voidEnableInt1(); break;
		case DIO_PB2: ExtInt_voidEnableInt2(); break;
		default: break;
	}
}


void PushBtn_voidDisable(u8 local_u8PushBtnPin)
{
	switch(local_u8PushBtnPin)
	{
		case DIO_PD2: ExtInt_voidDisableInt0(); break;
		case DIO_PD3: ExtInt_voidDisableInt1(); break;
		case DIO_PB2: ExtInt_voidDisableInt2(); break;
		default: break;
	}
}


u8 PushBtn_voidGetStatus(u8 local_u8PushBtnPin)
{
	u8 local_u8BtnState = DIO_u8GetPinValue(local_u8PushBtnPin);
	#if PUSH_BTN_CONNECTION == PUSH_BTN_PULL_UP
		local_u8BtnState = local_u8BtnState ? PUSH_BTN_RELEASED : PUSH_BTN_PRESSED;
	#elif PUSH_BTN_CONNECTION == PUSH_BTN_PULL_DOWN
		local_u8BtnState = local_u8BtnState ? PUSH_BTN_PRESSED : PUSH_BTN_NOT_PRESSED;
	#endif
	return local_u8BtnState;
}
