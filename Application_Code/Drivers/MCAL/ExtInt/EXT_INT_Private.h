/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup MCAL
 * This group contain MCAL drivers
 * @{
 * \addtogroup External_Interrupt
 * External_Interrupt module driver
 * @{
 * \file ADC_Private.h
 * \brief this file contains contains registers addresses for the External_Interrupt module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef EXT_INT_PRIVATE_H_
#define EXT_INT_PRIVATE_H_


/* EXT INT REGISTERS */
#define EXTINT_MCUCR	*((volatile u8*)0x55) /* sense for INT0, 1 */
#define EXTINT_MCUCSR	*((volatile u8*)0x54) /* sense for INT2 */
#define EXTINT_GICR		*((volatile u8*)0x5B) /* PIE enable */
#define EXTINT_GIFR		*((volatile u8*)0x5A) /* INT flag */

/* Ext Int. Pins */
#define EXT_INT0_PIN	DIO_PD2
#define EXT_INT1_PIN	DIO_PD3
#define EXT_INT2_PIN	DIO_PB2


/* EXT INT BITS IN REGISTERS */
#define EXTINT_MCUCR_ISC00		0
#define EXTINT_MCUCR_ISC01 		1
#define EXTINT_MCUCR_ISC10 		2
#define EXTINT_MCUCR_ISC11 		3

#define EXTINT_MCUCSR_ISC2		6

#define EXTINT_GICR_INT0 		6
#define EXTINT_GICR_INT1 		7
#define EXTINT_GICR_INT2		5

#define EXTINT_GIFR_INTF0 		6
#define EXTINT_GIFR_INTF1 		7
#define EXTINT_GIFR_INTF2		5


#endif /* EXT_INT_PRIVATE_H_ */
