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

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#ifdef __C128__
#include <c128.h>
#endif

#include "constants.h"
#include "input.h"
#include "menus.h"
#include "screen.h"

unsigned isInitialized = FALSE;

#ifdef __C128__
char* FILE_MENU_LABELS[9];
unsigned char FILE_MENU_KEYS[9];
#else
char* FILE_MENU_LABELS[8];
unsigned char FILE_MENU_KEYS[8];
#endif

void __fastcall__ initFileMenu(void)
{
	if(!isInitialized)
	{
		FILE_MENU_LABELS[0] = FILE_MENU_ABOUT;
		FILE_MENU_LABELS[1] = FILE_MENU_HELP;
		FILE_MENU_LABELS[2] = FILE_MENU_COPY;
		FILE_MENU_LABELS[3] = FILE_MENU_RENAME;
		FILE_MENU_LABELS[4] = FILE_MENU_MAKE_DIR;
		FILE_MENU_LABELS[5] = FILE_MENU_DELETE;
		FILE_MENU_LABELS[6] = FILE_MENU_FILE_INFO;
		FILE_MENU_LABELS[7] = FILE_MENU_QUIT;

#ifdef __C128__
		FILE_MENU_LABELS[8] = FILE_MENU_GO64;
#endif

		FILE_MENU_KEYS[0] = FILE_MENU_ABOUT_KEY;
		FILE_MENU_KEYS[1] = FILE_MENU_HELP_KEY;
		FILE_MENU_KEYS[2] = FILE_MENU_COPY_KEY;
		FILE_MENU_KEYS[3] = FILE_MENU_RENAME_KEY;
		FILE_MENU_KEYS[4] = FILE_MENU_MAKE_DIR_KEY;
		FILE_MENU_KEYS[5] = FILE_MENU_DELETE_KEY;
		FILE_MENU_KEYS[6] = FILE_MENU_FILE_INFO_KEY;
		FILE_MENU_KEYS[7] = FILE_MENU_QUIT_KEY;

#ifdef __C128__
		FILE_MENU_KEYS[8] = FILE_MENU_GO64_KEY;
#endif

		isInitialized = TRUE;
	}
}

void __fastcall__ handleFileMenu(void)
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
			if(currentMenuLine == 0) currentMenuLine = FILE_MENU_COUNT - 1;
			else currentMenuLine--;
			retrieveScreen();
			drawFileMenu(currentMenuX);
			handleKeys = TRUE;
			break;

		case CH_CURS_DOWN:
			if(currentMenuLine == FILE_MENU_COUNT - 1) currentMenuLine = 0;
			else currentMenuLine++;
			retrieveScreen();
			drawFileMenu(currentMenuX);
			handleKeys = TRUE;
			break;

		case CH_CURS_LEFT:
			retrieveScreen();
			writeMenu(left);
			return;

		case CH_CURS_RIGHT:
			retrieveScreen();
			writeMenu(options);
			return;

		case CH_ENTER:
			key = FILE_MENU_KEYS[currentMenuLine];

		default:
			if(key == FILE_MENU_ABOUT_KEY)
			{
				retrieveScreen();
				writeAboutBox();
			}
			else if(key == FILE_MENU_HELP_KEY)
			{
				retrieveScreen();
				writeHelpPanel();
			}
			else if(key == FILE_MENU_COPY_KEY)
			{
				retrieveScreen();
				copyFiles();
			}
			else if(key == FILE_MENU_RENAME_KEY)
			{
				retrieveScreen();
				renameFile();
			}
			else if(key == FILE_MENU_MAKE_DIR_KEY)
			{
				retrieveScreen();
				makeDirectory();
			}
			else if(key == FILE_MENU_DELETE_KEY)
			{
				retrieveScreen();
				deleteFiles();
			}
			else if(key == FILE_MENU_FILE_INFO_KEY)
			{
				retrieveScreen();
				writeFileInfoPanel();
			}
			else if(key == FILE_MENU_QUIT_KEY)
			{
				retrieveScreen();
				quit();
			}
#ifdef __C128__
			else if(key == FILE_MENU_GO64_KEY)
			{
				retrieveScreen();
				go64();
			}
#endif
			else
			{
				handleKeys = TRUE;
			}
			break;
		}
	}
}

void __fastcall__ writeHelpPanel(void)
{
	notImplemented();
}

void __fastcall__ copyFiles(void)
{
	notImplemented();
}

void __fastcall__ renameFile(void)
{
	notImplemented();
}

void __fastcall__ makeDirectory(void)
{
	notImplemented();
}

void __fastcall__ deleteFiles(void)
{
	notImplemented();
}

void __fastcall__ writeFileInfoPanel(void)
{
	notImplemented();
}

#ifdef __C128__
void __fastcall__ go64(void)
{
	writeStatusBar("Going to 64 mode.  Goodbye!", 0, 20);
	c64mode();
}
#endif

void __fastcall__ quit(void)
{
	writeStatusBar("Goodbye!", 0, 20);
	exit(EXIT_SUCCESS);
}

void __fastcall__ writeAboutBox(void)
{
	unsigned char x, y, i;
	unsigned char oldColor;
	unsigned char oldReverse;

	const unsigned char w = 25;
	const unsigned char h = 11;
	
	unsigned char* lines[7] =
		{
			"Copyright 2010",
			"Payton Byrd",
			"version 2010-05-01",
			"Thanks to Uz for CC65",
			"and all the support!",
			"",
#ifdef __C128__
			"C128 Edition"
#else
			"C64 Edition"
#endif
	};


	x = getCenterX(w);
	y = getCenterY(h);

	writePanel(TRUE, TRUE,
		COLOR_RED, 
		x, y, h, w,
		"About CBM-Command",
		NULL, "OK");

	oldReverse = revers(FALSE);
	oldColor = textcolor(COLOR_WHITE);
	y = getCenterY(7);
	for(i=0; i<7; i++)
	{
		x = getCenterX(strlen(lines[i]));
		gotoxy(x, y + i);
		cputs(lines[i]);
	}

	revers(oldReverse);
	textcolor(oldColor);

	waitForEnterEsc();

	retrieveScreen();

	writeStatusBar("Thank you for using CBM Command.", 0, 10);
}