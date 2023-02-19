/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup EEPROM
 * EEPROM module driver
 * @{
 * \file EEPROM_Program.c
 * \brief this file contains contains implementation for the EEPROM module
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

#include "../../MCAL/IIC/IIC_Config.h"
#include "../../MCAL/IIC/IIC_Interface.h"

#include "EEPROM_Interface.h"


/* Functions definitions */

void EEPROM_voidInit() {
	IIC_voidInit();
}


EEPROM_State_t EEPROM_voidWriteByte(u8 local_u8DataByte, u8 local_u8PageAddress, u8 local_u8ByteAddress) {
	u8 local_u8State = IIC_NOK;
	local_u8State = IIC_enumStartCondition();
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumSendSlaveAddressWithWrite(EEPROM_MSB_ADDRESS | local_u8PageAddress);
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumSendByte(local_u8ByteAddress);
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumSendByte(local_u8DataByte);
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumStopCondition();

	if(local_u8State == IIC_OK) local_u8State = EEPROM_OK;
	else local_u8State = EEPROM_NOK;
	return local_u8State;
}

EEPROM_State_t EEPROM_u8ReadByte(u8 local_u8PageAddress, u8 local_u8ByteAddress, u8 *local_u8PtrReceivedData) {
	u8 local_u8State = IIC_NOK;
	local_u8State = IIC_enumStartCondition();
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumSendSlaveAddressWithWrite(EEPROM_MSB_ADDRESS | local_u8PageAddress);
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumSendByte(local_u8ByteAddress);
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumRepeatStart();
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumSendSlaveAddressWithRead(EEPROM_MSB_ADDRESS | local_u8PageAddress);
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumReceiveByte(local_u8PtrReceivedData);
	if(local_u8State == IIC_OK)
		local_u8State = IIC_enumStopCondition();

	if(local_u8State == IIC_OK) local_u8State = EEPROM_OK;
	else local_u8State = EEPROM_NOK;
	return local_u8State;
}



