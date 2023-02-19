/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup MCAL
 * This group contain MCAL drivers
 * @{
 * \addtogroup ADC
 * ADC module driver
 * @{
 * \file ADC_Config.h
 * \brief this file contains macros configuration for the ADC module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */



#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


/** Input Frequency for ADC */
#define ADC_INPUT_FREQ		16000000UL


/** ADC reference voltage
 * values
 * {
 * 		ADC_VOLT_REF_EXTERNAL,
 * 		ADC_VOLT_REF_AVCC,
 * 		ADC_VOLT_REF_INTERNAL_2V56
 * }*/
#define ADC_VOLT_REF			ADC_VOLT_REF_EXTERNAL


/** reference voltage value */
#define ADC_VOLT_REF_VALUE		5


/** Prescaler value
 * {
 * 		ADC_PRESCALER_2  ,
 * 		ADC_PRESCALER_4	 ,
 * 		ADC_PRESCALER_8	 ,
 * 		ADC_PRESCALER_16 ,
 * 		ADC_PRESCALER_32 ,
 * 		ADC_PRESCALER_64 ,
 * 		ADC_PRESCALER_128
 * } */
#define ADC_PRESCALER			ADC_PRESCALER_128


/** values
 * {
 * 		ADC_AUTO_TRIGGER_ENABLE
 * 		ADC_AUTO_TRIGGER_DISABLE
 * } */
#define ADC_AUTO_TRIGGER_STATE		ADC_AUTO_TRIGGER_DISABLE


/** ADC source trigger
 * values
 * {
 * 		ADC_TRIG_SRC_FREE_RUNNING
 * 		ADC_TRIG_SRC_ANALOD_COMP
 * 		ADC_TRIG_SRC_EXT_INT0
 * 		ADC_TRIG_SRC_TIMER0_COM_MATCH
 * 		ADC_TRIG_SRC_TIMER0_OVERFLOW
 * 		ADC_TRIG_SRC_TIMER_COM_MATCH_B
 * 		ADC_TRIG_SRC_TIMER1_OVERFLOW
 * 		ADC_TRIG_SRC_TIMER1_CAP_EVENT
 * } */
#define ADC_TRIG_SRC			ADC_TRIG_SRC_FREE_RUNNING


/** ADC mode
 * values
 * {
 *  	ADC_POLLING_MODE
 *  	ADC_INTERRUPT_MODE
 * }*/
#define ADC_MODE				ADC_POLLING_MODE



#endif /* ADC_CONFIG_H_ */
