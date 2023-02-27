/**
 * \addtogroup APP
 * Main group application
 * @{
 * \file App.h
 * \brief functions prototype for application
 * \author Mustafa M.Montaser
 * \version v2.4.0
 * \date 23-Feb-2023
 * */

/** @} */


#ifndef APP_H_
#define APP_H_


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*
 * APP functions prototype
 */

/*================================================================================================================================*/

/**
 * @brief Initialise the system and all peripherals
 * @param void
 * @return void
 * */
void App_SystemInit(void);

/*================================================================================================================================*/

/**
 * @brief Set ON/OFF button handler
 * @note If not used, application will use default ON/OFF button handler
 * @note If used, must be called before system initialise
 * @param onOffBtnCallBack Pointer to function takes void and return void
 * @return void
 * */
void App_SetOnOffBtnHandler(void (*onOffBtnCallBack) (void));

/*================================================================================================================================*/

/**
 * @brief Set UP button handler
 * @note If not used, application will use default UP button handler
 * @note If used, must be called before system initialise
 * @param upBtnCallBack Pointer to function takes void and return void
 * @return void
 * */
void App_SetUpBtnHandler(void (*upBtnCallBack) (void));

/*================================================================================================================================*/

/**
 * @brief Set DOWN button handler
 * @note If not used, application will use default DOWN button handler
 * @note If used, must be called before system initialise
 * @param downBtnCallBack Pointer to function takes void and return void
 * @return void
 * */
void App_SetDownBtnHandler(void (*downBtnCallBack) (void));

/*================================================================================================================================*/

/**
 * @brief Set timer handler
 * @note If not used, application will use default timer handler
 * @note If used, must be called before system initialise
 * @param timerCallBack Pointer to function takes void and return void
 * @return void
 * */
void App_SetTimerHandler(void (*timerCallBack) (void));

/*================================================================================================================================*/

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

#endif /* APP_H_ */
