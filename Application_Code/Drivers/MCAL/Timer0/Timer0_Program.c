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
 * \file Timer0_Program.c
 * \brief this file contains contains implementation for the Timer0 module
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

#include "../DIO/DIO_Interface.h"

#include <avr/interrupt.h>

#include "Timer0_Config.h"
#include "Timer0_Interface.h"
#include "Timer0_Private.h"



/* global variables */

u32 Timer0_u32NumOfOverflows	= 0;
u8	Timer0_u8NumOfReminderTicks = 0;
u32 Timer0_u32IntCounter		= 0;
u32 Timer0_u8NumOfCompMatch		= 0;



#if ((TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_NORMAL_MODE) || (TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_CTC_MODE))

	void Timer0_voidInit() {
		/* waveform generation setting */
		#if TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_NORMAL_MODE
			CLR_BIT(TIMER0_TCCR0, TIMER0_TCCR0_WGM00);
			CLR_BIT(TIMER0_TCCR0, TIMER0_TCCR0_WGM01);
		#elif TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_CTC_MODE
			CLR_BIT(TIMER0_TCCR0, TIMER0_TCCR0_WGM00);
			SET_BIT(TIMER0_TCCR0, TIMER0_TCCR0_WGM01);
		#endif
	
		/* Enable  Timer0 Interrupt */
		#if TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_NORMAL_MODE
			SET_BIT(TIMER0_TIMSK, TIMER0_TIMSK_TOIE0);
		#elif TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_CTC_MODE
			SET_BIT(TIMER0_TIMSK, TIMER0_TIMSK_OCIE0);
		#endif
	}



	void Timer0_voidSetTime(u32 copy_u8Time) {
		/* Calc. Tick Time = (1 * prescaler) / F_OSC */
		u32 local_u32TickTime = 0;
		#if TIMER0_PRESCALER == TIMER0_NO_PRESCALER
			local_u32TickTime = 1 / TIMER0_F_OSC;
		#elif TIMER0_PRESCALER == TIMER0_PRESCALER_8	
			local_u32TickTime = 8 / TIMER0_F_OSC;
		#elif TIMER0_PRESCALER == TIMER0_PRESCALER_64
			local_u32TickTime = 64 / TIMER0_F_OSC;
		#elif TIMER0_PRESCALER == TIMER0_PRESCALER_256
			local_u32TickTime = 256 / TIMER0_F_OSC;
		#elif TIMER0_PRESCALER == TIMER0_PRESCALER_1024
			local_u32TickTime = 1024 / TIMER0_F_OSC;
		#endif
	
		#if TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_NORMAL_MODE
			u32 local_u32TotalNumOfTicks = (copy_u8Time * 1000) / local_u32TickTime;
			Timer0_u32NumOfOverflows = local_u32TotalNumOfTicks / 256;
			Timer0_u8NumOfReminderTicks = local_u32TotalNumOfTicks % 256;
			if(Timer0_u8NumOfReminderTicks != 0) {
				TIMER0_TCNT0 = 256 - Timer0_u8NumOfReminderTicks;
				Timer0_u32NumOfOverflows++;
			}
	
		#elif TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_CTC_MODE
			u32 local_u32TotalNumOfTicks = (copy_u8Time * 1000) / local_u32TickTime;
			u8 local_u8DivisionFactor = 255;
			while(local_u32TotalNumOfTicks % local_u8DivisionFactor) {
				local_u8DivisionFactor --;
			}
			Timer0_u8NumOfCompMatch = local_u32TotalNumOfTicks / local_u8DivisionFactor;
			TIMER0_OCR0 = local_u8DivisionFactor - 1;
		#endif
	}

#endif /* Normal and CTC mode */



void Timer0_voidStart() {
	WRT_3BITS(TIMER0_TCCR0, TIMER0_TCCR0_CS00, TIMER0_PRESCALER);
}



void Timer0_voidStop() {
	WRT_3BITS(TIMER0_TCCR0, TIMER0_TCCR0_CS00, TIMER0_STOP_PRESCALER);
}



