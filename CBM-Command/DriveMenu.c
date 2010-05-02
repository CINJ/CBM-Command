#include <cbm.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DriveMenu.h"
#include "drives.h"
#include "constants.h"
#include "screen.h"
#include "menus.h"

unsigned isInitialized = FALSE;
char* DRIVE_MENU_LABELS[3];
unsigned char DRIVE_MENU_KEYS[3];

void initDriveMenu(void)
{
	if(!isInitialized)
	{
		DRIVE_MENU_LABELS[0] = DRIVE_MENU_ON_OFF;
		DRIVE_MENU_LABELS[1] = DRIVE_MENU_REREAD;
		DRIVE_MENU_LABELS[2] = DRIVE_MENU_DRIVE;

		DRIVE_MENU_KEYS[0] = DRIVE_MENU_ON_OFF_KEY;
		DRIVE_MENU_KEYS[1] = DRIVE_MENU_REREAD_KEY;
		DRIVE_MENU_KEYS[2] = DRIVE_MENU_DRIVE_KEY;

		isInitialized = TRUE;
	}
}

void handleDriveMenu(enum menus menu)
{
	unsigned finalRetrieve = TRUE;
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
			if(currentMenuLine == 0) currentMenuLine = DRIVE_MENU_COUNT - 1;
			else currentMenuLine--;
			retrieveScreen();
			drawDriveMenu(currentMenuX);
			handleKeys = TRUE;
			break;

		case CH_CURS_DOWN:
			if(currentMenuLine == DRIVE_MENU_COUNT - 1) currentMenuLine = 0;
			else currentMenuLine++;
			retrieveScreen();
			drawDriveMenu(currentMenuX);
			handleKeys = TRUE;
			break;

		case CH_CURS_LEFT:
			retrieveScreen();
			currentMenuLine = 0;
			if(menu == right)
			{
				writeMenu(command);
			}
			else
			{
				writeMenu(right);
			}
			return;
			break;

		case CH_CURS_RIGHT:
			retrieveScreen();
			currentMenuLine = 0;
			if(menu == left)
			{
				writeMenu(file);
			}
			else
			{
				writeMenu(left);
			}
			return;
			break;

		case CH_ENTER:
			key = DRIVE_MENU_KEYS[currentMenuLine];

		default:
			if(key == DRIVE_MENU_ON_OFF_KEY)
			{
				retrieveScreen();
				notImplemented();
			}
			else if(key == DRIVE_MENU_DRIVE_KEY)
			{
				retrieveScreen();
				listDrives(menu);
				retrieveScreen();
				if(menu == left)
				{
					getDirectory(&leftPanelDrive);
					displayDirectory(&leftPanelDrive, menu);
				}
				else
				{
					getDirectory(&rightPanelDrive);
					displayDirectory(&rightPanelDrive, menu);
				}
				finalRetrieve = FALSE;
			}
			else if(key == DRIVE_MENU_REREAD_KEY)
			{
				retrieveScreen();
				if(menu == left)
				{
					getDirectory(&leftPanelDrive);
					displayDirectory(&leftPanelDrive, menu);
				}
				else
				{
					getDirectory(&rightPanelDrive);
					displayDirectory(&rightPanelDrive, menu);
				}
				finalRetrieve = FALSE;
			}
			else
			{
				handleKeys = TRUE;
			}
			break;
		}

	}

	if(finalRetrieve) retrieveScreen();
}