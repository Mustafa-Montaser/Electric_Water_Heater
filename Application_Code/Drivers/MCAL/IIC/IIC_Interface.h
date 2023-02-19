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
 * \file IIC_Interface.h
 * \brief this file contains function prototypes for the IIC module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */



#ifndef DATA_MCAL_IIC_IIC_INTERFACE_H_
#define DATA_MCAL_IIC_IIC_INTERFACE_H_



/* Macros */

#define IIC_BIT_RATE_PRESCALER_1				0b00
#define IIC_BIT_RATE_PRESCALER_4				0b01
#define IIC_BIT_RATE_PRESCALER_16				0b10
#define IIC_BIT_RATE_PRESCALER_64				0b11

#define IIC_MASTER_MODE							1
#define IIC_SLAVE_MODE							0

#define IIC_LISTEN_GENERAL_CALL_ENABLE			1
#define IIC_LISTEN_GENERAL_CALL_DISABLE			0

#define IIC_TIMEOUT								16000000UL


/**
 * @enum IIC_State_t
 * 		refer to IIC error states in each step of the communication
 * */
typedef enum {
	IIC_OK,
	IIC_NOK,
	IIC_START_COND_ERR,
	IIC_RE_START_ERR,
	IIC_STOP_COND_ERR,
	IIC_SLA_ADD_WRT_ERR,
	IIC_SLA_ADD_WRT_NACK,
	IIC_ARBITRATION_LOST,
	IIC_SLA_ADD_READ_ERR,
	IIC_SLA_ADD_READ_NACK,
	IIC_M_SEND_BYTE_ERR,
	IIC_M_SEND_BYTE_NACK,
	IIC_M_RECEIVE_BYTE_ERR,
	IIC_M_RECEIVE_BYTE_NACK,
	IIC_S_SEND_BYTE_ERR,
	IIC_S_RECEIVE_BYTE_ERR,
	IIC_TIMEOUT_ERR
} IIC_State_t;



/* functions declaration */


/**
 * @brief Initialise IIC module
 * @param void
 * @return void
 * */
void IIC_voidInit(void);

/**
 * @brief starting condition
 * @param void
 * @return error state
 * */
IIC_State_t IIC_enumStartCondition(void);

/**
 * @brief stop condition
 * @param void
 * @return error state
 * */
IIC_State_t IIC_enumStopCondition(void);

/**
 * @brief sending slave address with write operation
 * @param local_u8SlaveAddress slave address
 * @return error state
 * */
IIC_State_t IIC_enumSendSlaveAddressWithWrite(u8 local_u8SlaveAddress);

/**
 * @brief sending slave address with read operation
 * @param local_u8SlaveAddress slave address
 * @return error state
 * */
IIC_State_t IIC_enumSendSlaveAddressWithRead(u8 local_u8SlaveAddress);

/**
 * @brief sending byte of data
 * @param local_u8Data data to be sent
 * @return error state
 * */
IIC_State_t IIC_enumSendByte(u8 local_u8Data);

/**
 * @brief receiving byte of data
 * @param local_u8PtrReceivedByte pointer to data buffer where to receive data
 * @return error state
 * */
IIC_State_t	IIC_enumReceiveByte(u8 *local_u8PtrReceivedByte);

/**
 * @brief repeat start
 * @param void
 * @return void
 * */
IIC_State_t IIC_enumRepeatStart(void);


#endif /* DATA_MCAL_IIC_IIC_INTERFACE_H_ */















