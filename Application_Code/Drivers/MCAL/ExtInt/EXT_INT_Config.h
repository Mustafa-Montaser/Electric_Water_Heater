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
 * \file EXT_INT_Config.h
 * \brief this file contains macros configuration for the External Interrupt module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef EXT_INT_CONFIG_H_
#define EXT_INT_CONFIG_H_


/**
 * External Interrupt state for EXT0
 * values
 * {
 * 		EXT_INT_ENABLE
 * 		EXT_INT_DISABLE
 * }*/
#define EXT_INT0_STATE		EXT_INT_ENABLE

/**
 * External Interrupt state for EXT1
 * values
 * {
 * 		EXT_INT_ENABLE
 * 		EXT_INT_DISABLE
 * }*/
#define EXT_INT1_STATE		EXT_INT_ENABLE

/**
 * External Interrupt state for EXT2
 * values
 * {
 * 		EXT_INT_ENABLE
 * 		EXT_INT_DISABLE
 * }
 * */
#define EXT_INT2_STATE		EXT_INT_ENABLE



/* sense control 
	values = {
		EXT_INT_SENSE_CONTROL_LOW_LEVEL,		=> Int0, 1
		EXT_INT_SENSE_CONTROL_ANY_CHANGE,		=> Int0, 1
		EXT_INT_SENSE_CONTROL_FALLING_EDGE,		=> Int0, 1, 2
		EXT_INT_SENSE_CONTROL_RISING_EDGE		=> Int0, 1, 2
	}
*/


#if EXT_INT0_STATE == EXT_INT_ENABLE
/**
 * sense control for EXT0 is enabled
 * values
 * {
 * 		EXT_INT_SENSE_CONTROL_LOW_LEVEL
 * 		EXT_INT_SENSE_CONTROL_ANY_CHANGE
 * 		EXT_INT_SENSE_CONTROL_FALLING_EDGE
 * 		EXT_INT_SENSE_CONTROL_RISING_EDGE
 * }
 * */
#define EXT_INT0_SENSE_CTRL		EXT_INT_SENSE_CONTROL_FALLING_EDGE
#endif

#if EXT_INT1_STATE == EXT_INT_ENABLE
/**
 * sense control for EXT1 is enabled
 * values
 * {
 * 		EXT_INT_SENSE_CONTROL_LOW_LEVEL
 * 		EXT_INT_SENSE_CONTROL_ANY_CHANGE
 * 		EXT_INT_SENSE_CONTROL_FALLING_EDGE
 * 		EXT_INT_SENSE_CONTROL_RISING_EDGE
 * }
 * */
#define EXT_INT1_SENSE_CTRL		EXT_INT_SENSE_CONTROL_FALLING_EDGE
#endif

#if EXT_INT2_STATE == EXT_INT_ENABLE
/**
 * sense control for EXT2 is enabled
 * values
 * {
 * 		EXT_INT_SENSE_CONTROL_FALLING_EDGE
 * 		EXT_INT_SENSE_CONTROL_RISING_EDGE
 * }
 * */
#define EXT_INT2_SENSE_CTRL		EXT_INT_SENSE_CONTROL_FALLING_EDGE
#endif


#endif /* EXT_INT_CONFIG_H_ */
