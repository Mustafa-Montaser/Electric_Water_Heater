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
 * \file ADC_Program.c
 * \brief this file contains contains implementation for the ADC module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


/* header files includes */

#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"

#include <avr/interrupt.h>

#include "ADC_Config.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"



/* functions definitions */


void ADC_voidInit() {
	/* VREF setting */
	WRT_2BITS(ADC_ADMUX, ADC_ADMUX_REFS0, ADC_VOLT_REF);
	
	/* ADC Right Adjust  */
	CLR_BIT(ADC_ADMUX, ADC_ADMUX_ADLAR);
	
	/* ADC Prescaler */ 
	WRT_3BITS(ADC_ADCSRA, ADC_ADCSRA_ADPS0, ADC_PRESCALER);
	
	/* ADC Auto Trigger State */
	WRT_BIT(ADC_ADCSRA, ADC_ADCSRA_ADATE, ADC_AUTO_TRIGGER_STATE);
	
	/* ADC Interrupt Enable/Disable */
	#if ADC_MODE == ADC_INTERRUPT_MODE
		SET_BIT(ADC_ADCSRA, ADC_ADCSRA_ADIE);
	#elif ADC_MODE == ADC_POLLING_MODE
		CLR_BIT(ADC_ADCSRA, ADC_ADCSRA_ADIE);
	#endif
	
	/* ADC Auto Trigger Source */
	WRT_3BITS(ADC_SFIOR, ADC_SFIOR_ADTS0, ADC_TRIG_SRC);
	
	/* ADC Enable */
	SET_BIT(ADC_ADCSRA, ADC_ADCSRA_ADEN);
}




#if ADC_MODE == ADC_POLLING_MODE
u16 ADC_u16Read(u8 Copy_u8ChNumber) {
	/* select channel */
	switch(Copy_u8ChNumber) {
		case ADC_CH0: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC0); break;
		case ADC_CH1: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC1); break;
		case ADC_CH2: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC2); break;
		case ADC_CH3: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC3); break;
		case ADC_CH4: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC4); break;
		case ADC_CH5: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC5); break;
		case ADC_CH6: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC6); break;
		case ADC_CH7: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC7); break;
		default: break;
	}

	/* ADC Start Conversion */
	SET_BIT(ADC_ADCSRA, ADC_ADCSRA_ADSC);

	/* polling till finish conversion */
	while(GET_BIT(ADC_ADCSRA, ADC_ADCSRA_ADIF) == 0);

	/* return ADC value in mVolt */
	u16 Local_u16AnalogRead = (u16)(((u32)ADC_VALUE * (u32)ADC_VOLT_REF_VALUE * (u32)1000) / (u32)1024);
	return Local_u16AnalogRead;
}



#elif ADC_MODE == ADC_INTERRUPT_MODE 

void ADC_voidStartConversion(u8 Copy_u8ChNumber) {
	/* select channel */
	switch(Copy_u8ChNumber) {
		case ADC_CH0: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC0); break;
		case ADC_CH1: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC1); break;
		case ADC_CH2: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC2); break;
		case ADC_CH3: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC3); break;
		case ADC_CH4: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC4); break;
		case ADC_CH5: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC5); break;
		case ADC_CH6: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC6); break;
		case ADC_CH7: WRT_5BITS(ADC_ADMUX, ADC_ADMUX_MUX0, ADC_CH_ADC7); break;
		default: break;
	}

	/* ADC Start Conversion */
	SET_BIT(ADC_ADCSRA, ADC_ADCSRA_ADSC);
}


/* Pointer to callback function */
void (*AdcCallBack) (void) = NULL;

/* ADC Interrupt callback function */
void ADC_voidSetCallBack(void (*ptr) (void)) { AdcCallBack = ptr; }
ISR(ADC_vect) { AdcCallBack(); }

//void  __vector_16 (void) __attribute__((signal));
//void __vector_16(void) { AdcCallBack(); }


u16 ADC_u16GetValue() {
	u16 Local_u16AnalogRead = (u16)(((u32)ADC_VALUE * (u32)ADC_VOLT_REF_VALUE * (u32)1000) / (u32)1024);
	return Local_u16AnalogRead;
}

#endif

