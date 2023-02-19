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
 * \file GIE_Interface.h
 * \brief this file contains function prototypes for the GIE module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef GIE_INTERFACE_H_
#define GIE_INTERFACE_H_

/* function declaration */

/**
 * @brief enable global interrupt
 * @param void
 * @return void
 * */
void GIE_voidEnableGlobalINT();

/**
 * @brief disable global interrupt
 * @param void
 * @return void
 * */
void GIE_voidDisableGlobalINT();


#endif /* GIE_INTERFACE_H_ */
