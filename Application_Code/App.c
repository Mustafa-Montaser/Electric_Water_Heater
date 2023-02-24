/**
 * \addtogroup APP
 * Main group application
 * @{
 * \file App.c
 * \brief functions implementation for application
 * \author Mustafa M.Montaser
 * \version v2.4.0
 * \date 23-Feb-2023
 * */

/** @} */

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*
 * Header files includes
 */

#include "Drivers/LIB/StdTypes.h"
#include "Drivers/LIB/BitMath.h"

#include "Drivers/MCAL/DIO/DIO_Interface.h"
#include "Drivers/MCAL/GIE/GIE_Interface.h"
#include "Drivers/MCAL/Timer0/Timer0_Interface.h"

#include "Drivers/HAl/Cooler/Cooler_Interface.h"
#include "Drivers/HAL/DSSD/DSSD_Interface.h"
#include "Drivers/HAL/EEPROM/EEPROM_Interface.h"
#include "Drivers/HAL/Heater/Heater.h"
#include "Drivers/HAL/LED/LED_Interface.h"
#include "Drivers/HAL/PushButton/PushBtn_Interface.h"
#include "Drivers/HAL/SensorLM35/SensorLM35_Interface.h"

/// CPU Frequency
#define F_CPU 16000000UL
#include <util/delay.h>

#include "Macros.h"
#include "App.h"


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*
 * Private Variables
 */

/// Temperature set point
static u8 App_u8TempSetPoint = TEMP_INITIAL_SET_POINT;

/// Current temperature
static u8 App_u8CurrentTemp = 0;

/// Array of the last 10 temperature readings
static u8 App_u8TempAverage[10] = { 0 };

/// For average of the last 10 temperature readings
static u16 App_u16TempAverageCalc = 0;

/// System state [running, stopped]
static u8 App_u8SystemState = SYSTEM_STOPPED;

/// 7 segment current digit to display required value [ones, tens]
static u8 App_u8SevenSegDigit = DSSD_DISPLAY_ONES;

/// setting mode on or off [enable, disable]
static u8 App_u8SettingModeState = SETTING_MODE_DIS;

/// timer counter for temperature reading to be used with sensor
static u8 App_u8TempTimerCounter = 0;

/// timer counter for setting mode
static u16 App_u16SetModeTimerCounter = 0;

/// pointer to On/OFF button call back function
static void (*App_ptrOnOffBtnHandler) (void);

/// pointer to UP button call back function
static void (*App_ptrUpBtnHandler) (void);

/// pointer to DOWN button call back function
static void (*App_ptrDownBtnHandler) (void);

/// pointer to timer call back function
static void (*App_ptrTimerHandler) (void);


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*
 * Private functions prototype
 */

/*=====================================================================================================================================*/

/**
 * @brief Default ON/OFF button handler
 * @note Used in case user don't set handler for On/OFF button
 * @param void
 * @return void
 * */
static void App_DefaultOnOffBtnHandler(void);

/*=====================================================================================================================================*/

/**
 * @brief Default UP button handler
 * @note Used in case user don't set handler for UP button
 * @param void
 * @return void
 * */
static void App_DefaultUpBtnHandler(void);

/*=====================================================================================================================================*/

/**
 * @brief Default DOWN button handler
 * @note Used in case user don't set handler for DOWN button
 * @param void
 * @return void
 * */
static void App_DefaultDownBtnHandler(void);

/*=====================================================================================================================================*/

/**
 * @brief Default timer handler
 * @note Used in case user don't set handler for timer
 * @param void
 * @return void
 * */
static void App_DefaultTimerHandler(void);

/*=====================================================================================================================================*/

/**
 * @brief Initialise the system timer
 * @note System timer period value is can be configured in macros file
 * @param void
 * @return void
 * */
static void App_TimerInit(void);

/*=====================================================================================================================================*/

/**
 * @brief Start the system timer
 * @param void
 * @return void
 * */
static void App_TimerBegin(void);

/*=====================================================================================================================================*/

