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
 * \file IIC_Private.h
 * \brief this file contains contains registers addresses for the IIC module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DATA_MCAL_IIC_IIC_PRIVATE_H_
#define DATA_MCAL_IIC_IIC_PRIVATE_H_



#define IIC_TWBR				*((volatile u8*)0x20)

#define IIC_TWBR_TWBR7			7
#define IIC_TWBR_TWBR6			6
#define IIC_TWBR_TWBR5			5
#define IIC_TWBR_TWBR4			4
#define IIC_TWBR_TWBR3			3
#define IIC_TWBR_TWBR2			2
#define IIC_TWBR_TWBR1			1
#define IIC_TWBR_TWBR0			0


#define IIC_TWCR				*((volatile u8*)0x56)

#define IIC_TWCR_TWINT 			7
#define IIC_TWCR_TWEA           6
#define IIC_TWCR_TWSTA          5
#define IIC_TWCR_TWSTO          4
#define IIC_TWCR_TWWC           3
#define IIC_TWCR_TWEN           2
#define IIC_TWCR_TWIE           0


#define IIC_TWSR				*((volatile u8*)0x21)

#define IIC_TWSR_TWS7   		 7
#define IIC_TWSR_TWS6            6
#define IIC_TWSR_TWS5            5
#define IIC_TWSR_TWS4            4
#define IIC_TWSR_TWS3            3
#define IIC_TWSR_TWPS1           2
#define IIC_TWSR_TWPS0           0


#define IIC_TWDR				*((volatile u8*)0x23)

#define IIC_TWDR_TWD7  			7
#define IIC_TWDR_TWD6           6
#define IIC_TWDR_TWD5           5
#define IIC_TWDR_TWD4           4
#define IIC_TWDR_TWD3           3
#define IIC_TWDR_TWD2           2
#define IIC_TWDR_TWD1           1
#define IIC_TWDR_TWD0           0


#define IIC_TWAR				*((volatile u8*)0x22)

#define IIC_TWAR_TWA6   		 7
#define IIC_TWAR_TWA5            6
#define IIC_TWAR_TWA4            5
#define IIC_TWAR_TWA3            4
#define IIC_TWAR_TWA2            3
#define IIC_TWAR_TWA1            2
#define IIC_TWAR_TWA0            1
#define IIC_TWAR_TWGCE           0



#endif /* DATA_MCAL_IIC_IIC_PRIVATE_H_ */
