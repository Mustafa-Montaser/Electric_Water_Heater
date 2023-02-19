/**
 * \addtogroup APP
 * Main group application
 * @{
 * \file Macros.h
 * \brief Macros for main application
 * \author Mustafa M.Montaser
 * \version v2.4.0
 * \date 17-Feb-2023
 * */

/** @} */

#ifndef MACROS_H_
#define MACROS_H_


/// ON/OFF system button pin
#define BTN_ON_OFF			DIO_PB2

/// set point increasing button pin
#define BTN_UP_CTRL			DIO_PD2

/// set point decreasing button pin
#define BTN_DOWN_CTRL		DIO_PD3

/// LED pin
#define LED_C_H				DIO_PC4

/// Relay pin of the heater
#define HEATER_RELAY_PIN	DIO_PC3

/// Relay pin of the cooler
#define COOLER_RELAY_PIN	DIO_PC5

/// Sensor LM35 pin
#define LM35_PIN			DIO_PA7

/// System timer period in msec
#define TIMER_PERIOD_MSEC		10

/// Minimum allowable set point
#define TEMP_MIN_SET_POINT		35

/// Maximum allowable set point
#define TEMP_MAX_SET_POINT		75

/// Initial system set point
#define TEMP_INITIAL_SET_POINT	60

/// On change value for set point when press UP or DOWN buttons
#define TEMP_ON_CHANGE_VALUE	5

/// Temperature tolerance when current temperature reach the set point
#define TEMP_TOLERANCE			5

/// Indicate that system is ON
#define SYSTEM_RUNNING			1

/// Indicate that system is OFF
#define SYSTEM_STOPPED			0

/// Mode setting is enabled
#define SETTING_MODE_EN			1

/// Mode setting is disabled
#define SETTING_MODE_DIS		0


#endif /* MACROS_H_ */



