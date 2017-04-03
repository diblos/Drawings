/*
 * main.c
 *
 * Created: 2012-04-09 4:35:26 PM
 *  Author: Justin
 * 1.0.0.0		-			CW		First Release
 */ 

#include <avr32/io.h>
#include <stdio.h>
#include <string.h>
#include "font.h"
#include "color.h"
#include "h2framework.h"
#include "activity.h"
#include "h2core.h"
#include "util.h"
#include "act.h"


void scpi_task();
//
// START:
//
void (*entry)(void);
int main(void)
{
	int iRet = 0;

	
	//
	// Init Core (all hardware)
	//
	h2core_init(0);
	
	//
	//Init Framework
	//
	h2framework_init("My Drawings", 0x01000000);
	
	//
	// Register Activities
	//
	activity_register(ACT_MAINSCREEN_ID, &act_mainscreen_process);//register to activity manager by activity ID and the main functin pointer
	
	//
	// Start the activity
	//
	activity_start(ACT_MAINSCREEN_ID, ACTCODE_START, 0, 0);		// This function will call in "act_mainscreen_process()" with ACTCODE_START
																// And proceed with act_mainscreen_actstart();
																
	while(1)
	{
		//Mandatory core task
		h2core_task();
		scpi_task();
		//Mandatory Framework task
		h2framework_task();
	}
	
	//
	//END: Exit App, return back to main application sector
	//
	h2core_exit_to_main_sector();
}