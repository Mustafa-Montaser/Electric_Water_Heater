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
 * \file Timer0_Interface.h
 * \brief this file contains function prototypes for the Timer0 module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */



#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

/* MACROS */

#define TIMER0_WAVEFORM_NORMAL_MODE			0
#define TIMER0_WAVEFORM_CTC_MODE			1
#define TIMER0_WAVEFORM_FAST_PWM_MODE		2
#define TIMER0_WAVEFORM_PHASE_CORRECT_MODE	3

#define TIMER0_STOP_PRESCALER				0b000
#define TIMER0_NO_PRESCALER					0b001
#define TIMER0_PRESCALER_8					0b010
#define	TIMER0_PRESCALER_64					0b011
#define TIMER0_PRESCALER_256				0b100
#define TIMER0_PRESCALER_1024				0b101
#define TIMER0_EXT_CLK_FALLING				0b110
#define TIMER0_EXT_CLK_RISING				0b111

#define TIMER0_FAST_PWM_NON_INVERTING_MODE	0
#define TIMER0_FAST_PWM_INVERTING_MODE		1



/* fucntions declaration */


/**
 * @brief Initialise timer0
 * @param void
 * @return void
 * */
void Timer0_voidInit();

/**
 * @brief setting time
 * @param copy_u8Time time in msec
 * @return void
 * */
void Timer0_voidSetTime(u32 copy_u8Time);

/**
 * @brief start timing
 * @param void
 * @return void
 * */
void Timer0_voidStart();

/**
 * @brief stop time
 * @param void
 * @return void
 * */
void Timer0_voidStop();

/**
 * @brief callback function when timer is interrupt
 * @param ptr pointer to function
 * @return void
 * */
void Timer0_voidSetCallBack(void (*ptr) (void));

/**
 * @brief PWM Initialise
 * @param void
 * @return void
 * */
void Timer0_voidPwmInit();

/**
 * @brief duty cycle setting for PWM
 * @param local_u8DuctyCycle duty cycle value
 * @return void
 * */
void Timer0_voidSetPwmDutyCycle(u8 local_u8DuctyCycle);

/**
 * @brief start PWM
 * @param void
 * @return void
 * */
void Timer0_voidStartPwm();

/**
 * @brief stop PWM
 * @param void
 * @return void
 * */
void Timer0_voidStopPwm();

#endif /* TIMER0_INTERFACE_H_ */

