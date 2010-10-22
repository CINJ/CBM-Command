/***************************************************************
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
#include <stdbool.h>
//#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#ifdef __C128__
#include <c128.h>
#endif

#include "ConfigurationManager.h"
#include "Configuration.h"
#include "constants.h"
#include "globalInput.h"
#include "globals.h"
#include "screen.h"

static void refreshScreen(void)
{
	setupScreen();

	writeFunctionKeys();
	writeMenu();
}

void main(void)
{
#ifdef __C128__
	videomode(VIDEOMODE_80COL);
	fast();
#endif

	initialize();
	refreshScreen();

	while(true)
	{
		readKeyboard();
	}
}

static void readKeyboard(void)
{
	char key = cgetc();

	switch(key)
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
#ifdef COLOR_RED
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		changeColor(key);
		break;
#endif
	case 'l':
		if(++defaultLeftDrive > 15) defaultLeftDrive = 8;
		refreshScreen();
		break;
	case 'r':
		if(++defaultRightDrive > 15) defaultRightDrive = 8;
		refreshScreen();
		break;
	}
}

#ifdef COLOR_RED
static void __fastcall__ changeColor(char key)
{
	switch(key)
	{
	case '1':
		pickColor(&color_background);
		break;
	case '2':
		pickColor(&color_border);
		break;
	case '3':
		pickColor(&color_selector);
		break;
	case '4':
		pickColor(&color_text_borders);
		break;
	case '5':
		pickColor(&color_text_menus);
		break;
	case '6':
		pickColor(&color_text_files);
		break;
	case '7':
		pickColor(&color_text_status);
		break;
	case '8':
		pickColor(&color_text_highlight);
		break;
	case '9':
		pickColor(&color_text_other);
		break;
	}
	refreshScreen();
}

static void __fastcall__ displayColor(unsigned char color)
{
	gotox(14);
	cputc(':');
	(void)textcolor(color);
	revers(true);
	cputc(' ');
	revers(false);
	(void)textcolor(color_text_menus);
}
#endif

static void help(void)
{
	static const char *const help_message[] =
	{
		{ "Please visit:" },
#if size_x < 40
		{ "cbmcommand.codeplex" },
		{ " .com/documentation" }
#else
		{ "http://cbmcommand.codeplex.com/" },
		{ "        /documentation" }
#endif
	};

	//saveScreen();

	drawDialog(help_message, A_SIZE(help_message), "Help", OK);

	retrieveScreen();
}

static void quit(void)
{
	static const char *const quit_message[] =
	{
		{ "Are you sure" },
		{ "you want to quit?" }
	};

	//saveScreen();

	if(writeYesNo("Confirm", quit_message, A_SIZE(quit_message)))
	{
		clrscr();
		writeStatusBar("Goodbye!");
		(void)bordercolor(outsideFrame);
		(void)bgcolor(outsideScreen);
		(void)textcolor(outsideText);
		exit(EXIT_SUCCESS);
	}

	retrieveScreen();
}

static void writeMenu(void)
{
	writePanel(true, false, color_text_borders,
		0, 1, size_y - 3, size_x - 1,
#if size_x < 40
		"Config. Manager",
#else
		"CBM-Command Configuration Manager",
#endif
		NULL, NULL);

	(void)textcolor(color_text_menus);
	cputsxy(1, 4, "Drives:");
#if size_x > 22
	gotox(2); cprintf("\nL - Default  Left Drive:%3u", defaultLeftDrive);
	gotox(2); cprintf("\nR - Default Right Drive:%3u", defaultRightDrive);
#else
	gotox(2); cprintf("\nL - Def  Lft Dr:%2u", defaultLeftDrive);
	gotox(2); cprintf("\nR - Def Rght Dr:%2u", defaultRightDrive);
#endif

#ifdef COLOR_RED
	cputsxy(1, 8, "Colors:");
	gotox(2); cputs("\n1 Background"); displayColor(color_background);
	gotox(2); cputs("\n2 Border"); displayColor(color_border);
	gotox(2); cputs("\n3 Selector"); displayColor(color_selector);
	gotox(2); cputs("\n4 Box Border"); displayColor(color_text_borders);
	gotox(2); cputs("\n5 Menues"); displayColor(color_text_menus);
	gotox(2); cputs("\n6 Filenames"); displayColor(color_text_files);
	gotox(2); cputs("\n7 Status Bar"); displayColor(color_text_status);
	gotox(2); cputs("\n8 Highlight"); displayColor(color_text_highlight);
	gotox(2); cputs("\n9 Other"); displayColor(color_text_other);
#endif
}

static void writeFunctionKeys(void)
{
#define bottom size_y - 1

	(void)textcolor(color_text_other);
	//cclearxy(0, bottom, size_x);
	cputsxy(2, bottom, "HELP    QUIT    SAVE");

	revers(true);
#ifdef __PET__
	cputcxy(1, bottom, '1');
	gotox(9); cputc('2');
	gotox(17); cputc('3');
#else
	cputsxy(0, bottom, "F1");
	gotox(8); cputs("F2");
	gotox(16); cputs("F3");
#endif
	revers(false);
}

static void save(void)
{
#ifdef __CBM__
	unsigned char d;
	signed char r;

	cbm_open(15,_curunit,15,"");	// open the status channel
	d = cbm_open(1, _curunit, 3, "@0:cbmcmd-cfg."
#ifdef __C64__
		"c64"
#endif
#ifdef __C128__
		"c128"
#endif
#ifdef __VIC20__
		"vic20"
#endif
#ifdef __PET__
		"pet"
#endif
#ifdef __PLUS4__
		"plus4"
#endif
		",s,w");
	if(d == 0)			// XXX: success means only that the drive exists
	{
		cbm_write(1, &defaultLeftDrive, 1);
		cbm_write(1, &defaultRightDrive, 1);

// The CBM/Pet clan (except the CBM510) doesn't support color.
// Don't save colors if only black and white are defined.
#ifdef COLOR_RED
		cbm_write(1, &color_background, 1);
		cbm_write(1, &color_border, 1);
		cbm_write(1, &color_selector, 1);
		cbm_write(1, &color_text_borders, 1);
		cbm_write(1, &color_text_menus, 1);
		cbm_write(1, &color_text_files, 1);
		cbm_write(1, &color_text_status, 1);
		cbm_write(1, &color_text_other, 1);
		cbm_write(1, &color_text_highlight, 1);
#endif

		r = cbm_read(15, buffer, (sizeof buffer) - 1);
		buffer[r < 0 ? 0 : r] = '\0';
		if (buffer[0] != '0')
		{
			writeStatusBar(buffer);
			waitForEnterEsc();
		}
		else
		{
			writeStatusBar("Wrote configuration.");
		}
	}
	else
	{
		waitForEnterEscf("Error %u openning cfg", d);
		r = cbm_read(15,buffer,(sizeof buffer) - 1);
		buffer[r < 0 ? 0 : r] = '\0';
		writeStatusBar(buffer);
		waitForEnterEsc();
	}

	cbm_close(1);
	cbm_close(15);
#endif
}

#ifdef COLOR_RED
static void __fastcall__ pickColor(unsigned char *color)
{
	unsigned char k, j, i;
#if defined(__VIC20__)
#define NUM_COLORS 8
#elif defined(__C64__) || defined(__C128__) || defined(__CBM510__)
#define NUM_COLORS 16
#elif defined(__PLUS4__)
#define NUM_COLORS 128
#endif

	writePanel(true, false, color_text_borders, 0, 0, size_y-1, size_x-1,
		"Pick a Color", "Cancel", "OK");

	revers(true);
	for(i=0; i<NUM_COLORS; i += 16)
	{
		for(j=0; j<16 && (unsigned char)(i + j) < NUM_COLORS; ++j)
		{
			textcolor(j + i);
			cputcxy(2+j*2, 2+i/(16/2), ' ');
		}
	}
	revers(false);
	textcolor(color_selector);

	i = *color / 16;
	j = *color % 16;

	for (;;)
	{
		cputcxy(2+j*2, 3+i*2, '^');
		k=getKey();
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
			*color = j + i*16;
		case CH_STOP:
			return;
		}
	}
}
#endif
