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

#include "Configuration.h"
#include "constants.h"
#include "globals.h"
#include "input.h"
#include "menus.h"
#include "screen.h"

unsigned char currentMenuX;
unsigned char currentMenuLine;

//void  writeMenu(enum menus menu)
//{
//	unsigned char x;
//
//	if(menu == left)
//	{
//		x = size_x * LEFT_MENU_X / 100;
//		currentMenuLine = 0;
//		drawDriveMenu(x);
//		handleDriveMenu(left);
//	}
//	else if(menu == right)
//	{
//		x = RIGHT_MENU_X * size_x / 100;
//		currentMenuLine = 0;
//		drawDriveMenu(x);
//		handleDriveMenu(right);
//	}
//	else if(menu == file)
//	{
//		x = FILE_MENU_X * size_x / 100;
//		currentMenuLine = 0;
//		drawFileMenu(x);
//		handleFileMenu();
//	}
//	else if(menu == command)
//	{
//		x = COMMAND_MENU_X * size_x / 100;
//		currentMenuLine = 0;
//		drawCommandMenu(x);
//		handleCommandMenu();
//	}
//	else if(menu == options)
//	{
//		x = OPTIONS_MENU_X * size_x / 100;
//		currentMenuLine = 0;
//		drawOptionsMenu(x);
//		handleOptionMenu();
//	}	
//}
//
//void  drawFileMenu(unsigned char x)
//{
//	int i = 0;
//	unsigned char oldColor;
//	//unsigned char buffer[79];
//	
//	initFileMenu();
//	
//	//revers(TRUE);
//	oldColor = textcolor(color_text_menus);
//
//	drawMenu(x,
//		FILE_MENU_WIDTH, 
//		FILE_MENU_COUNT, 
//		FILE_MENU_LABELS,
//		FILE_MENU_KEYS);
//
//	//revers(FALSE);
//	textcolor(oldColor);
//}
//
//void  drawDriveMenu(unsigned char x)
//{
//	int i = 0;
//	unsigned char oldColor;
//	//unsigned char buffer[79];
//	
//	initDriveMenu();
//	
//	//revers(TRUE);
//	oldColor = textcolor(color_text_menus);
//
//	drawMenu(x,
//		DRIVE_MENU_WIDTH, 
//		DRIVE_MENU_COUNT, 
//		DRIVE_MENU_LABELS,
//		DRIVE_MENU_KEYS);
//
//	//revers(FALSE);
//	textcolor(oldColor);
//}
//
//
//void  drawCommandMenu(unsigned char x)
//{
//	int i = 0;
//	unsigned char oldColor;
//	//unsigned char buffer[79];
//	
//	initCommandMenu();
//	
//	//revers(TRUE);
//	oldColor = textcolor(color_text_menus);
//
//	drawMenu(x,
//		COMMAND_MENU_WIDTH, 
//		COMMAND_MENU_COUNT, 
//		COMMAND_MENU_LABELS,
//		COMMAND_MENU_KEYS);
//
//	//revers(FALSE);
//	textcolor(oldColor);
//}
//
//void  drawOptionsMenu(unsigned char x)
//{
//	int i = 0;
//	unsigned char oldColor;
//	//unsigned char buffer[79];
//
//	initOptionMenu();
//	
//	//revers(TRUE);
//	oldColor = textcolor(color_text_menus);
//
//	drawMenu(x,
//		OPTION_MENU_WIDTH, 
//		OPTION_MENU_COUNT, 
//		OPTION_MENU_LABELS,
//		OPTION_MENU_KEYS);
//
//	//revers(FALSE);
//	textcolor(oldColor);
//}
//
//void  drawMenu(
//	unsigned char x,
//	unsigned char width, 
//	unsigned char count, 
//	char* labels[],
//	unsigned char keys[])
//{
//	unsigned int i=0, j=0;
//	const unsigned char offset = 0x80;
//	//unsigned test;
//
//	currentMenuX = x;
//	//currentMenuLine = 0;
//
//	saveScreen();
//
//	drawBox(x, 1, width + 1, 
//		count + 1, color_text_borders, FALSE);
//
//	for(i=0; i < count; ++i)
//	{
//		drawMenuLine(
//			(i==currentMenuLine), 
//			keys[i], labels[i], 
//			x + 1, i + 2);
//	}
//}
//
//void  drawMenuLine(
//	unsigned reverse, 
//	unsigned char key, 
//	char* label, 
//	unsigned char x, 
//	unsigned char y)
//{
//	int j;
//	const unsigned char offset = 0x80;
//	unsigned test;
//	revers(reverse);
//
//	for(j=0; j<strlen(label); j++)
//	{
//		test = 
//			(unsigned char)(key + offset) == 
//			(unsigned char)(label[j]);
//
//		if(test)
//		{
//			textcolor(color_text_highlight);
//		}
//
//		gotoxy(x + j, y);
//		cputc(label[j]);
//
//		if(test)
//		{
//			textcolor(color_text_menus);
//		}
//	}
//}

// Writes the menu bar at the top of the screen
// which is scaled to the current screen size.
void writeMenuBar(void)
{
	unsigned char bottom = 0;
	//textcolor(color_text_menus);
	//revers(TRUE);

	//cclearxy(0, 0, size_x);

	//cputsxy(LEFT_MENU_X * size_x / 100, 0, LEFT_MENU);

	//cputsxy(FILE_MENU_X  *size_x / 100, 0, FILE_MENU);

	//cputsxy(COMMAND_MENU_X * size_x / 100, 0, COMMAND_MENU);

	//cputsxy(OPTIONS_MENU_X * size_x / 100, 0, OPTIONS_MENU);

	//cputsxy(RIGHT_MENU_X  *size_x / 100, 0, RIGHT_MENU);
	//	
	//revers(FALSE);

	bottom = size_y - 1;
	cclearxy(0, bottom, size_x);
#ifdef __C64__	
	cputsxy(0, bottom, " HLP  QUIT  SEL  REF  CPY  REN  MDR  DEL");

	revers(TRUE);
	gotoxy(0, bottom); cputc('1');
	gotoxy(5, bottom); cputc('2');
	gotoxy(11, bottom); cputc('3');
	gotoxy(16, bottom); cputc('4');
	gotoxy(21, bottom); cputc('5');
	gotoxy(26, bottom); cputc('6');
	gotoxy(31, bottom); cputc('7');
	gotoxy(36, bottom); cputc('8');

	revers(FALSE);
#endif
#ifdef __C128__
	cputsxy(0, bottom, "  HELP     QUIT    SELECT   REFRESH   COPY    RENAME    MAKE DIRECTORY    DELETE");

	revers(TRUE);
	gotoxy(0, bottom); cputc('F'); cputc('1');
	gotoxy(9, bottom); cputc('F'); cputc('2');
	gotoxy(17, bottom); cputc('F'); cputc('3');
	gotoxy(26, bottom); cputc('F'); cputc('4');
	gotoxy(36, bottom); cputc('F'); cputc('5');
	gotoxy(44, bottom); cputc('F'); cputc('6');
	gotoxy(54, bottom); cputc('F'); cputc('7');
	gotoxy(72, bottom); cputc('F'); cputc('8');

	revers(FALSE);
#endif
}

