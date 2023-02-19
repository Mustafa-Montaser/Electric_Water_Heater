/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup LED
 * LED module driver
 * @{
 * \file Cooler_Interface.h
 * \brief this file contains function prototypes for the LED module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DRIVERS_HAL_LED_LED_INTERFACE_H_
#define DRIVERS_HAL_LED_LED_INTERFACE_H_

/* functions declaration */


/**
 * @brief Initialise LED
 * @param local_u8LedPin LED pin
 * @return void
 * */
void LED_voidInit(u8 local_u8LedPin);

/**
 * @brief turn on LED
 * @param local_u8LedPin LED pin
 * @return void
 * */
void LED_voidTurnOn(u8 local_u8LedPin);

/**
 * @brief turn off LED
 * @param local_u8LedPin LED pin
 * @return void
 * */
void LED_voidTurnOff(u8 local_u8LedPin);

/**
 * @brief toggle LED
 * @param local_u8LedPin LED pin
 * @return void
 * */
void LED_voidToggle(u8 local_u8LedPin);


#endif /* DRIVERS_HAL_LED_LED_INTERFACE_H_ */
