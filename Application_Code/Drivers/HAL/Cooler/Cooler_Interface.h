/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup Cooler
 * Cooler module driver
 * @{
 * \file Cooler_Interface.h
 * \brief this file contains function prototypes for the Cooler module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DRIVERS_HAL_COOLER_COOLER_INTERFACE_H_
#define DRIVERS_HAL_COOLER_COOLER_INTERFACE_H_

/* Functions Declarations */

/**
 * @brief Initialise the Cooler
 * @param local_u8CoolerPin cooler pin
 * @return void
 * */
void Cooler_voidInit(u8 local_u8CoolerPin);


/**
 * @brief Turn ON the Cooler
 * @param local_u8CoolerPin cooler pin
 * @return void
 * */
void Cooler_voidTurnOn(u8 local_u8CoolerPin);


/**
 * @brief Turn OFF the Cooler
 * @param local_u8CoolerPin cooler pin
 * @return void
 * */
void Cooler_voidTurnOff(u8 local_u8CoolerPin);


#endif /* DRIVERS_HAL_COOLER_COOLER_INTERFACE_H_ */