/**
 * @brief Stop the system timer
 * @param void
 * @return void
 * */
static void App_TimerStop(void);

/*=====================================================================================================================================*/


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*
 * Private functions implementation
 */

/*=====================================================================================================================================*/

/**
 * @details
 *
 * 	Check if the system is running or not.
 * 	If system is running, then
 * 		- stop the system
 * 		- disable setting mode
 * 		- clear all timer counters
 * 		- stop system timer
 * 		- turn off DSSD, cooler, heater and heater LED
 * 		- disable Up and DOWN buttons
 * 	If system is stopped, then
 *		- run the system
 * 		- start system timer
 * 		- enable Up and DOWN buttons
 *
 * */
static void App_DefaultOnOffBtnHandler(void)
{
	if(App_u8SystemState == SYSTEM_RUNNING)
	{
		App_u8SystemState = SYSTEM_STOPPED;
		App_u8SettingModeState = SETTING_MODE_DIS;
		App_u16SetModeTimerCounter = 0;
		App_u8TempTimerCounter = 0;
		App_TimerStop();
		DSSD_voidDisableAll();
		Heater_voidTurnOff(HEATER_RELAY_PIN);
		Cooler_voidTurnOff(COOLER_RELAY_PIN);
		LED_voidTurnOff(LED_C_H);
		PushBtn_voidDisable(BTN_UP_CTRL);
		PushBtn_voidDisable(BTN_DOWN_CTRL);
	}
	else
	{
		App_u8SystemState = SYSTEM_RUNNING;
		App_TimerBegin();
		PushBtn_voidEnable(BTN_UP_CTRL);
		PushBtn_voidEnable(BTN_DOWN_CTRL);
	}
}

/*=====================================================================================================================================*/


/**
 * @details
 *
 * 	- First check if temperature set point is still lower that the configured maximum temperature set point value
 * 	  and it is the first press in the setting mode.
 * 	- If it lower, increment the temperature set point value by 5 degrees and write it into the EEPROM. If not, do nothing.
 * 	- In addition that, enable setting mode and reset setting mode counter.
 *
 * */
static void App_DefaultUpBtnHandler(void)
{
	if((App_u8TempSetPoint < TEMP_MAX_SET_POINT) && (App_u8SettingModeState == SETTING_MODE_EN))
	{
		App_u8TempSetPoint += TEMP_ON_CHANGE_VALUE;
		EEPROM_voidWriteByte(App_u8TempSetPoint, 0, 0);
	}
	App_u8SettingModeState = SETTING_MODE_EN;
	App_u16SetModeTimerCounter = 0;
}

/*=====================================================================================================================================*/

/**
 * @details
 *
 * 	- First check if temperature set point is still higher that the configured minimum temperature set point value
 * 	  and it is the first press in the setting mode.
 * 	- If it higher, decrement the temperature set point value by 5 degrees and write it into the EEPROM. If not, do nothing.
 * 	- In addition that, enable setting mode and reset setting mode counter.
 *
 * */
/*=====================================================================================================================================*/

static void App_DefaultDownBtnHandler(void)
{
	if((App_u8TempSetPoint > TEMP_MIN_SET_POINT) && (App_u8SettingModeState == SETTING_MODE_EN))
	{
		App_u8TempSetPoint -= TEMP_ON_CHANGE_VALUE;
		EEPROM_voidWriteByte(App_u8TempSetPoint, 0, 0);
	}
	App_u8SettingModeState = SETTING_MODE_EN;
	App_u16SetModeTimerCounter = 0;
}

/*=====================================================================================================================================*/

