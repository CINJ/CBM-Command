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
#include <peekpoke.h>

#include "ConfigurationManager.h"
#include "Configuration.h"
#include "constants.h"
#include "globalInput.h"
#include "globals.h"
#include "screen.h"

unsigned char *colors[] =
{
	{ "Black" },
	{ "White" },
	{ "Red" },
	{ "Cyan" },
	{ "Purple" },
	{ "Green" },
	{ "Blue" },
	{ "Yellow" },
	{ "Orange" },
	{ "Brown" },
	{ "Light Red" },
	{ "Dark Gray" },
	{ "Medium Gray" },
	{ "Light Green" },
	{ "Light Blue" },
	{ "Light Gray" }
};

unsigned int main(void)
{
#if defined(__C128__)
	videomode(VIDEOMODE_80COL);
	fast();
#endif

	initialize();
	load();
	setupScreen();
	writeFunctionKeys();
	writeMenu();

	while(TRUE)
	{
		readKeyboard();
	}

	return EXIT_SUCCESS;
}

void  readKeyboard(void)
{
	unsigned char result;

	result = cgetc();

	switch((int)result)
	{
	case KEY_F1:
		help();
		break;
	case KEY_F2:
		quit();
		break;
	case KEY_F3:
		save();
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		changeColor(result);
		break;
	case 'l':
		++defaultLeftDrive;
		if(defaultLeftDrive == 16) defaultLeftDrive = 8;
		setupScreen();
		writeFunctionKeys();
		writeMenu();
		break;
	case 'r':
		++defaultRightDrive;
		if(defaultRightDrive == 16) defaultRightDrive = 8;
		setupScreen();
		writeFunctionKeys();
		writeMenu();
		break;
	}
}

void  changeColor(unsigned char key)
{
	unsigned char y, color;
	y = 8 + (key - 49);
	switch((int)key)
	{
	case '1':
		incrementColor(&color_background);
		color = color_background;
		break;
	case '2':
		incrementColor(&color_border);
		color = color_border;
		break;
	case '3':
		incrementColor(&color_selector);
		color = color_selector;
		break;
	case '4':
		incrementColor(&color_text_borders);
		color = color_text_borders;
		break;
	case '5':
		incrementColor(&color_text_menus);
		color = color_text_menus;
		break;
	case '6':
		incrementColor(&color_text_files);
		color = color_text_files;
		break;
	case '7':
		incrementColor(&color_text_status);
		color = color_text_status;
		break;
	case '8':
		incrementColor(&color_text_highlight);
		color = color_text_other;
		break;
	case '9':
		incrementColor(&color_text_other);
		color = color_text_highlight;
		break;
	}
	setupScreen();
	writeFunctionKeys();
	writeMenu();
}

void  displayColor(
	unsigned char x,
	unsigned char y,
	unsigned char color)
{
	cclearxy(x, y, 12);
	textcolor(color);
	revers(TRUE);
	cputsxy(x, y, " ");
	revers(FALSE);
	textcolor(color_text_menus);
	cputsxy(x+1, y, colors[color]);
}

void  incrementColor(unsigned char *color)
{
#if defined(__C128__) || defined(__C64__)
	if((unsigned)(*color) == COLOR_GRAY3) (*color) = (unsigned char)COLOR_BLACK;
#else
	if((unsigned)(*color) == 7) (*color) = 0;
#endif
	else { ++(*color); }
	
	return;
}

void  help(void)
{
	unsigned char *help_message[] =
	{
		{ "Please visit:" },
		{ "http://cbmcommand.codeplex.com/" },
		{ "        /documentation" }
	};

	saveScreen();

	drawDialog(help_message, 3, "Help", OK);

	retrieveScreen();
}

void  quit(void)
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

void  writeMenu(void)
{
	writePanel(TRUE, FALSE, color_text_borders,
		0, 0, size_y - 3, size_x - 1,
		"CBM-Command Configuration Manager",
		NULL, NULL);

	textcolor(color_text_menus);
	cputsxy(1, 3, "Drives");
	cputsxy(2, 4, "L - Default Left Drive :"); gotoxy(27,4); cprintf("%d", defaultLeftDrive);
	cputsxy(2, 5, "R - Default Right Drive: "); gotoxy(27,5); cprintf("%d", defaultRightDrive);

	cputsxy(1, 7, "Colors");
	cputsxy(2, 8,  "1 - Background    : "); displayColor(22,8,color_background);
	cputsxy(2, 9,  "2 - Border        : "); displayColor(22,9,color_border);
	cputsxy(2, 10, "3 - Selector      : "); displayColor(22,10,color_selector);
	cputsxy(2, 11, "4 - Box Borders   : "); displayColor(22,11,color_text_borders);
	cputsxy(2, 12, "5 - Menus         : "); displayColor(22,12,color_text_menus);
	cputsxy(2, 13, "6 - Filenames     : "); displayColor(22,13,color_text_files);
	cputsxy(2, 14, "7 - Status Bar    : "); displayColor(22,14,color_text_status);
	cputsxy(2, 15, "8 - Text Highlight: "); displayColor(22,15,color_text_highlight);
	cputsxy(2, 16, "9 - Other         : "); displayColor(22,16,color_text_other);

}

void  writeFunctionKeys(void)
{
	unsigned char bottom = 0;
	bottom = size_y - 1;
	cclearxy(0, bottom, size_x);
#ifdef __C64__	
	cputsxy(0, bottom," HELP  QUIT  SAVE");

	revers(TRUE);
	gotoxy(0, bottom); cputc('1');
	gotoxy(6, bottom); cputc('2');
	gotoxy(12, bottom); cputc('3');

	revers(FALSE);
#endif
#ifdef __C128__
	cputsxy(0, bottom, "  HELP     QUIT    SAVE");

	revers(TRUE);
	gotoxy(0, bottom); cputc('F'); cputc('1');
	gotoxy(9, bottom); cputc('F'); cputc('2');
	gotoxy(17, bottom); cputc('F'); cputc('3');

	revers(FALSE);
#endif
}

void  save(void)
{
#if defined(__C128__) || defined(__C64__)
	unsigned char r, d;
	unsigned char *buffer;
	buffer = calloc(1, sizeof(unsigned char));
	d = PEEK(0x00BA);
	cbm_open(15,d,15,"");
#ifdef __C64__
	r = cbm_open(1,d,2,"@0:cbmcmd-cfg.c64,s,w");
#endif
#ifdef __C128__
	r = cbm_open(1,d,2,"@0:cbmcmd-cfg.c128,s,w");
#endif

	if(r == 0)
	{
		cbm_write(1, &defaultLeftDrive, 1);
		cbm_write(1, &defaultRightDrive, 1);

		cbm_write(1, &color_background, 1);
		cbm_write(1, &color_border, 1);
		cbm_write(1, &color_selector, 1);
		cbm_write(1, &color_text_borders, 1);
		cbm_write(1, &color_text_menus, 1);
		cbm_write(1, &color_text_files, 1);
		cbm_write(1, &color_text_status, 1);
		cbm_write(1, &color_text_other, 1);
		cbm_write(1, &color_text_highlight, 1);

		writeStatusBar("Wrote configuration.");
	}
	else
	{
		free(buffer);
		buffer = calloc(41, sizeof(unsigned char));
		writeStatusBarf("Error %d writing cfg", r);
		waitForEnterEsc();
		r = cbm_read(15,buffer,39);
		buffer[r] = '\0';
		writeStatusBar(buffer);
		waitForEnterEsc();
	}

	cbm_close(1);
	cbm_close(15);
	free(buffer);
#endif
}
