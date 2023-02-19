/**
 * \addtogroup APP
 * Main group application
 * @{
 * \file main.c
 * \brief main application
 * \author Mustafa M.Montaser
 * \version v2.4.0
 * \date 17-Feb-2023
 * */

/** @} */


/*Libraries and drivers includes */

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




/* Global Variables */

/// Temperature set point
u8 app_u8TempSetPoint = TEMP_INITIAL_SET_POINT;

/// Current temperature
u8 app_u8CurrentTemp = 0;

/// Array of the last 10 temperature readings
u8 app_u8TempAverage[10] = { 0 };

/// For average of the last 10 temperature readings
u16 app_u16TempAverageCalc = 0;

/// System state [running, stopped]
u8 app_u8SystemState = SYSTEM_STOPPED;

/// 7 segment current digit to display required value [ones, tens]
u8 app_u8SevenSegDigit = DSSD_DISPLAY_ONES;

/// setting mode on or off [enable, disable]
u8 app_u8SettingModeState = SETTING_MODE_DIS;

/// timer counter for temperature reading to be used with sensor
u8 app_u8TempTimerCounter = 0;

/// timer counter for setting mode
u16 app_u16SetModeTimerCounter = 0;




/* APP Functions Declarations */

/**
 * @brief Initialise the system and all peripherals
 * @param None
 * @return None
 * */
void App_SystemInit();


/**
 * @brief Increase temperate set point
 * @param None
 * @return None
 * */
void App_IncreaseTempSetPoint();


/**
 * @brief Decrease temperate set point
 * @param None
 * @return None
 * */
void App_DecreaseTempSetPoint();


/**
 * @brief Turn system ON or OFF
 * @param None
 * @return None
 * */
void App_SysOnOff();


/**
 * @brief Initialise system timer
 * @param local_u8Timer timer period in m seconds
 * @param ptr_callBack pointer to call back function which is called each timer period
 * @return None
 * */
void App_TimerInit(u8 local_u8Timer, void (*ptr_callBack) (void));


/**
 * @brief start system timer
 * @param None
 * @return None
 * */
void App_TimerBegin();


/**
 * @brief stop system timer
 * @param None
 * @return None
 * */
void App_TimerStop();


/**
 * @brief call back function to be called every timer period
 * @param None
 * @return None
 * */
void App_TimerCallBack();




/**
 * @brief main function
 * @param void
 * @return 0
 */
int main()
{
	/// System Initialise
	App_SystemInit();

	while(1) {}
	return 0;
}





/* Functions Definitions */

void App_SystemInit()
{
	/// Global Interrupt Init
	GIE_voidEnableGlobalINT();

	/// Push Buttons Init [UP, DOWN, On/OFF]
	PushBtn_voidInit(BTN_ON_OFF, PUSH_BTN_INTERRUPT_EN, App_SysOnOff);
	PushBtn_voidInit(BTN_UP_CTRL, PUSH_BTN_INTERRUPT_EN, App_IncreaseTempSetPoint);
	PushBtn_voidInit(BTN_DOWN_CTRL, PUSH_BTN_INTERRUPT_EN, App_DecreaseTempSetPoint);

	/// Timer Init with 10 msec timer period
	App_TimerInit(TIMER_PERIOD_MSEC, App_TimerCallBack);

	/// DSSD Init
	DSSD_voidInit();

	/// Sensor LM35 Init
	SensorLM35_voidInit();

	/// Fill the array of last 10 temperature readings with current reading at the beginning
	app_u8CurrentTemp = SensorLM35_u16ReadTemp(LM35_PIN);
	for(u8 i = 0; i < 10; i++)
	{
		app_u8TempAverage[i] = app_u8CurrentTemp;
	}

	/// Heater Init
	Heater_voidInit(HEATER_RELAY_PIN);

	/// LED Init
	LED_voidInit(LED_C_H);

	/// cooler Init
	Cooler_voidInit(COOLER_RELAY_PIN);

	/// EEPROM Init and getting temperature set point value
	EEPROM_voidInit();
	_delay_ms(1);

	/// Check if EEPROM is used for the first time or not. If yes, write into it the initial temperature set point
	EEPROM_u8ReadByte(0, 0, &app_u8TempSetPoint);
	_delay_ms(1);
	if(app_u8TempSetPoint == 255)
	{
		app_u8TempSetPoint = TEMP_INITIAL_SET_POINT;
		EEPROM_voidWriteByte(TEMP_INITIAL_SET_POINT, 0, 0);
		_delay_ms(1);
	}
}



