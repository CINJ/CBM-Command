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
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Configuration.h"
#include "constants.h"
#include "globals.h"
#include "screen.h"

unsigned int main(void)
{

#if defined(__C128__)
	videomode(VIDEOMODE_80COL);
	fast();
#endif

	initialize();
	setupScreen();
	writeFunctionKeys();
	writeMenu();

	while(TRUE)
	{
		readKeyboard();
	}

	return EXIT_SUCCESS;
}

void __fastcall__ readKeyboard(void)
{
	unsigned char result;

	result = cgetc();

	switch((int)result)
	{
	case KEY_F2:
		quit();
		break;
	}
}

void __fastcall__ quit(void)
{
	unsigned result;
	unsigned char *quit_message[] =
	{
		{ "Are you sure you want to quit?" }
	};

	saveScreen();

	result = writeYesNo("Confirm", quit_message, 1);
	
	if(result == TRUE)
	{
		writeStatusBar("Goodbye!");
		exit(EXIT_SUCCESS);
	}

	retrieveScreen();
}

/*
void writePanel(
	unsigned drawBorder,
	unsigned reverse,
	unsigned char color,
	unsigned char x, unsigned char y,
	unsigned char h, unsigned char w,
	unsigned char *title,
	unsigned char *cancel,
	unsigned char *ok);
*/
void __fastcall__ writeMenu(void)
{
	writePanel(TRUE, FALSE, color_text_borders,
		0, 0, size_y - 3, size_x - 1,
		"CBM-Command Configuration Manager",
		NULL, NULL);

	textcolor(color_text_menus);
	cputsxy(1, 3, "Drives");
	cputsxy(2, 4, "L - Default Left Drive :");
	cputsxy(2, 5, "R - Default Right Drive: ");

	cputsxy(1, 7, "Colors");
	cputsxy(2, 8,  "1 - Background    : ");
	cputsxy(2, 9,  "2 - Border        : ");
	cputsxy(2, 10, "3 - Selector      : ");
	cputsxy(2, 11, "4 - Box Borders   : ");
	cputsxy(2, 12, "5 - Menus         : ");
	cputsxy(2, 13, "6 - Filenames     : ");
	cputsxy(2, 14, "7 - Status Bar    : ");
	cputsxy(2, 15, "8 - Text Highlight: ");
	cputsxy(2, 16, "9 - Other         : ");
}

void __fastcall__ writeFunctionKeys(void)
{
	unsigned char bottom = 0;
	bottom = size_y - 1;
	cclearxy(0, bottom, size_x);
#ifdef __C64__	
	gotoxy(0, bottom); cputs(" HELP  QUIT  SAVE");

	revers(TRUE);
	gotoxy(0, bottom); cputc('1');
	gotoxy(6, bottom); cputc('2');
	gotoxy(12, bottom); cputc('3');

	revers(FALSE);
#endif
#ifdef __C128__
	gotoxy(0, bottom); 
	cputs("  HELP     QUIT    SAVE");

	revers(TRUE);
	gotoxy(0, bottom); cputc('F'); cputc('1');
	gotoxy(9, bottom); cputc('F'); cputc('2');
	gotoxy(17, bottom); cputc('F'); cputc('3');

	revers(FALSE);
#endif
}
