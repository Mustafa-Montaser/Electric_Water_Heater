/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup MCAL
 * This group contain MCAL drivers
 * @{
 * \addtogroup Timer0
 * Timer0 module driver
 * @{
 * \file Timer0_Config.h
 * \brief this file contains macros configuration for the Timer0 module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */



#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

/**
 * mode of waveform
 * values
 * {
 * 		TIMER0_WAVEFORM_NORMAL_MODE
 * 		TIMER0_WAVEFORM_PHASE_CORRECT_MODE
 * 		TIMER0_WAVEFORM_CTC_MODE
 * 		TIMER0_WAVEFORM_FAST_PWM_MODE
 * }
 * */
#define TIMER0_WAVEFORM_MODE		TIMER0_WAVEFORM_NORMAL_MODE


/**
 * timer_0 prescaler
 * values
 * {
 * 		TIMER0_STOP_PRESCALER
 * 		TIMER0_NO_PRESCALER
 * 		TIMER0_PRESCALER_8
 * 		TIMER0_PRESCALER_64
 * 		TIMER0_PRESCALER_256
 * 		TIMER0_PRESCALER_1024
 * 		TIMER0_EXT_CLK_FALLING
 * 		TIMER0_EXT_CLK_RISING
 * }
 * */
#define TIMER0_PRESCALER			TIMER0_PRESCALER_1024



/**
 * Timer0 input frequency in MHz (before prescaler)
 * */
#define TIMER0_F_OSC				16


/**
 * PWM modes
 * values
 * {
 * 		TIMER0_FAST_PWM_NON_INVERTING_MODE
 * 		TIMER0_FAST_PWM_INVERTING_MODE
 * }
 * */
#define TIMER0_FAST_PWM_MODE		TIMER0_FAST_PWM_NON_INVERTING_MODE


#endif /* TIMER0_CONFIG_H_ */
