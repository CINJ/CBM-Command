#include <cbm.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CommandMenu.h"
#include "constants.h"
#include "screen.h"
#include "menus.h"

unsigned isInitialized = FALSE;

char* COMMAND_MENU_LABELS[2];
unsigned char COMMAND_MENU_KEYS[2];

void initCommandMenu(void)
{
	if(!isInitialized)
	{
		COMMAND_MENU_LABELS[0] = COMMAND_MENU_SWAP_PANELS;
		COMMAND_MENU_LABELS[1] = COMMAND_MENU_PANELS_ON_OFF;

		COMMAND_MENU_KEYS[0] = COMMAND_MENU_SWAP_PANELS_KEY;
		COMMAND_MENU_KEYS[1] = COMMAND_MENU_PANELS_ON_OFF_KEY;

		isInitialized = TRUE;
	}
}

void handleCommandMenu(void)
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
			if(currentMenuLine == 0) currentMenuLine = COMMAND_MENU_COUNT - 1;
			else currentMenuLine--;
			retrieveScreen();
			drawCommandMenu(currentMenuX);
			handleKeys = TRUE;
			break;

		case CH_CURS_DOWN:
			if(currentMenuLine == COMMAND_MENU_COUNT - 1) currentMenuLine = 0;
			else currentMenuLine++;
			retrieveScreen();
			drawCommandMenu(currentMenuX);
			handleKeys = TRUE;
			break;

		case CH_CURS_LEFT:
			retrieveScreen();
			writeMenu(options);
			return;
			break;

		case CH_CURS_RIGHT:
			retrieveScreen();
			writeMenu(right);
			return;
			break;

		case CH_ENTER:
			key = COMMAND_MENU_KEYS[currentMenuLine];

		default:
			if(key == COMMAND_MENU_SWAP_PANELS_KEY)
			{
				retrieveScreen();
				notImplemented();
			}
			else if(key == COMMAND_MENU_PANELS_ON_OFF_KEY)
			{
				retrieveScreen();
				notImplemented();
			}
			else
			{
				handleKeys = TRUE;
			}
			break;
		}
	}
}