void App_IncreaseTempSetPoint()
{
	/// make sure that set point is still lower than maximum allowable set point
	if((app_u8TempSetPoint < TEMP_MAX_SET_POINT) && (app_u8SettingModeState == SETTING_MODE_EN))
	{
		/// If OK then, Increase temperature set point by 5
		app_u8TempSetPoint += TEMP_ON_CHANGE_VALUE;

		/// Disable push buttons to make sure that value of set point is written into EEPROM and not interrupted
		PushBtn_voidDisable(BTN_ON_OFF);
		PushBtn_voidDisable(BTN_UP_CTRL);
		PushBtn_voidDisable(BTN_DOWN_CTRL);

		/// Writing into EEPROM the current set point value in page 0 in address 0
		EEPROM_voidWriteByte(app_u8TempSetPoint, 0, 0);

		/// Enable buttons again after writing into EEPROM
		PushBtn_voidEnable(BTN_ON_OFF);
		PushBtn_voidEnable(BTN_UP_CTRL);
		PushBtn_voidEnable(BTN_DOWN_CTRL);
	}

	/// Enabling setting mode and clear its timer
	app_u8SettingModeState = SETTING_MODE_EN;
	app_u16SetModeTimerCounter = 0;
}



void App_DecreaseTempSetPoint()
{
	/// make sure that set point is still greater than minimum allowable set point
	if((app_u8TempSetPoint > TEMP_MIN_SET_POINT) && (app_u8SettingModeState == SETTING_MODE_EN))
	{
		/// If OK then, Decrease temperature set point by 5
		app_u8TempSetPoint -= TEMP_ON_CHANGE_VALUE;

		/// Disable push buttons to make sure value of set point is written into EEPROM to be not interrupted
		PushBtn_voidDisable(BTN_ON_OFF);
		PushBtn_voidDisable(BTN_UP_CTRL);
		PushBtn_voidDisable(BTN_DOWN_CTRL);

		/// Writing into EEPROM the current set point value in page 0 in address 0
		EEPROM_voidWriteByte(app_u8TempSetPoint, 0, 0);

		/// Enable buttons again after writing into EEPROM
		PushBtn_voidEnable(BTN_ON_OFF);
		PushBtn_voidEnable(BTN_UP_CTRL);
		PushBtn_voidEnable(BTN_DOWN_CTRL);
	}

	/// Enabling setting mode and clear its timer
	app_u8SettingModeState = SETTING_MODE_EN;
	app_u16SetModeTimerCounter = 0;
}



void App_SysOnOff()
{
	/// If ON/OFF button is released and system is running then, stop system and disable all
	if(app_u8SystemState == SYSTEM_RUNNING)
	{
		/// Stop the system
		app_u8SystemState = SYSTEM_STOPPED;

		/// Disable setting mode
		app_u8SettingModeState = SETTING_MODE_DIS;

		/// clear timer counter for temperature and setting mode
		app_u16SetModeTimerCounter = 0;
		app_u8TempTimerCounter = 0;

		/// stop system timer
		App_TimerStop();

		/// disable 7segment display
		DSSD_voidDisableAll();

		/// turn off heater, cooler and LED
		Heater_voidTurnOff(HEATER_RELAY_PIN);
		Cooler_voidTurnOff(COOLER_RELAY_PIN);
		LED_voidTurnOff(LED_C_H);

		/// disable UP and DOWN buttons
		PushBtn_voidDisable(BTN_UP_CTRL);
		PushBtn_voidDisable(BTN_DOWN_CTRL);
	}

	/// If ON/OFF button is released and system is stopped then, run the system
	else
	{
		/// run the system
		app_u8SystemState = SYSTEM_RUNNING;

		/// start system timer
		App_TimerBegin();

		/// enable UP and DOWN buttons
		PushBtn_voidEnable(BTN_UP_CTRL);
		PushBtn_voidEnable(BTN_DOWN_CTRL);
	}
}




