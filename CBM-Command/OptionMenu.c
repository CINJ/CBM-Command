#include <cbm.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OptionMenu.h"
#include "constants.h"
#include "screen.h"
#include "menus.h"
#include "FileMenu.h"
#include "DriveMenu.h"

unsigned isInitialized = FALSE;

#ifdef __C128__
char* OPTION_MENU_LABELS[3];
unsigned char OPTION_MENU_KEYS[3];
#else
char* OPTION_MENU_LABELS[2];
unsigned char OPTION_MENU_KEYS[2];
#endif

void initOptionMenu(void)
{
	if(!isInitialized)
	{
		OPTION_MENU_LABELS[0] = OPTION_MENU_OPTIONS;
		OPTION_MENU_LABELS[1] = OPTION_MENU_SAVE;
#ifdef __C128__
		OPTION_MENU_LABELS[2] = OPTION_MENU_TOGGLE;
#endif

		OPTION_MENU_KEYS[0] = OPTION_MENU_OPTIONS_KEY;
		OPTION_MENU_KEYS[1] = OPTION_MENU_SAVE_KEY;
#ifdef __C128__
		OPTION_MENU_KEYS[2] = OPTION_MENU_TOGGLE_KEY;
#endif

		isInitialized = TRUE;
	}
}

void handleOptionMenu(void)
{
	unsigned char key;
	unsigned handleKeys = TRUE;
	unsigned char buffer[39];

	while(handleKeys)
	{
		key = cgetc();
		handleKeys = FALSE;
		switch((int)key)
		{
#ifdef __C128__
		case CH_ESC:
#endif
		case CH_STOP:
			retrieveScreen();
			strcpy(buffer, "Escaping menu...");
			writeStatusBar(buffer, 0, 20);
			return;
			break;

		case CH_CURS_UP:
			if(currentMenuLine == 0) currentMenuLine = OPTION_MENU_COUNT - 1;
			else currentMenuLine--;
			retrieveScreen();
			drawOptionsMenu(currentMenuX);
			handleKeys = TRUE;
			break;

		case CH_CURS_DOWN:
			if(currentMenuLine == OPTION_MENU_COUNT - 1) currentMenuLine = 0;
			else currentMenuLine++;
			retrieveScreen();
			drawOptionsMenu(currentMenuX);
			handleKeys = TRUE;
			break;

		case CH_CURS_LEFT:
			retrieveScreen();
			writeMenu(file);
			return;
			break;

		case CH_CURS_RIGHT:
			retrieveScreen();
			writeMenu(command);
			return;
			break;

		case CH_ENTER:
			key = OPTION_MENU_KEYS[currentMenuLine];

		default:
			if(key == OPTION_MENU_OPTIONS_KEY)
			{
				retrieveScreen();
				strcpy(buffer, OPTION_MENU_OPTIONS);
				writeStatusBar(buffer, 0, 20);
			}
#ifdef __C128__
			else if(key == OPTION_MENU_TOGGLE_KEY)
			{
				retrieveScreen();
				strcpy(buffer, OPTION_MENU_TOGGLE);
				writeStatusBar(buffer, 0, 20);
			}
#endif
			else if(key == OPTION_MENU_SAVE_KEY)
			{
				retrieveScreen();
				strcpy(buffer, OPTION_MENU_SAVE);
				writeStatusBar(buffer, 0, 20);
			}
			else
			{
				handleKeys = TRUE;
			}
			break;
		}
	}
}