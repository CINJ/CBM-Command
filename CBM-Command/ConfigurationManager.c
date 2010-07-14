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


unsigned int main(void)
{
#if defined(__C128__)
	videomode(VIDEOMODE_80COL);
	fast();
#endif

	initialize();
#ifndef __PET__	
	load();
#endif
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
	case CH_F1:
		help();
		break;
	case CH_F2:
		quit();
		break;
	case CH_F3:
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
		color_background = pickColor(color_background);
		break;
	case '2':
		color_border = pickColor(color_border);
		break;
	case '3':
		color_selector = pickColor(color_selector);
		break;
	case '4':
		color_text_borders = pickColor(color_text_borders);
		break;
	case '5':
		color_text_menus = pickColor(color_text_menus);
		break;
	case '6':
		color_text_files = pickColor(color_text_files);
		break;
	case '7':
		color_text_status = pickColor(color_text_status);
		break;
	case '8':
		color_text_highlight = pickColor(color_text_highlight);
		break;
	case '9':
		color_text_other = pickColor(color_text_other);
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
	cclearxy(x, y, 1);
	textcolor(color);
	revers(TRUE);
	cputsxy(x, y, " ");
	revers(FALSE);
	textcolor(color_text_menus);
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
		{ "Are you sure you" },
		{ "want to quit?" }
	};

	saveScreen();

	result = writeYesNo("Confirm", quit_message, 2);
	
	if(result == TRUE)
	{
		clrscr();
		writeStatusBar("Goodbye!");
		exit(EXIT_SUCCESS);
	}

	retrieveScreen();
}

void  writeMenu(void)
{
	writePanel(TRUE, FALSE, color_text_borders,
		0, 0, size_y - 3, size_x - 1,
		"Config Manager",
		NULL, NULL);

	textcolor(color_text_menus);
	cputsxy(1, 3, "Drives");
#ifndef __VIC20__
	cputsxy(2, 4, "L - Default Left Drive : "); gotoxy(27,4); cprintf("%d", defaultLeftDrive);
	cputsxy(2, 5, "R - Default Right Drive: "); gotoxy(27,5); cprintf("%d", defaultRightDrive);
#else
	cputsxy(2, 4, "L - Def Lft Dr :"); cprintf("%d", defaultLeftDrive);
	cputsxy(2, 5, "R - Def Rght Dr:"); cprintf("%d", defaultRightDrive);
#endif

	cputsxy(1, 7, "Colors");
	cputsxy(2, 8,  "1 - Background: "); displayColor(17,8,color_background);
	cputsxy(2, 9,  "2 - Border    : "); displayColor(17,9,color_border);
	cputsxy(2, 10, "3 - Selector  : "); displayColor(17,10,color_selector);
	cputsxy(2, 11, "4 - Box Brders: "); displayColor(17,11,color_text_borders);
	cputsxy(2, 12, "5 - Menus     : "); displayColor(17,12,color_text_menus);
	cputsxy(2, 13, "6 - Filenames : "); displayColor(17,13,color_text_files);
	cputsxy(2, 14, "7 - Status Bar: "); displayColor(17,14,color_text_status);
	cputsxy(2, 15, "8 - Highlight : "); displayColor(17,15,color_text_highlight);
	cputsxy(2, 16, "9 - Other     : "); displayColor(17,16,color_text_other);

}

void  writeFunctionKeys(void)
{
	unsigned char bottom = 0;
	bottom = size_y - 1;
	cclearxy(0, bottom, size_x);
#if defined(__C64__) || defined(__PLUS4__) || defined(__VIC20__)
	cputsxy(0, bottom," HELP  QUIT  SAVE");

	revers(TRUE);
	gotoxy(0, bottom); cputc('1');
	gotoxy(6, bottom); cputc('2');
	gotoxy(12, bottom); cputc('3');

	revers(FALSE);
#endif
#if defined(__C128__) || defined(__PET__)
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
#if defined(__C128__) || defined(__C64__) || defined(__PET__) || defined(__VIC20__) || defined(__PLUS4__)
	unsigned char r, d;
	unsigned char *buffer;
	buffer = calloc(1, sizeof(unsigned char));
#ifndef __PLUS4__
	d = PEEK(0x00BA);
#else
	d = PEEK(174);
#endif
	cbm_open(15,d,15,"");
#ifdef __C64__
	r = cbm_open(1,d,2,"@0:cbmcmd-cfg.c64,s,w");
#endif
#ifdef __C128__
	r = cbm_open(1,d,2,"@0:cbmcmd-cfg.c128,s,w");
#endif
#ifdef __VIC20__
	r = cbm_open(1,d,2,"@0:cbmcmd-cfg.vic20,s,w");
#endif
#ifdef __PET__
	r = cbm_open(1,d,2,"@0:cbmcmd-cfg.pet,s,w");
#endif
#ifdef __PLUS4__
	r = cbm_open(1,d,2,"@0:cbmcmd-cfg.plus4,s,w");
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

unsigned char pickColor(unsigned char startColor)
{
	unsigned char i = 0, j = 0, k = 0;
#ifdef __VIC20__
#define NUM_COLORS 8
	unsigned char colors[NUM_COLORS];
#elif __C64__
#define NUM_COLORS 16
	unsigned char colors[NUM_COLORS];
#elif __C128__
#define NUM_COLORS 16
	unsigned char colors[NUM_COLORS];
#elif __PLUS4__
#define NUM_COLORS 128
	unsigned char colors[NUM_COLORS];
#endif

	for(;i<NUM_COLORS;++i)
	{
		colors[i] = i;
	}

	saveScreen();
	writePanel(TRUE, FALSE, color_text_borders, 0, 0, size_y-1, size_x-1, "Pick Color", "Cancel", "OK");

	revers(TRUE);
	for(i=0; i<NUM_COLORS; i += 16)
	{
		for(j=0; j<16 && i + j < NUM_COLORS; ++j)
		{
			textcolor(colors[j + i]);
			cputcxy(2+j*2, 2+(i/16)*2, ' ');
		}
	}
	revers(FALSE);
	textcolor(color_selector);

	i=startColor / 16; 
	j=startColor % 16;

	while(k != CH_ENTER && k != CH_STOP)
	{
		cputcxy(2+j*2, 3+i*2, '^');
		k=cgetc();
		cputcxy(2+j*2, 3+i*2, ' ');
		switch(k)
		{
		case CH_CURS_DOWN:
			if((i + 1) * 16 < NUM_COLORS) ++i;
			break;

		case CH_CURS_UP:
			if(i > 0) --i;
			break;

		case CH_CURS_LEFT:
			if(j > 0) --j;
			break;

		case CH_CURS_RIGHT:
			if(j < 15 && j +1 < NUM_COLORS) ++j;
			break;

		case CH_ENTER:
			return colors[i*16 + j];
			break;
		}
	}

	//waitForEnterEsc();

	retrieveScreen();
	return startColor;
}