/**
 * @details
 *
 * 	This function is responsible for system operation.
 *
 * 	{ LM35 Temperature sensor }
 * 		- increment temperature timer counter.
 * 		- depend on temperature timer counter, measure temperature every 100 msec and assign it into array of 10 elements.
 * 		- then, calculate the average of the last 10 readings according to the array.
 * 		- if the average value is greater than temperature set point plus tolerance, turn on the cooler and the LED.
 * 		- if the average value is lower than temperature set point minus tolerance, turn on the heater and blink the LED.
 * 		- otherwise, turn off the cooler, heater and LED.
 * 		- then clear the average value buffer to calculate the new one.
 * 		- reset timer counter after every 10 cycles.
 *
 * 	{ Seven Segments Display }
 * 		- check if system in normal mode or in setting mode.
 * 		- if in setting mode, increment setting mode counter, blink SSD every 1 sec and display current temperature set point.
 * 		- if Up or DOWN button not pressed for 5 sec., disable setting mode and write the last modified set point into the EEPROM and display current temperature.
 * 		- if setting mode is disabled, display current temperature.
 * 		- in every cycle, switch between seven segment digits to display ones or tens of the selected number
 *
 *
 * */

static void App_DefaultTimerHandler(void)
{
	App_u8TempTimerCounter++;
	if(App_u8TempTimerCounter % 10 == 0)
	{
		App_u8CurrentTemp = SensorLM35_u16ReadTemp(LM35_PIN);
		App_u8TempAverage[(App_u8TempTimerCounter / 10) - 1] = App_u8CurrentTemp;
		for(u8 i = 0; i < 10; i++)
		{
			App_u16TempAverageCalc += App_u8TempAverage[i];
		}
		if(((f32)(App_u16TempAverageCalc / 10)) > ((f32)(App_u8TempSetPoint + TEMP_TOLERANCE)))
		{
			Cooler_voidTurnOn(COOLER_RELAY_PIN);
			Heater_voidTurnOff(HEATER_RELAY_PIN);
			LED_voidTurnOn(LED_C_H);
		}
		else if(((f32)(App_u16TempAverageCalc / 10)) < ((f32)(App_u8TempSetPoint - TEMP_TOLERANCE)))
		{
			Heater_voidTurnOn(HEATER_RELAY_PIN);
			Cooler_voidTurnOff(COOLER_RELAY_PIN);
			if(App_u8TempTimerCounter >= 100) LED_voidToggle(LED_C_H);
		}
		else
		{
			Heater_voidTurnOff(HEATER_RELAY_PIN);
			Cooler_voidTurnOff(COOLER_RELAY_PIN);
			LED_voidTurnOff(LED_C_H);
		}
		App_u16TempAverageCalc = 0;
	}
	if(App_u8TempTimerCounter >= 100)
	{
		App_u8TempTimerCounter = 0;
	}

	if(App_u8SettingModeState == SETTING_MODE_EN)
	{
		App_u16SetModeTimerCounter++;
		if(App_u16SetModeTimerCounter % 100 == 0)
		{
			if(DSSD_u8Status() == DSSD_ON)
			{
				DSSD_voidDisableAll();
			}

			else if(DSSD_u8Status() == DSSD_OFF)
			{
				DSSD_voidEN1();
			}
		}
		if(DSSD_u8Status() == DSSD_ON)
		{
			DSSD_voidDisplay(App_u8TempSetPoint, App_u8SevenSegDigit);
		}
		if(App_u16SetModeTimerCounter >= 500)
		{
			App_u8SettingModeState = SETTING_MODE_DIS;
			App_u16SetModeTimerCounter = 0;
			EEPROM_voidWriteByte(App_u8TempSetPoint, 0, 0);
		}
	}
	else if(App_u8SettingModeState == SETTING_MODE_DIS)
	{
		DSSD_voidDisplay(App_u8CurrentTemp, App_u8SevenSegDigit);
	}
	App_u8SevenSegDigit = App_u8SevenSegDigit == DSSD_DISPLAY_ONES ? DSSD_DISPLAY_TENS : DSSD_DISPLAY_ONES;
}

/*=====================================================================================================================================*/


/**
 * @details
 *
 * 	this function is responsible for
 * 		- initialise the timer [Timer 0]
 * 		- set the timer period
 * 		- set call back handler for the timer
 *
 * */