void App_TimerInit(u8 local_u8Timer, void (*ptr_callBack) (void))
{
	/// timer 0 Init
	Timer0_voidInit();

	/// setting timer period
	Timer0_voidSetTime(local_u8Timer);

	/// setting timer call back
	Timer0_voidSetCallBack(ptr_callBack);
}



void App_TimerBegin()
{
	/// start timer 0
	Timer0_voidStart();
}



void App_TimerStop()
{
	/// stop timer 0
	Timer0_voidStop();
}



void App_TimerCallBack()
{
	/// Temperature setting
	app_u8TempTimerCounter++;

	/// Get temperature value each 100 msec and assign it into array of the last 10 readings
	if(app_u8TempTimerCounter % 10 == 0)
	{
		app_u8CurrentTemp = SensorLM35_u16ReadTemp(LM35_PIN);
		app_u8TempAverage[(app_u8TempTimerCounter / 10) - 1] = app_u8CurrentTemp;

		/// Get the average of the last 10 readings
		for(u8 i = 0; i < 10; i++)
		{
			app_u16TempAverageCalc += app_u8TempAverage[i];
		}
		//app_u16TempAverageCalc /= 10;

		/// Check if the average is greater than temperature set point plus tolerance 5 degrees
		if(((f32)(app_u16TempAverageCalc / 10)) > ((f32)(app_u8TempSetPoint + TEMP_TOLERANCE)))
		{
			/// If greater, turn on the cooler, turn off the heater and turn on the LED
			Cooler_voidTurnOn(COOLER_RELAY_PIN);
			Heater_voidTurnOff(HEATER_RELAY_PIN);
			LED_voidTurnOn(LED_C_H);
		}

		/// Check if else the average is lower than temperature set point minus tolerance 5 degrees
		else if(((f32)(app_u16TempAverageCalc / 10)) < ((f32)(app_u8TempSetPoint - TEMP_TOLERANCE)))
		{
			/// If lower, turn of the cooler, turn on the heater and blink the LED each 1 sec
			Heater_voidTurnOn(HEATER_RELAY_PIN);
			Cooler_voidTurnOff(COOLER_RELAY_PIN);
			if(app_u8TempTimerCounter >= 100) LED_voidToggle(LED_C_H);
		}

		/// otherwise, turn off cooler, heater and LED
		else
		{
			Heater_voidTurnOff(HEATER_RELAY_PIN);
			Cooler_voidTurnOff(COOLER_RELAY_PIN);
			LED_voidTurnOff(LED_C_H);
		}

		/// clear the temperature average buffer
		app_u16TempAverageCalc = 0;
	}

	/// clear temperature timer counter each 10 cycles
	if(app_u8TempTimerCounter >= 100)
	{
		app_u8TempTimerCounter = 0;
	}

	/// 7 segment display setting
	/// In case setting mode is ON
	if(app_u8SettingModeState == SETTING_MODE_EN)
	{
		app_u16SetModeTimerCounter++;
		/// check DSSD state each 1 sec to be blinked
		if(app_u16SetModeTimerCounter % 100 == 0)
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

		/// in case DSSD in ON, display current set point
		if(DSSD_u8Status() == DSSD_ON)
		{
			DSSD_voidDisplay(app_u8TempSetPoint, app_u8SevenSegDigit);
		}

		/// If Up or DOWN buttons not pressed for 5 sec
		if(app_u16SetModeTimerCounter >= 500)
		{
			/// then, disable setting mode
			app_u8SettingModeState = SETTING_MODE_DIS;

			/// clear setting mode timer counter
			app_u16SetModeTimerCounter = 0;

			/// write set point value into EEPROM
			EEPROM_voidWriteByte(app_u8TempSetPoint, 0, 0);
		}
	}

	/// In case setting mode is OFF
	else if(app_u8SettingModeState == SETTING_MODE_DIS)
	{
		/// Display current temperature value
		DSSD_voidDisplay(app_u8CurrentTemp, app_u8SevenSegDigit);
	}

	/// Change the desired digit of the 7seg for the next timer period
	app_u8SevenSegDigit = app_u8SevenSegDigit == DSSD_DISPLAY_ONES ? DSSD_DISPLAY_TENS : DSSD_DISPLAY_ONES;
}



