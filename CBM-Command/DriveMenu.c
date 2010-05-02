/**************************************************************
Copyright (c) 2010, Payton Byrd
All rights reserved.

Redistribution and use in source and binary forms, with or 
without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above 
  copyright notice, this list of conditions and the following 
  disclaimer.

* Redistributions in binary form must reproduce the above 
  copyright notice, this list of conditions and the following 
  disclaimer in the documentation and/or other materials 
  provided with the distribution.

* Neither the name of Payton Byrd nor the names of its 
  contributors may be used to endorse or promote products 
  derived from this software without specific prior written 
  permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************/

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