/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup MCAL
 * This group contain MCAL drivers
 * @{
 * \addtogroup IIC
 * IIC module driver
 * @{
 * \file IIC_Program.c
 * \brief this file contains contains implementation for the IIC module
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

#include "../DIO/DIO_Interface.h"

#include "IIC_Config.h"
#include "IIC_Interface.h"
#include "IIC_Private.h"


/* functions definition */


void IIC_voidInit(void) {

	/* F_SCL Setting */
	#if IIC_OPERATION_MODE == IIC_MASTER_MODE
		if(((F_OSC_HZ - (16 * IIC_F_SCL_HZ)) / (2 * IIC_F_SCL_HZ * 1)) <= 255) {
			IIC_TWBR = (F_OSC_HZ - (16 * IIC_F_SCL_HZ)) / (2 * IIC_F_SCL_HZ * 1);
			WRT_2BITS(IIC_TWSR, IIC_TWSR_TWPS0, IIC_BIT_RATE_PRESCALER_1);

		} else if(((F_OSC_HZ - (16 * IIC_F_SCL_HZ)) / (2 * IIC_F_SCL_HZ * 4)) <= 255) {
			IIC_TWBR = (F_OSC_HZ - (16 * IIC_F_SCL_HZ)) / (2 * IIC_F_SCL_HZ * 4);
			WRT_2BITS(IIC_TWSR, IIC_TWSR_TWPS0, IIC_BIT_RATE_PRESCALER_4);

		} else if(((F_OSC_HZ - (16 * IIC_F_SCL_HZ)) / (2 * IIC_F_SCL_HZ * 16)) <= 255) {
			IIC_TWBR = (F_OSC_HZ - (16 * IIC_F_SCL_HZ)) / (2 * IIC_F_SCL_HZ * 16);
			WRT_2BITS(IIC_TWSR, IIC_TWSR_TWPS0, IIC_BIT_RATE_PRESCALER_16);

		} else {
			IIC_TWBR = (F_OSC_HZ - (16 * IIC_F_SCL_HZ)) / (2 * IIC_F_SCL_HZ * 64);
			WRT_2BITS(IIC_TWSR, IIC_TWSR_TWPS0, IIC_BIT_RATE_PRESCALER_64);
		}
	#endif

	/* IIC Enable Acknowledge Bit */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWEA);

	/* Write Slave Address [For This Device] */
	IIC_TWAR = IIC_SLAVE_ADDRESS << 1;

	/* Listen To General Call State */
	WRT_BIT(IIC_TWAR, IIC_TWAR_TWGCE, IIC_LISTEN_GENERAL_CALL);

	/* Clear The Flag ( with [SET] ) */
//	SET_BIT(IIC_TWCR, IIC_TWCR_TWINT);

	/* IIC Enable */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWEN);

}



IIC_State_t IIC_enumStartCondition(void) {

	IIC_State_t local_enumState = IIC_NOK;

	/* Start Condition */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWSTA);

	/* Clear The Flag ( with [SET] ) */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWINT);

	/* Waiting till Job Is Done [Start Condition] */
	u32 local_u32Loop = 0;
	while(GET_BIT(IIC_TWCR, IIC_TWCR_TWINT) == 0 && local_u32Loop < IIC_TIMEOUT) {
		local_u32Loop++;
	}

	if(local_u32Loop >= IIC_TIMEOUT) {
		local_enumState = IIC_TIMEOUT_ERR;
	} else {
		if((IIC_TWSR & 0xF8) == 0x08)
			local_enumState = IIC_OK;
		else
			local_enumState = IIC_START_COND_ERR;
	}

	/* Clear TWSTA Bit After Start Condition */
//	CLR_BIT(IIC_TWCR, IIC_TWCR_TWSTA);

	return local_enumState;

}



IIC_State_t IIC_enumStopCondition(void) {

	IIC_State_t local_enumState = IIC_NOK;

	/* Stop Condition */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWSTO);

	/* Clear The Flag ( with [SET] ) */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWINT);

	/* Waiting till [Stop Condition] is done */
	u32 local_u32Loop = 0;
	while(GET_BIT(IIC_TWCR, IIC_TWCR_TWSTO) == 1 && local_u32Loop < IIC_TIMEOUT) {
		local_u32Loop++;
	}

	if(local_u32Loop >= IIC_TIMEOUT)
		local_enumState = IIC_TIMEOUT_ERR;
	else
		local_enumState = IIC_OK;

	return local_enumState;

}



IIC_State_t IIC_enumSendSlaveAddressWithWrite(u8 local_u8SlaveAddress) {

	IIC_State_t local_enumState = IIC_NOK;

	/* Writing Slave Address + [WRITE] */
	IIC_TWDR = local_u8SlaveAddress << 1;

	/* Clear Required Bits in TWCR */
	CLR_BIT(IIC_TWCR, IIC_TWCR_TWSTA);
	CLR_BIT(IIC_TWCR, IIC_TWCR_TWSTO);

	/* Clear The Flag ( with [SET] ) */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWINT);

	/* Waiting till Job Is Done [Send Slave Address + Write] */
	u32 local_u32Loop = 0;
	while(GET_BIT(IIC_TWCR, IIC_TWCR_TWINT) == 0 && local_u32Loop < IIC_TIMEOUT) {
		local_u32Loop++;
	}

	if(local_u32Loop >= IIC_TIMEOUT) {
		local_enumState = IIC_TIMEOUT_ERR;
	} else {
		if((IIC_TWSR & 0xF8) == 0x18)
			local_enumState = IIC_OK;
		else if((IIC_TWSR & 0xF8) == 0x20)
			local_enumState = IIC_SLA_ADD_WRT_NACK;
		else if((IIC_TWSR & 0xF8) == 0x38)
			local_enumState = IIC_ARBITRATION_LOST;
		else
			local_enumState = IIC_SLA_ADD_WRT_ERR;
	}

	return local_enumState;

}



