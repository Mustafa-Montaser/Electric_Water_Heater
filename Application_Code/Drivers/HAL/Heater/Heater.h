/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup Heater
 * Heater module driver
 * @{
 * \file Cooler_Interface.h
 * \brief this file contains function prototypes for the Heater module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */

#ifndef DRIVERS_HAL_HEATER_HEATER_H_
#define DRIVERS_HAL_HEATER_HEATER_H_

/* Functions declaration */

/**
 * \brief Heater initialisation
 * \param local_u8HeaterPin heater pin
 * \return void
 * */
void Heater_voidInit(u8 local_u8HeaterPin);

/**
 * \brief Heater turn ON
 * \param local_u8HeaterPin heater pin
 * \return void
 * */
void Heater_voidTurnOn(u8 local_u8HeaterPin);

/**
 * \brief Heater turn OFF
 * \param local_u8HeaterPin heater pin
 * \return void
 * */
void Heater_voidTurnOff(u8 local_u8HeaterPin);

#endif /* DRIVERS_HAL_HEATER_HEATER_H_ */

