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
 * \file DSSD_Interface.h
 * \brief this file contains function prototypes for the DSSD module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DSSD_INTERFACE_H_
#define DSSD_INTERFACE_H_


/** DSSD operation modes { BCD, normal } */
#define DSSD_BCD_MODE		0
#define DSSD_NORMAL_MODE	1


/** DSSD digits { ones, tens } */
#define DSSD_DISPLAY_ONES	0
#define DSSD_DISPLAY_TENS	1


/** DSSD state { on, off } */
#define DSSD_ON				1
#define DSSD_OFF			0



/* APP Functions Declarations */


/**
 * @brief Initialise the DSSD
 * @param void
 * @return void
 * */
void DSSD_voidInit();


/**
 * @brief Enable EN1 to display the right digit
 * @param void
 * @return void
 * */
void DSSD_voidEN1();


/**
 * @brief Enable EN2 to display the left digit
 * @param void
 * @return void
 * */
void DSSD_voidEN2();


/**
 * @brief Disable DSSD [act as turn it OFF]
 * @param void
 * @return void
 * */
void DSSD_voidDisableAll();


/**
 * @brief Display Number from 2 digits
 * @param local_u8Num the desired number to be printed
 * @param u8Digit desired digit to be displayed [DSSD_DISPLAY_ONES, DSSD_DISPLAY_TENS]
 * @return void
 * */
void DSSD_voidDisplay(u8 local_u8Num, u8 u8Digit);


/**
 * @brief get current state [ON, OFF]
 * @param void
 * @return local_u8state state
 * */
u8 DSSD_u8Status();



#endif /* DSSD_INTERFACE_H_ */
