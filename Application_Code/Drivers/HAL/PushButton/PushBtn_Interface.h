/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup HAL
 * This group contain HAL drivers
 * @{
 * \addtogroup PushButton
 * PushButton module driver
 * @{
 * \file PushBtn_Interface.h
 * \brief this file contains function prototypes for the PushButton module
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */
/** @} */


#ifndef DRIVERS_HAL_PUSHBUTTON_PUSHBTN_INTERFACE_H_
#define DRIVERS_HAL_PUSHBUTTON_PUSHBTN_INTERFACE_H_

/* macros */

#define PUSH_BTN_PULL_UP		1
#define PUSH_BTN_PULL_DOWN		0

#define PUSH_BTN_PRESSED		1
#define PUSH_BTN_NOT_PRESSED	0

#define PUSH_BTN_INTERRUPT_EN	1
#define PUSH_BTN_INTERRUPT_DIS	0

/* Functions declaration */


/**
 * @brief Initialise the push button
 * @param local_u8PushBtnPin push button pin
 * @param local_u8InterruptState enable or disable interrupt { PUSH_BTN_INTERRUPT_EN, PUSH_BTN_INTERRUPT_DIS }
 * @param ptr_callBack pointer to call back function in case interrupt is enable. If not, equal to NULL
 * @return void
 * */
void PushBtn_voidInit(u8 local_u8PushBtnPin, u8 local_u8InterruptState, void (*ptr_callBack) (void));

/**
 * @brief enable push button
 * @param local_u8PushBtnPin push button pin
 * @return void
 * */
void PushBtn_voidEnable(u8 local_u8PushBtnPin);

/**
 * @brief disable push button
 * @param local_u8PushBtnPin push button pin
 * @return void
 * */
void PushBtn_voidDisable(u8 local_u8PushBtnPin);

/**
 * @brief get push button status
 * @param local_u8PushBtnPin push button pin
 * @return void
 * */
u8 PushBtn_voidGetStatus(u8 local_u8PushBtnPin);


#endif /* DRIVERS_HAL_PUSHBUTTON_PUSHBTN_INTERFACE_H_ */
