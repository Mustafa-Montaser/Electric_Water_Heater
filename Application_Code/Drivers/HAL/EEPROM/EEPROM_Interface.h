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
 * \file EEPROM_Interface.h
 * \brief this file contains function prototypes for the EEPROM module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */

#ifndef DATA_HAL_EEPROM_EEPROM_INTERFACE_H_
#define DATA_HAL_EEPROM_EEPROM_INTERFACE_H_


/// static MSB address for pages in EEPROM
#define EEPROM_MSB_ADDRESS		0x50


/* Special Types */

/**
 * @enum EEPROM_State_t
 * Refer to EEPROM state after writing or receiving data
 * @var EEPROM_State_t::EEPROM_OK
 * 		data is written or read successfully
 * @var EEPROM_State_t::EEPROM_NOK
 * 		error in reading from or writing into EEPROM
 * */
typedef enum {
	EEPROM_OK,
	EEPROM_NOK
} EEPROM_State_t;


/* Functions declaration */

/**
 * @brief Initialise EEPROM
 * @param void
 * @return void
 * */
void EEPROM_voidInit();

/**
 * @brief writing byte data into EEPROM
 * @param local_u8DataByte byte data to be written into EEPROM
 * @param local_u8PageAddress page address inside EEPROM
 * @param local_u8ByteAddress byte address inside the selected page
 * @return EEPROM_State_t
 * */
EEPROM_State_t EEPROM_voidWriteByte(u8 local_u8DataByte, u8 local_u8PageAddress, u8 local_u8ByteAddress);

/**
 * @brief reading byte from EEPROM
 * @param local_u8PageAddress page address inside EEPROM
 * @param local_u8ByteAddress byte address inside the selected page
 * @param local_u8PtrReceivedData pointer to buffer where data will be set into after reading
 * @return EEPROM_State_t
 * */
EEPROM_State_t EEPROM_u8ReadByte(u8 local_u8PageAddress, u8 local_u8ByteAddress, u8 *local_u8PtrReceivedData);


#endif /* DATA_HAL_EEPROM_EEPROM_INTERFACE_H_ */
