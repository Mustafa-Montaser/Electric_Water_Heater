/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup DSSD
 * Decoded seven segment display module driver
 * @{
 * \file DSSD_Program.c
 * \brief this file contains contains implementation for the cooler module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */



/* Header files includes */

#include "../../LIB/StdTypes.h"
#include "../../LIB/BitMath.h"

#include "../../MCAL/DIO/DIO_Private.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#include "DSSD_Config.h"
#include "DSSD_Interface.h"



/* private functions declaration */

/**
 * @brief display right digit
 * @param local_u8Num number of 2 digits
 * @return None
 * */
static void DSSD_voidDisplayOnes(u8 local_u8Num);


/**
 * @brief display left digit
 * @param local_u8Num number of 2 digits
 * @return None
 * */
static void DSSD_voidDisplayTens(u8 local_u8Num);


/**
 * @brief display number 0
 * @param None
 * @return None
 * */
static void display_0();


/**
 * @brief display number 1
 * @param None
 * @return None
 * */
static void display_1();


/**
 * @brief display number 2
 * @param None
 * @return None
 * */
static void display_2();


/**
 * @brief display number 3
 * @param None
 * @return None
 * */
static void display_3();


/**
 * @brief display number 4
 * @param None
 * @return None
 * */
static void display_4();


/**
 * @brief display number 5
 * @param None
 * @return None
 * */
static void display_5();


/**
 * @brief display number 6
 * @param None
 * @return None
 * */
static void display_6();


/**
 * @brief display number 7
 * @param None
 * @return None
 * */
static void display_7();


/**
 * @brief display number 8
 * @param None
 * @return None
 * */
static void display_8();


/**
 * @brief display number 9
 * @param None
 * @return None
 * */
static void display_9();


/**
 * @brief display the selected number
 * @param local_u8Num number of 1 digit
 * @return None
 * */
static void displaySelected(u8 local_u8Num);


/* functions definition */

void DSSD_voidInit() {

	/// drive data and control pins as a outputs
	DIO_voidSetPinMode(DSSD_EN1, DIO_PIN_OUTPUT);
	DIO_voidSetPinMode(DSSD_EN2, DIO_PIN_OUTPUT);
	DIO_voidSetPinMode(DSSD_DIP, DIO_PIN_OUTPUT);
	
	DIO_voidSetPinMode(DSSD_A, DIO_PIN_OUTPUT);
	DIO_voidSetPinMode(DSSD_B, DIO_PIN_OUTPUT);
	DIO_voidSetPinMode(DSSD_C, DIO_PIN_OUTPUT);
	DIO_voidSetPinMode(DSSD_D, DIO_PIN_OUTPUT);
	
	#if DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidSetPinMode(DSSD_E, DIO_PIN_OUTPUT);
		DIO_voidSetPinMode(DSSD_F, DIO_PIN_OUTPUT);
		DIO_voidSetPinMode(DSSD_G, DIO_PIN_OUTPUT);
	#endif

}

void DSSD_voidEN1() {

	/// enable EN1
	DIO_voidSetPinValue(DSSD_EN1);

	/// disable EN2
	DIO_voidClearPinValue(DSSD_EN2);
}

void DSSD_voidEN2() {

	/// enable EN2
	DIO_voidSetPinValue(DSSD_EN2);

	/// disable EN1
	DIO_voidClearPinValue(DSSD_EN1);
}


void DSSD_voidDisableAll()
{
	/// disable EN1 and EN2
	DIO_voidSetPinValue(DSSD_EN1);
	DIO_voidSetPinValue(DSSD_EN2);
}

void DSSD_voidDisplayOnes(u8 local_u8Num)
{
	/// enable EN1 then get and display the right digit from the number
	DSSD_voidEN1();
	displaySelected(local_u8Num - (local_u8Num / 10) * 10);
}

void DSSD_voidDisplayTens(u8 local_u8Num)
{
	/// enable EN2 then get and display the left digit from the number
	DSSD_voidEN2();
	displaySelected(local_u8Num / 10);
}

void DSSD_voidDisplay(u8 local_u8Num, u8 u8Digit)
{
	/// according to desired digit, display it
	switch(u8Digit)
	{
		case DSSD_DISPLAY_ONES: DSSD_voidDisplayOnes(local_u8Num); break;
		case DSSD_DISPLAY_TENS: DSSD_voidDisplayTens(local_u8Num); break;
	}
}

//////////////////////////////////////////////////////////////////////

u8 DSSD_u8Status()
{
	/// if EN1 and EN2 are low then, DSSD is OFF. Otherwise, it is ON
	u8 local_u8state = 0;
	if(GET_BIT(DSSD_CTRL_REG, DSSD_EN1 % 10) && GET_BIT(DSSD_CTRL_REG, DSSD_EN2 % 10))
	{
		local_u8state = DSSD_OFF;
	}
	else
	{
		local_u8state = DSSD_ON;
	}
	return local_u8state;
}

//////////////////////////////////////////////////////////////////////

static void display_0() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_LOW);
	#endif
}

static void display_1() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_LOW);
	#endif
}

static void display_2() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_HIGH);
	#endif
}

static void display_3() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_HIGH);
	#endif
}

static void display_4() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_HIGH);
	#endif
}

static void display_5() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_HIGH);
	#endif
}

static void display_6() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_HIGH);
	#endif
}

static void display_7() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_LOW);
	#endif
}

static void display_8() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_HIGH);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_HIGH);
	#endif
}

static void display_9() {
	#if DSSD_MODE == DSSD_BCD_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_HIGH);
	#elif DSSD_MODE == DSSD_NORMAL_MODE
		DIO_voidWritePinValue(DSSD_A, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_B, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_C, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_D, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_E, DIO_PIN_LOW);
		DIO_voidWritePinValue(DSSD_F, DIO_PIN_HIGH);
		DIO_voidWritePinValue(DSSD_G, DIO_PIN_HIGH);
	#endif
}

static void displaySelected(u8 local_u8Num) {
	switch(local_u8Num) {
		case 0: 	display_0(); 	break;
		case 1: 	display_1(); 	break;
		case 2: 	display_2(); 	break;
		case 3: 	display_3(); 	break;
		case 4: 	display_4(); 	break;
		case 5: 	display_5(); 	break;
		case 6: 	display_6(); 	break;
		case 7: 	display_7();	break;
		case 8:	 	display_8(); 	break;
		case 9: 	display_9(); 	break;
		default: 	display_0();	break;
	}
}










