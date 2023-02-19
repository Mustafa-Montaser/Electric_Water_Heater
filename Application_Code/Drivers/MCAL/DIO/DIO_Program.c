/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup MCAL
 * This group contain MCAL drivers
 * @{
 * \addtogroup DIO
 * DIO module driver
 * @{
 * \file DIO_Program.c
 * \brief this file contains contains implementation for the DIO module
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

#include "DIO_Private.h"
#include "DIO_Interface.h"


/* function definitions */

void DIO_voidSetPortMode(DIO_PortId_t Copy_u8PortId, DIO_PortMode_t Copy_u8PortMode) {
	switch(Copy_u8PortId) {
		case DIO_PORT_A: DIO_DDRA = Copy_u8PortMode; break;
		case DIO_PORT_B: DIO_DDRB = Copy_u8PortMode; break;
		case DIO_PORT_C: DIO_DDRC = Copy_u8PortMode; break;
		case DIO_PORT_D: DIO_DDRD = Copy_u8PortMode; break;
		default: break;
	}
}



void DIO_voidWritePortValue(DIO_PortId_t Copy_u8PortId, u8 Copy_u8PortValue) {
	switch(Copy_u8PortId) {
		case DIO_PORT_A: DIO_PORTA = Copy_u8PortValue; break;
		case DIO_PORT_B: DIO_PORTB = Copy_u8PortValue; break;
		case DIO_PORT_C: DIO_PORTC = Copy_u8PortValue; break;
		case DIO_PORT_D: DIO_PORTD = Copy_u8PortValue; break;
		default: break;
	}
}



u8 DIO_voidReadPortValue(DIO_PortId_t Copy_u8PortId) {
	u8 Local_u8PortValue = 0;
	switch(Copy_u8PortId) {
		case DIO_PORT_A: Local_u8PortValue = DIO_PINA; break;
		case DIO_PORT_B: Local_u8PortValue = DIO_PINB; break;
		case DIO_PORT_C: Local_u8PortValue = DIO_PINC; break;
		case DIO_PORT_D: Local_u8PortValue = DIO_PIND; break;
		default: break;
	}
	return Local_u8PortValue;
}



void DIO_voidSetPinMode(DIO_Pin_t Copy_u8Pin, DIO_PinMode_t Copy_u8PinMode) {
	u8 Local_u8PinId = Copy_u8Pin % 10;
	u8 Local_u8PortId = (Copy_u8Pin / 10) - 1;

	switch(Local_u8PortId) {
		case DIO_PORT_A: WRT_BIT(DIO_DDRA, Local_u8PinId, Copy_u8PinMode); break;
		case DIO_PORT_B: WRT_BIT(DIO_DDRB, Local_u8PinId, Copy_u8PinMode); break;
		case DIO_PORT_C: WRT_BIT(DIO_DDRC, Local_u8PinId, Copy_u8PinMode); break;
		case DIO_PORT_D: WRT_BIT(DIO_DDRD, Local_u8PinId, Copy_u8PinMode); break;
		default: break;
	}
}



void DIO_voidSetPinValue(DIO_Pin_t Copy_u8Pin) {
	u8 Local_u8PinId = Copy_u8Pin % 10;
	u8 Local_u8PortId = (Copy_u8Pin / 10) - 1;

	switch(Local_u8PortId) {
		case DIO_PORT_A: SET_BIT(DIO_PORTA, Local_u8PinId); break;
		case DIO_PORT_B: SET_BIT(DIO_PORTB, Local_u8PinId); break;
		case DIO_PORT_C: SET_BIT(DIO_PORTC, Local_u8PinId); break;
		case DIO_PORT_D: SET_BIT(DIO_PORTD, Local_u8PinId); break;
		default: break;
	}
}




void DIO_voidClearPinValue(DIO_Pin_t Copy_u8Pin) {
	u8 Local_u8PinId = Copy_u8Pin % 10;
	u8 Local_u8PortId = (Copy_u8Pin / 10) - 1;

	switch(Local_u8PortId) {
		case DIO_PORT_A: CLR_BIT(DIO_PORTA, Local_u8PinId); break;
		case DIO_PORT_B: CLR_BIT(DIO_PORTB, Local_u8PinId); break;
		case DIO_PORT_C: CLR_BIT(DIO_PORTC, Local_u8PinId); break;
		case DIO_PORT_D: CLR_BIT(DIO_PORTD, Local_u8PinId); break;
		default: break;
	}
}



void DIO_voidTogglePinValue(DIO_Pin_t Copy_u8Pin) {
	u8 Local_u8PinId = Copy_u8Pin % 10;
	u8 Local_u8PortId = (Copy_u8Pin / 10) - 1;

	switch(Local_u8PortId) {
		case DIO_PORT_A: TOG_BIT(DIO_PORTA, Local_u8PinId); break;
		case DIO_PORT_B: TOG_BIT(DIO_PORTB, Local_u8PinId); break;
		case DIO_PORT_C: TOG_BIT(DIO_PORTC, Local_u8PinId); break;
		case DIO_PORT_D: TOG_BIT(DIO_PORTD, Local_u8PinId); break;
		default: break;
	}
}



void DIO_voidWritePinValue(DIO_Pin_t Copy_u8Pin, DIO_PinValue_t Copy_u8Value) {
	u8 Local_u8PinId = Copy_u8Pin % 10;
	u8 Local_u8PortId = (Copy_u8Pin / 10) - 1;

	switch(Local_u8PortId) {
		case DIO_PORT_A: WRT_BIT(DIO_PORTA, Local_u8PinId, Copy_u8Value); break;
		case DIO_PORT_B: WRT_BIT(DIO_PORTB, Local_u8PinId, Copy_u8Value); break;
		case DIO_PORT_C: WRT_BIT(DIO_PORTC, Local_u8PinId, Copy_u8Value); break;
		case DIO_PORT_D: WRT_BIT(DIO_PORTD, Local_u8PinId, Copy_u8Value); break;
		default: break;
	}
}



DIO_PinValue_t DIO_u8GetPinValue(DIO_Pin_t Copy_u8Pin) {
	u8 Local_u8PinId = Copy_u8Pin % 10;
	u8 Local_u8PortId = (Copy_u8Pin / 10) - 1;
	u8 Local_u8PinValue = 0;

	switch(Local_u8PortId) {
		case DIO_PORT_A: Local_u8PinValue = GET_BIT(DIO_PINA, Local_u8PinId); break;
		case DIO_PORT_B: Local_u8PinValue = GET_BIT(DIO_PINB, Local_u8PinId); break;
		case DIO_PORT_C: Local_u8PinValue = GET_BIT(DIO_PINC, Local_u8PinId); break;
		case DIO_PORT_D: Local_u8PinValue = GET_BIT(DIO_PIND, Local_u8PinId); break;
		default: break;
	}
	return Local_u8PinValue;
}















