/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup MCAL
 * This group contain MCAL drivers
 * @{
 * \addtogroup DIO
 * DIO module driver
 * @{
 * \file DIO_Interface.h
 * \brief this file contains function prototypes for the DIO module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


/* special types */

/**
 * @enum DIO_PortId_t
 * 		refer to port ID
 * @var DIO_PortId_t::DIO_PORT_A
 * 		port_A ID
 * @var DIO_PortId_t::DIO_PORT_B
 * 		port_B ID
 * @var DIO_PortId_t::DIO_PORT_C
 * 		port_C ID
 * @var DIO_PortId_t::DIO_PORT_D
 * 		port_D ID
 * */
typedef enum {
	DIO_PORT_A,
	DIO_PORT_B,
	DIO_PORT_C,
	DIO_PORT_D
} DIO_PortId_t;



/**
 * @enum DIO_PinId_t
 * 		refer to PIN ID in each port
 * @var DIO_PinId_t::DIO_PIN0
 * 		PIN_0 ID
 * @var DIO_PinId_t::DIO_PIN1
 * 		PIN_1 ID
 * @var DIO_PinId_t::DIO_PIN2
 * 		PIN_2 ID
 * @var DIO_PinId_t::DIO_PIN3
 * 		PIN_3 ID
 * @var DIO_PinId_t::DIO_PIN4
 * 		PIN_4 ID
 * @var DIO_PinId_t::DIO_PIN5
 * 		PIN_5 ID
 * @var DIO_PinId_t::DIO_PIN6
 * 		PIN_6 ID
 * @var DIO_PinId_t::DIO_PIN7
 * 		PIN_7 ID
 * */
typedef enum {
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
} DIO_PinId_t;



/**
 * @enum DIO_Pin_t
 * 		another method for PIN ID where ones value refer to PIN ID itself and tens value refer to port ID
 * */
typedef enum {
	DIO_PA0 = 10,
	DIO_PA1,
	DIO_PA2,
	DIO_PA3,
	DIO_PA4,
	DIO_PA5,
	DIO_PA6,
	DIO_PA7,

	DIO_PB0 = 20,
	DIO_PB1,
	DIO_PB2,
	DIO_PB3,
	DIO_PB4,
	DIO_PB5,
	DIO_PB6,
	DIO_PB7,

	DIO_PC0 = 30,
	DIO_PC1,
	DIO_PC2,
	DIO_PC3,
	DIO_PC4,
	DIO_PC5,
	DIO_PC6,
	DIO_PC7,

	DIO_PD0 = 40,
	DIO_PD1,
	DIO_PD2,
	DIO_PD3,
	DIO_PD4,
	DIO_PD5,
	DIO_PD6,
	DIO_PD7
} DIO_Pin_t;



/**
 * @enum DIO_PinMode_t
 * 		PIN mode
 * @var DIO_PinMode_t::DIO_PIN_INPUT
 * 		Input PIN
 * @var DIO_PIN_INPUT::DIO_PIN_OUTPUT
 * 		Output PIN
 * */
typedef enum {
	DIO_PIN_INPUT,
	DIO_PIN_OUTPUT
} DIO_PinMode_t;



/**
 * @enum DIO_PortMode_t
 * 		port mode
 * @var DIO_PortMode_t::DIO_PORT_INPUT
 * 		port is input
 * @var DIO_PortMode_t::DIO_PORT_OUTPUT
 * 		port is output
 * */
typedef enum {
	DIO_PORT_INPUT,
	DIO_PORT_OUTPUT	= 0xFF
} DIO_PortMode_t;



/**
 * @enum DIO_PinValue_t
 * 		PIN value
 * @var DIO_PinValue_t::DIO_PIN_LOW
 * 		pin is low
 * @var DIO_PinValue_t::DIO_PIN_HIGH
 * 		pin is high
 * */
typedef enum {
	DIO_PIN_LOW,
	DIO_PIN_HIGH
} DIO_PinValue_t;



/**
 * @enum DIO_PortValue_t
 * 		all port value
 * @var DIO_PortValue_t::DIO_PORT_LOW
 * 		all port is low
 * @var DIO_PortValue_t::DIO_PORT_HIGH
 * 		all port is high
 * */
typedef enum {
	DIO_PORT_LOW,
	DIO_PORT_HIGH = 0XFF
} DIO_PortValue_t;



/* function declaration */


/**
 * @brief set port mode
 * @param Copy_u8PortId port ID
 * @param Copy_u8PortMode port mode
 * @return void
 * */
void DIO_voidSetPortMode(DIO_PortId_t Copy_u8PortId, DIO_PortMode_t Copy_u8PortMode);

/**
 * @brief write value to all the port
 * @param Copy_u8PortId port ID
 * @param Copy_u8PortValue port value
 * @return void
 * */
void DIO_voidWritePortValue(DIO_PortId_t Copy_u8PortId, u8 Copy_u8PortValue);

/**
 * @brief get port value
 * @param Copy_u8PortId port ID
 * @return port value
 * */
u8 DIO_voidReadPortValue(DIO_PortId_t Copy_u8PortId);


/**
 * @brief set pin mode
 * @param Copy_u8Pin pin ID
 * @param Copy_u8PinMode pin mode
 * @return void
 * */
void DIO_voidSetPinMode(DIO_Pin_t Copy_u8Pin, DIO_PinMode_t Copy_u8PinMode);

/**
 * set pin value to 1
 * @param Copy_u8Pin pin ID
 * @return void
 * */
void DIO_voidSetPinValue(DIO_Pin_t Copy_u8Pin);

/**
 * @brief clear pin value to 0
 * @param Copy_u8Pin pin ID
 * @return void
 * */
void DIO_voidClearPinValue(DIO_Pin_t Copy_u8Pin);

/**
 * @brief toggle pin value
 * @param Copy_u8Pin pin ID
 * @return void
 * */
void DIO_voidTogglePinValue(DIO_Pin_t Copy_u8Pin);

/**
 * @brief writing bit value
 * @param Copy_u8Pin pin ID
 * @param Copy_u8Value PIN (Bit) value
 * @return void
 * */
void DIO_voidWritePinValue(DIO_Pin_t Copy_u8Pin, DIO_PinValue_t Copy_u8Value);

/**
 * getting PIN (Bit) value
 * @param Copy_u8Pin pin ID
 * @return PIN value
 * */
DIO_PinValue_t DIO_u8GetPinValue(DIO_Pin_t Copy_u8Pin);

#endif /* DIO_INTERFACE_H_ */














