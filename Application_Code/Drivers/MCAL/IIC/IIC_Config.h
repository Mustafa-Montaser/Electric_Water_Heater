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
 * \file IIC_Config.h
 * \brief this file contains macros configuration for the IIC module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DATA_MCAL_IIC_IIC_CONFIG_H_
#define DATA_MCAL_IIC_IIC_CONFIG_H_


/* Macros */

/** CPU frequency in Hz*/
#define F_OSC_HZ					16000000

/** SCL frequency in Hz */
#define IIC_F_SCL_HZ				400000

/** device slave address (when be a slave in network) */
#define IIC_SLAVE_ADDRESS			0x05


/**
 * mode of operation
 * values
 * {
 * 		IIC_MASTER_MODE
 * 		IIC_SLAVE_MODE
 * }
 * */
#define IIC_OPERATION_MODE			IIC_MASTER_MODE


/*
 * IIC_LISTEN_GENERAL_CALL_ENABLE
 * IIC_LISTEN_GENERAL_CALL_DISABLE
*/

/**
 * general call setting
 * values
 * {
 * 		IIC_LISTEN_GENERAL_CALL_ENABLE
 * 		IIC_LISTEN_GENERAL_CALL_DISABLE
 * }
 * */
#define IIC_LISTEN_GENERAL_CALL		IIC_LISTEN_GENERAL_CALL_ENABLE


#endif /* DATA_MCAL_IIC_IIC_CONFIG_H_ */