IIC_State_t IIC_enumSendSlaveAddressWithRead(u8 local_u8SlaveAddress) {

	IIC_State_t local_enumState = IIC_NOK;

	/* Writing Slave Address With [READ] */
	IIC_TWDR = (local_u8SlaveAddress << 1) | 1;

	/* Clear Required Bits in TWCR */
	CLR_BIT(IIC_TWCR, IIC_TWCR_TWSTA);
	CLR_BIT(IIC_TWCR, IIC_TWCR_TWSTO);

	/* Clear The Flag ( with [SET] ) */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWINT);

	/* Waiting till Job Is Done [Send Slave Address with Read]  */
	u32 local_u32Loop = 0;
	while(GET_BIT(IIC_TWCR, IIC_TWCR_TWINT) == 0 && local_u32Loop < IIC_TIMEOUT) {
		local_u32Loop++;
	}

	if(local_u32Loop >= IIC_TIMEOUT) {
		local_enumState = IIC_TIMEOUT_ERR;
	} else {
		if((IIC_TWSR & 0xF8) == 0x40)
			local_enumState = IIC_OK;
		else if((IIC_TWSR & 0xF8) == 0x48)
			local_enumState = IIC_SLA_ADD_READ_NACK;
		else if((IIC_TWSR & 0xF8) == 0x38)
			local_enumState = IIC_ARBITRATION_LOST; // or IIC_SLA_ADD_READ_NACK
		else
			local_enumState = IIC_SLA_ADD_READ_ERR;
	}

	return local_enumState;

}



IIC_State_t IIC_enumSendByte(u8 local_u8Data) {

	IIC_State_t local_enumState = IIC_NOK;

	/* Sending Byte */
	IIC_TWDR = local_u8Data;

	/* Clear Required Bits in TWCR */
	CLR_BIT(IIC_TWCR, IIC_TWCR_TWSTA);
	CLR_BIT(IIC_TWCR, IIC_TWCR_TWSTO);

	/* Clear The Flag ( with [SET] ) */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWINT);

	/* Waiting till Job Is Done [Sending Data] */
	u32 local_u32Loop = 0;
	while(GET_BIT(IIC_TWCR, IIC_TWCR_TWINT) == 0 && local_u32Loop < IIC_TIMEOUT) {
		local_u32Loop++;
	}

	if(local_u32Loop >= IIC_TIMEOUT) {
		local_enumState = IIC_TIMEOUT_ERR;
	} else {
		if((IIC_TWSR & 0xF8) == 0x28)
			local_enumState = IIC_OK;
		else if((IIC_TWSR & 0xF8) == 0x30)
			local_enumState = IIC_M_SEND_BYTE_NACK;
		else if((IIC_TWSR & 0xF8) == 0x38)
			local_enumState = IIC_ARBITRATION_LOST; // or IIC_SLA_ADD_READ_NACK
		else
			local_enumState = IIC_M_SEND_BYTE_ERR;
	}

	return local_enumState;

}



IIC_State_t IIC_enumReceiveByte(u8 *local_u8PtrReceivedByte) {

	IIC_State_t local_enumState = IIC_NOK;

	/* Clear and Set Required Bits in TWCR */
	CLR_BIT(IIC_TWCR, IIC_TWCR_TWSTA);
	CLR_BIT(IIC_TWCR, IIC_TWCR_TWSTO);
	SET_BIT(IIC_TWCR, IIC_TWCR_TWEA);

	/* Clear The Flag ( with [SET] ) */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWINT);

	/* Waiting till Job Is Done [Reading Data]  */
	u32 local_u32Loop = 0;
	while(GET_BIT(IIC_TWCR, IIC_TWCR_TWINT) == 0 && local_u32Loop < IIC_TIMEOUT) {
		local_u32Loop++;
	}

	if(local_u32Loop >= IIC_TIMEOUT) {
		local_enumState = IIC_TIMEOUT_ERR;
	} else {
		if((IIC_TWSR & 0xF8) == 0x50) {
			local_enumState = IIC_OK;
			*local_u8PtrReceivedByte = IIC_TWDR;
		}
		else if((IIC_TWSR & 0xF8) == 0x58)
			local_enumState = IIC_M_RECEIVE_BYTE_NACK;
		else
			local_enumState = IIC_M_SEND_BYTE_ERR;
	}

	return local_enumState;

}



IIC_State_t IIC_enumRepeatStart(void) {

	IIC_State_t local_enumState = IIC_NOK;

	/* Repeat Start */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWSTA);

	/* Clear The Flag ( with [SET] ) */
	SET_BIT(IIC_TWCR, IIC_TWCR_TWINT);

	/* Waiting till Job Is Done [Repeat Start]  */
	u32 local_u32Loop = 0;
	while(GET_BIT(IIC_TWCR, IIC_TWCR_TWINT) == 0 && local_u32Loop < IIC_TIMEOUT) {
		local_u32Loop++;
	}

	if(local_u32Loop >= IIC_TIMEOUT) {
		local_enumState = IIC_TIMEOUT_ERR;
	} else {
		if((IIC_TWSR & 0xF8) == 0x10)
			local_enumState = IIC_OK;
		else
			local_enumState = IIC_RE_START_ERR;
	}

	return local_enumState;

}








