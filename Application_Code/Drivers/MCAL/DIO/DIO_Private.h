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
 * \file DIO_Private.h
 * \brief this file contains contains registers addresses for the DIO module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


/*	Port A registers	*/
#define DIO_DDRA	*((volatile u8*)0x3A)
#define DIO_PORTA	*((volatile u8*)0x3B)
#define DIO_PINA	*((volatile u8*)0x39)


/*	Port B registers	*/
#define DIO_DDRB	*((volatile u8*)0x37)
#define DIO_PORTB	*((volatile u8*)0x38)
#define DIO_PINB	*((volatile u8*)0x36)


/*	Port C registers	*/
#define DIO_DDRC	*((volatile u8*)0x34)
#define DIO_PORTC	*((volatile u8*)0x35)
#define DIO_PINC	*((volatile u8*)0x33)


/*	Port D registers	*/
#define DIO_DDRD	*((volatile u8*)0x31)
#define DIO_PORTD	*((volatile u8*)0x32)
#define DIO_PIND	*((volatile u8*)0x30)


#endif /* DIO_PRIVATE_H_ */
