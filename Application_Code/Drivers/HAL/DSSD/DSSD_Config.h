/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup DSSD
 * Decoded seven segment display module driver
 * @{
 * \file DSSD_Config.h
 * \brief this file contains configuration macros for the DSSD module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DSSD_CONFIG_H_
#define DSSD_CONFIG_H_



/// modes of DSSD { DSSD_NORMAL_MODE, DSSD_BCD_MODE }
#define DSSD_MODE			DSSD_NORMAL_MODE

/// enable_1 pin
#define DSSD_EN1			DIO_PB1

/// enable_2 pin
#define DSSD_EN2			DIO_PB0

/// DIP pin
#define DSSD_DIP			DIO_PA7

/// Data port if data pins is connected to the same port
#define DSSD_DATA_REG		DIO_PORTA

/// Control port if control pins is connected to the same port
#define DSSD_CTRL_REG		DIO_PORTB

/**
 * Data pins [A - G]
 * If using BCD mode, [E, F, G] don't care
 * */
#define DSSD_A				DIO_PA0
#define DSSD_B				DIO_PA1
#define DSSD_C				DIO_PA2
#define DSSD_D				DIO_PA3
#define DSSD_E				DIO_PA4
#define DSSD_F				DIO_PA5
#define DSSD_G				DIO_PA6






#endif /* DSSD_CONFIG_H_ */