void (*Timer0CallBack) (void) = NULL;

void Timer0_voidSetCallBack(void (*ptr) (void)) { Timer0CallBack = ptr; }


#if TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_NORMAL_MODE
	
ISR(TIMER0_OVF_vect) {
	Timer0_u32IntCounter++;
	if(Timer0_u32IntCounter == Timer0_u32NumOfOverflows) {
		Timer0CallBack();
		Timer0_u32IntCounter = 0;
		TIMER0_TCNT0 = 256 - Timer0_u8NumOfReminderTicks;
	}
}

//void  __vector_11 (void) __attribute__((signal));
//void __vector_11(void) { Timer0CallBack(); }


#elif TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_CTC_MODE

	ISR(TIMER0_COMP_vect) {
		Timer0_u32IntCounter++;
		if(Timer0_u32IntCounter == Timer0_u8NumOfCompMatch) {
			Timer0CallBack();
			Timer0_u32IntCounter = 0;
		}
	}

#endif



#if ((TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_FAST_PWM_MODE) || (TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_PHASE_CORRECT_MODE))

void Timer0_voidPwmInit() {

	DIO_voidSetPinMode(TIMER0_FAST_PWM_PIN, DIO_PIN_OUTPUT);

	#if TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_FAST_PWM_MODE
		SET_BIT(TIMER0_TCCR0, TIMER0_TCCR0_WGM00);
		SET_BIT(TIMER0_TCCR0, TIMER0_TCCR0_WGM01);
	#elif TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_PHASE_CORRECT_MODE
		SET_BIT(TIMER0_TCCR0, TIMER0_TCCR0_WGM00);
		CLR_BIT(TIMER0_TCCR0, TIMER0_TCCR0_WGM01);
	#endif

	#if TIMER0_FAST_PWM_MODE == TIMER0_FAST_PWM_NON_INVERTING_MODE
		CLR_BIT(TIMER0_TCCR0, TIMER0_TCCR0_COM00);
		SET_BIT(TIMER0_TCCR0, TIMER0_TCCR0_COM01);
	#elif TIMER0_FAST_PWM_MODE == TIMER0_FAST_PWM_INVERTING_MODE
		SET_BIT(TIMER0_TCCR0, TIMER0_TCCR0_COM00);
		SET_BIT(TIMER0_TCCR0, TIMER0_TCCR0_COM01);
	#endif
}


void Timer0_voidSetPwmDutyCycle(u8 local_u8DuctyCycle) {
	#if TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_FAST_PWM_MODE
		u8 local_u8OCR0 = 0;
		#if TIMER0_FAST_PWM_MODE == TIMER0_FAST_PWM_NON_INVERTING_MODE
			if(local_u8DuctyCycle == 0) local_u8DuctyCycle = 1;
			local_u8OCR0 = ((local_u8DuctyCycle * 256) / 100) - 1;
		#elif TIMER0_FAST_PWM_MODE == TIMER0_FAST_PWM_INVERTING_MODE
			if(local_u8DuctyCycle == 100) local_u8DuctyCycle = 99;
			local_u8OCR0 = 255 - ((local_u8DuctyCycle * 256) / 100);
		#endif
		TIMER0_OCR0 = local_u8OCR0;
		
	#elif TIMER0_WAVEFORM_MODE == TIMER0_WAVEFORM_PHASE_CORRECT_MODE
		#if TIMER0_FAST_PWM_MODE == TIMER0_FAST_PWM_NON_INVERTING_MODE
			TIMER0_OCR0 = (local_u8DuctyCycle * 255) / 100;
		#elif TIMER0_FAST_PWM_MODE == TIMER0_FAST_PWM_INVERTING_MODE
			TIMER0_OCR0 = 255 - ((local_u8DuctyCycle * 255) / 100);
		#endif /* calc OCR0 */

	#endif /* PWM Mode select */

	

}


void Timer0_voidStartPwm() {
	Timer0_voidStart();
}


void Timer0_voidStopPwm() {
	Timer0_voidStop();
}


#endif /* Fast PWM and Phase Correct Mode */
