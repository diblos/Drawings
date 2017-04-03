/*
 * act_mainscreen.c
 *
 * Created: 2012-11-22 3:34:24 PM
 *  Author: Justin
 */ 
#include <string.h>
#include <stdio.h>

#include "typedef.h"
#include "debug.h"
#include "activity.h"
#include "gui.h"
#include "debug.h"
#include "theme.h"
#include "h2core.h"
#include "h2framework.h"
#include "act.h"
#include "images.h"
#include "font.h"

//
// Screen Division
//
#define MENU_X			THEME_WINDOW_X
#define MENU_Y			THEME_WINDOW_Y
#define MENU_WIDTH		(THEME_WINDOW_WIDTH/2)
#define MENU_HEIGHT		THEME_WINDOW_HEIGHT
#define DRAWING_X		(THEME_WINDOW_X+(THEME_WINDOW_WIDTH/2))
#define DRAWING_Y		THEME_WINDOW_Y
#define DRAWING_WIDTH	(THEME_WINDOW_WIDTH/2)
#define DRAWING_HEIGTH	THEME_WINDOW_HEIGHT

//
// List View Items
//
#define MAIN_SCREEN_MAX_ITEMS 10
static listviewitem lvItemMainScreen[MAIN_SCREEN_MAX_ITEMS]={0};
static listview lvMainScreen = {0};
static int lvDrawTextBox = 0;
static int lvDrawXBar = 0;
static int lvDrawIcon = 0;
static int lvDrawImg = 0;
static int lvExitIndex = 0;

void _clear_drawing_box(void)
{
	lcd_draw_fillrect(DRAWING_X, DRAWING_Y, DRAWING_WIDTH, DRAWING_HEIGTH, BLACK);
}

void _draw_text_box(void)
{
	box txtTest1 = {0};

	_clear_drawing_box();
	
	txtTest1.x = DRAWING_X+10;
	txtTest1.y = DRAWING_Y+10;
	txtTest1.width = DRAWING_WIDTH - 20;
	txtTest1.height = 30;
	txtTest1.margin = 0;
	gui_draw_textbox("Single", font_MsSerif24, BLUE, WHITE, txtTest1, ATTR_ALIGN_CENTER|ATTR_ALIGN_MIDDLE);
	
	txtTest1.x = DRAWING_X+10;
	txtTest1.y = DRAWING_Y+50;
	txtTest1.width = DRAWING_WIDTH - 20;
	txtTest1.height = 150;
	txtTest1.margin = 0;
	gui_draw_textbox_multiline("This is Multi line Texts", font_MsSerif24, BLUE, WHITE, txtTest1, ATTR_ALIGN_CENTER|ATTR_ALIGN_MIDDLE);
}

void _draw_xbar(void)
{
				
	_clear_drawing_box();
	
	lcd_draw_xbar(xbarBlue32, DRAWING_X+10, DRAWING_Y+20, 100, 32);
	
	lcd_draw_xbar(xbarGreen24, DRAWING_X+10, DRAWING_Y+100, 100, 24);
}

void _draw_icon(void)
{
	_clear_drawing_box();
	
	lcd_draw_icon(gIcon_map, DRAWING_X, DRAWING_Y, WHITE, BLUE);
}
	
void _draw_img(void)
{
	_clear_drawing_box();
	
	lcd_draw_gcolorimage((unsigned short*)gImage_globe, DRAWING_X, DRAWING_Y, 0, 0);//use 0 for width and height is to draw all image according to image width and height
}

void act_mainscreen_process_selection(int selectionevent)
{
	int iSelectionIndex;
	
	iSelectionIndex = gui_listview_get_selected_index();
	
	if(selectionevent == LIST_EVENT_SELECT)
	{
		if(iSelectionIndex == lvDrawTextBox)
			_draw_text_box();
		else if(iSelectionIndex == lvDrawXBar)
			_draw_xbar();
		else if(iSelectionIndex == lvDrawIcon)
			_draw_icon();
		else if(iSelectionIndex == lvDrawImg)
			_draw_img();
		else if(iSelectionIndex == lvExitIndex)
			h2core_exit_to_main_sector();
	}
}

void act_mainscreen_show_form()
{
	//Draw Menu
	gui_listview_show(&lvMainScreen);
	
	//Draw Drawing Box
	_clear_drawing_box();
}

void mainscreen_initialize_form(void)
{
	
	gui_listview_initilize_component(&lvMainScreen, LIST_TYPE_BASIC1, MENU_X, MENU_Y, MENU_WIDTH, MENU_HEIGHT, "Select Draw", lvItemMainScreen, MAIN_SCREEN_MAX_ITEMS);
	gui_listview_set_color_scheme(&lvMainScreen, 0);
	
	lvDrawTextBox = gui_listview_additem(&lvMainScreen, 0, 0, "Draw Text Box", "");
	lvDrawXBar = gui_listview_additem(&lvMainScreen, 0, 0, "Draw XBar", "");
	lvDrawIcon = gui_listview_additem(&lvMainScreen, 0, 0, "Draw Icon", "");
    lvDrawImg = gui_listview_additem(&lvMainScreen, 0, 0, "Draw Image", "");
	lvExitIndex = gui_listview_additem(&lvMainScreen, 0, 0, "EXIT", "");
}

void act_mainscreen_actstart()
{
	//h2o_debug_print("act_mainscreen_actstart");
	mainscreen_initialize_form();
	act_mainscreen_show_form();
}

void act_mainscreen_actresume()
{
	//h2o_debug_print("act_mainscreen_actresume");
	act_mainscreen_show_form();
}

void act_mainscreen_actpause()
{
	//h2o_debug_print("act_mainscreen_actpause");
}

void act_mainscreen_actstop()
{
	//h2o_debug_print("act_mainscreen_actstop");
}

void act_mainscreen_actkeyevent(unsigned char event, unsigned char key)
{
	int iEvent;
	
	iEvent = gui_listview_process_key_event(event, key);	//This activity are control by listview
															//So, just to pass the key event to listview key event
															//This will allow control/select the list by arrow key
	
	if(iEvent != LIST_EVENT_NULL)							//Event on Listview will be returned
	{														//Process the event here			
		act_mainscreen_process_selection(iEvent);
	}
}


unsigned char act_mainscreen_process(unsigned short acitivity_code, unsigned char* activity_data, int activity_data_len)
{
	if(acitivity_code == ACTCODE_START)
		act_mainscreen_actstart();
	else if(acitivity_code == ACTCODE_PAUSE)
		act_mainscreen_actpause();
	else if(acitivity_code == ACTCODE_RESUME)
		act_mainscreen_actresume();
	else if(acitivity_code == ACTCODE_STOP)
		act_mainscreen_actstop();
	else if(acitivity_code == ACTCODE_KEY_EVENT)
		act_mainscreen_actkeyevent(*activity_data, *(activity_data+1));
	else
	{
		//h2o_debug_printbytes("Unknown Mainscreen Act", 2, acitivity_code);
	}

	return true;
}

