/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup SensorLM35
 * SensorLM35 module driver
 * @{
 * \file SensorLM35_Interface.h
 * \brief this file contains function prototypes for the SensorLM35 module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DRIVERS_HAL_SENSORLM35_SENSORLM35_INTERFACE_H_
#define DRIVERS_HAL_SENSORLM35_SENSORLM35_INTERFACE_H_

/* Functions Declarations */

/**
 * @brief Initialise LM35 sensor
 * @param void
 * @return void
 * */
void SensorLM35_voidInit();

/**
 * @brief read current temperature
 * @param local_u8Pin sensor pin
 * @return sensor read value
 * */
u16 SensorLM35_u16ReadTemp(u8 local_u8Pin);

#endif /* DRIVERS_HAL_SENSORLM35_SENSORLM35_INTERFACE_H_ */
