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
 * \file EXT_INT_Interface.h
 * \brief this file contains function prototypes for the External_Interrupt module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */



#ifndef EXT_INT_INTERFACE_H_
#define EXT_INT_INTERFACE_H_

/* Macros */

/* EXT INT state */
#define EXT_INT_ENABLE		1
#define EXT_INT_DISABLE		0

/* Sense control */
#define EXT_INT_SENSE_CONTROL_LOW_LEVEL		0b00
#define EXT_INT_SENSE_CONTROL_ANY_CHANGE	0b01
#define EXT_INT_SENSE_CONTROL_FALLING_EDGE	0b10
#define EXT_INT_SENSE_CONTROL_RISING_EDGE	0b11


/* functions declaration */

/**
 * @brief Initialise External_Interrupt
 * @param void
 * @return void
 * */
void ExtInt_voidInit();

/**
 * @brief Disable external interrupt 0
 * @param void
 * @return void
 * */
void ExtInt_voidDisableInt0();

/**
 * @brief Disable external interrupt 1
 * @param void
 * @return void
 * */
void ExtInt_voidDisableInt1();

/**
 * @brief Disable external interrupt 2
 * @param void
 * @return void
 * */
void ExtInt_voidDisableInt2();

/**
 * @brief Enable external interrupt 0
 * @param void
 * @return void
 * */
void ExtInt_voidEnableInt0();

/**
 * @brief Enable external interrupt1
 * @param void
 * @return void
 * */
void ExtInt_voidEnableInt1();

/**
 * @brief Enable external interrupt 2
 * @param void
 * @return void
 * */
void ExtInt_voidEnableInt2();

/**
 * @brief setting call back for external interrupt 0
 * @param ptr pointer to function
 * @return void
 * */
void ExtInt_SetCallBack0(void (*ptr) (void));

/**
 * @brief setting call back for external interrupt 1
 * @param ptr pointer to function
 * @return void
 * */
void ExtInt_SetCallBack1(void (*ptr) (void));

/**
 * @brief setting call back for external interrupt 1
 * @param ptr pointer to function
 * @return void
 * */
void ExtInt_SetCallBack2(void (*ptr) (void));





#endif /* EXT_INT_INTERFACE_H_ */
