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
 * \file ADC_Interface.h
 * \brief this file contains function prototypes for the ADC module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_



/* Macros */
	
#define ADC_RESOLUTION					1024

#define ADC_VOLT_REF_EXTERNAL			0b00
#define ADC_VOLT_REF_AVCC				0b01
#define ADC_VOLT_REF_INTERNAL_2V56		0b11


#define ADC_CH_ADC0						0b00000
#define ADC_CH_ADC1						0b00001
#define ADC_CH_ADC2						0b00010
#define ADC_CH_ADC3						0b00011
#define ADC_CH_ADC4						0b00100
#define ADC_CH_ADC5						0b00101
#define ADC_CH_ADC6						0b00110
#define ADC_CH_ADC7						0b00111


#define ADC_PRESCALER_2					0b001	
#define ADC_PRESCALER_4					0b010	
#define ADC_PRESCALER_8					0b011	
#define ADC_PRESCALER_16				0b100	
#define ADC_PRESCALER_32				0b101	
#define ADC_PRESCALER_64				0b110	
#define ADC_PRESCALER_128               0b111	


#define ADC_AUTO_TRIGGER_ENABLE			1
#define ADC_AUTO_TRIGGER_DISABLE		0


#define ADC_TRIG_SRC_FREE_RUNNING		0b000
#define ADC_TRIG_SRC_ANALOD_COMP		0b001
#define ADC_TRIG_SRC_EXT_INT0			0b010
#define ADC_TRIG_SRC_TIMER0_COM_MATCH	0b011
#define ADC_TRIG_SRC_TIMER0_OVERFLOW	0b100
#define ADC_TRIG_SRC_TIMER_COM_MATCH_B	0b101
#define ADC_TRIG_SRC_TIMER1_OVERFLOW	0b110
#define ADC_TRIG_SRC_TIMER1_CAP_EVENT	0b111


#define ADC_POLLING_MODE				0
#define ADC_INTERRUPT_MODE				1


/** ADC channel 0 */
#define ADC_CH0					 0

/** ADC channel 1 */
#define ADC_CH1					 1

/** ADC channel 2 */
#define ADC_CH2					 2

/** ADC channel 3 */
#define ADC_CH3					 3

/** ADC channel 4 */
#define ADC_CH4					 4

/** ADC channel 5 */
#define ADC_CH5					 5

/** ADC channel 6 */
#define ADC_CH6					 6

/** ADC channel 7 */
#define ADC_CH7					 7


/* functions declaration */


/**
 * @brief Initialise ADC
 * @param void
 * @return void
 * */
void ADC_voidInit();


/**
 * @brief reading ADC converted value (used only in case polling mode)
 * @param Copy_u8ChNumber channel number
 * @return converted value
 * */
u16 ADC_u16Read(u8 Copy_u8ChNumber);


/**
 * @brief starting conversion from analog to digital
 * @param Copy_u8ChNumber channel number
 * @return void
 * */
void ADC_voidStartConversion(u8 Copy_u8ChNumber);

/**
 * @brief call back function which is called after conversion interrupt
 * @param ptr pointer to function
 * @return void
 * */
void ADC_voidSetCallBack(void (*ptr) (void));


/**
 * @brief getting converted value (called only in case interrupt mode)
 * @param void
 * @return converted value
 * */
u16 ADC_u16GetValue();

#endif /* ADC_INTERFACE_H_ */
