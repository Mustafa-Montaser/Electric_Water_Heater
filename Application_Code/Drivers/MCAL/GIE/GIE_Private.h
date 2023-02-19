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
 * \file GIE_Private.h
 * \brief this file contains contains registers addresses for the GIE module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef GIE_PRIVATE_H_
#define GIE_PRIVATE_H_


/** GLOBAL Interrupt Register */
#define GIE_SREG	*((volatile u8*)0x5F)


/** GLOBAL Interrupt Enable I_BIT Bit */
#define GIE_SREG_I	7


#endif /* GIE_PRIVATE_H_ */