static void App_TimerInit(void)
{
	Timer0_voidInit();
	Timer0_voidSetTime(TIMER_PERIOD_MSEC);
	Timer0_voidSetCallBack(App_ptrTimerHandler);
}

/*=====================================================================================================================================*/


static void App_TimerBegin(void)
{
	Timer0_voidStart();
}

/*=====================================================================================================================================*/

/*=====================================================================================================================================*/

static void App_TimerStop(void)
{
	Timer0_voidStop();
}

/*=====================================================================================================================================*/


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*
 * Global functions implementation
 */

/*=====================================================================================================================================*/

/**
 * @details
 *
 * 	- enable GIE [global interrupt enable]
 * 	- set the buttons and timer handlers depend on user handler or default handlers
 * 	- initialise buttons [UP, DOWN, ON/OFF], timer, DSSD, LM35 sensor, heater, cooler, LED, EEPROM
 * 	- fill an array of 10 elements with the current temperature
 * 	- getting the the the temperature set point value which saved on EEPROM.
 * 	  if EEPROM is used for first time, write into it the initial set point which configured in the macros file.
 *
 * */
void App_SystemInit(void)
{
	GIE_voidEnableGlobalINT();

	if(App_ptrOnOffBtnHandler == NULL) 	App_ptrOnOffBtnHandler 	= App_DefaultOnOffBtnHandler;
	if(App_ptrUpBtnHandler == NULL) 	App_ptrUpBtnHandler 	= App_DefaultUpBtnHandler;
	if(App_ptrDownBtnHandler == NULL) 	App_ptrDownBtnHandler 	= App_DefaultDownBtnHandler;
	if(App_ptrTimerHandler == NULL) 	App_ptrTimerHandler 	= App_DefaultTimerHandler;

	PushBtn_voidInit(BTN_ON_OFF, PUSH_BTN_INTERRUPT_EN, App_ptrOnOffBtnHandler);
	PushBtn_voidInit(BTN_UP_CTRL, PUSH_BTN_INTERRUPT_EN, App_ptrUpBtnHandler);
	PushBtn_voidInit(BTN_DOWN_CTRL, PUSH_BTN_INTERRUPT_EN, App_ptrDownBtnHandler);

	App_TimerInit();
	DSSD_voidInit();
	SensorLM35_voidInit();

	App_u8CurrentTemp = SensorLM35_u16ReadTemp(LM35_PIN);
	for(u8 i = 0; i < 10; i++)
	{
		App_u8TempAverage[i] = App_u8CurrentTemp;
	}

	Heater_voidInit(HEATER_RELAY_PIN);
	LED_voidInit(LED_C_H);
	Cooler_voidInit(COOLER_RELAY_PIN);
	EEPROM_voidInit();
	_delay_ms(1);

	EEPROM_u8ReadByte(0, 0, &App_u8TempSetPoint);
	_delay_ms(1);
	if(App_u8TempSetPoint == 255)
	{
		App_u8TempSetPoint = TEMP_INITIAL_SET_POINT;
		EEPROM_voidWriteByte(TEMP_INITIAL_SET_POINT, 0, 0);
		_delay_ms(1);
	}
}

/*=====================================================================================================================================*/

void App_SetOnOffBtnHandler(void (*onOffBtnCallBack) (void))
{
	if(onOffBtnCallBack != NULL) App_ptrOnOffBtnHandler = onOffBtnCallBack;
}

/*=====================================================================================================================================*/

void App_SetUpBtnHandler(void (*upBtnCallBack) (void))
{
	if(upBtnCallBack != NULL) App_ptrUpBtnHandler = upBtnCallBack;
}

/*=====================================================================================================================================*/

void App_SetDownBtnHandler(void (*downBtnCallBack) (void))
{
	if(downBtnCallBack != NULL) App_ptrDownBtnHandler = downBtnCallBack;
}

/*=====================================================================================================================================*/

void App_SetTimerHandler(void (*timerCallBack) (void))
{
	if(timerCallBack != NULL) App_ptrTimerHandler = timerCallBack;
}

/*=====================================================================================================================================*/


