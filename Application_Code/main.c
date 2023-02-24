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

#include "Drivers/LIB/StdTypes.h"
#include "App.h"


int main()
{
	/// setting handlers
	App_SetOnOffBtnHandler(NULL);
	App_SetUpBtnHandler(NULL);
	App_SetDownBtnHandler(NULL);
	App_SetTimerHandler(NULL);


	/// System Initialise
	App_SystemInit();

	while(1) {}
	return 0;
}







