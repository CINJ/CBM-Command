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
#include <peekpoke.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "screen.h"
#include "constants.h"
#include "globals.h"
#include "PlatformSpecific.h"
#include "input.h"

#ifdef __C64__
unsigned char* SCREEN_BUFFER;
unsigned char* SCREEN;
unsigned int vicRegister;
unsigned int screenMemoryStart;
#endif

// Prepares the screen 
void setupScreen(void)
{
#ifdef __C64__
	vicRegister = 53727U;
	screenMemoryStart = ((PEEK(vicRegister) & 0xF0) >> 4) * 1024;
	SCREEN = screenMemoryStart;
	SCREEN_BUFFER = screenMemoryStart + 1000u;
#endif

	clrscr();

	textcolor(COLOR_YELLOW);
	bgcolor(COLOR_BLACK);
	bordercolor(COLOR_BLACK);

	return;
}

void __fastcall__ saveScreen(void)
{
#ifdef __C128__
	copyVdcScreen(0x00, 0x10);
#else
	unsigned int colorMemoryStart = 0xD800;
	unsigned int i = 0;

	for(i = 0; i<1000; ++i)
	{
		SCREEN_BUFFER[i] = SCREEN[i];
	}
	
	memcpy(COLOR_BUFFER, colorMemoryStart, 1000);
#endif
}

void __fastcall__ retrieveScreen(void)
{
#ifdef __C128__
	copyVdcScreen(0x10, 0x00);
#else
	unsigned int colorMemoryStart = 0xD800;
	unsigned int i = 0;

	for(i = 0; i<1000; ++i)
	{
	 	SCREEN[i] = SCREEN_BUFFER[i];
	}
	
	memcpy(colorMemoryStart, COLOR_BUFFER, 1000);
#endif

}

void __fastcall__ writeStatusBar(
	unsigned char message[])
{
	unsigned char oldColor, oldX, oldY;

	oldX = wherex();
	oldY = wherey();

	oldColor = textcolor(COLOR_GRAY3);
	revers(TRUE);

	gotoxy(0, size_y - 1);
	cputs(blank_line);

	gotoxy(0, size_y - 1);
	cputs(message);
	
	revers(FALSE);

	gotoxy(oldY, oldY);
	textcolor(oldColor);
}

// Writes the menu bar at the top of the screen
// which is scaled to the current screen size.
void writeMenuBar(void)
{
	unsigned char oldColor;

	oldColor = textcolor(COLOR_GRAY3);
	revers(TRUE);

	gotoxy(0, 0);
	cputs(blank_line);

	gotoxy(LEFT_MENU_X * size_x / 100, 0);
	cputs(LEFT_MENU);

	gotoxy(FILE_MENU_X  *size_x / 100, 0);
	cputs(FILE_MENU);

	gotoxy(COMMAND_MENU_X * size_x / 100, 0);
	cputs(COMMAND_MENU);

	gotoxy(OPTIONS_MENU_X * size_x / 100, 0);
	cputs(OPTIONS_MENU);

	gotoxy(RIGHT_MENU_X  *size_x / 100, 0);
	cputs(RIGHT_MENU);

	revers(FALSE);

	textcolor(oldColor);
}

void drawBox(
	unsigned char x,
	unsigned char y,
	unsigned char w,
	unsigned char h,
	unsigned char color,
	unsigned reverse)
{
	unsigned char oldColor;
	unsigned char line[39];
	unsigned char spcs[39];
	unsigned int i;
	unsigned oldReverse;
	
	for(i=0; i<w-1; ++i)
	{
		line[i] = CH_HLINE;
		spcs[i] = ' ';
	}
	line[i] = '\0';
	spcs[i] = '\0';	
	
	oldColor = textcolor(color);
	oldReverse = revers(reverse);

	// draw top line
	cputcxy(x, y, CH_ULCORNER);
	cputsxy(x+1, y, line);
	cputcxy(x+w, y, CH_URCORNER);

	// draw body
	for(i=y+1; i<y+h; ++i)
	{
		cputcxy(x, i, CH_VLINE);
		cputsxy(x+1, i, spcs);
		cputcxy(x+w, i, CH_VLINE);
	}

	// draw bottom line
	cputcxy(x, y+h, CH_LLCORNER);
	cputsxy(x+1, y+h, line);
	cputcxy(x+w, y+h, CH_LRCORNER);
	
	revers(oldReverse);
	textcolor(oldColor);
}

unsigned char __fastcall__ getCenterX(unsigned char w)
{
	return size_x / 2 - w / 2 - 1;
}

unsigned char __fastcall__ getCenterY(unsigned char h)
{
	return size_y / 2 - h / 2 - 1;
}

void writePanel(
	unsigned drawBorder,
	unsigned reverse,
	unsigned char color,
	unsigned char x, unsigned char y,
	unsigned char h, unsigned char w,
	unsigned char *title,
	unsigned char *cancel,
	unsigned char *ok)
{
	unsigned int i, okLeft, cancelLeft;
	unsigned char oldColor;
	unsigned char oldReverse;
	unsigned char buffer[80];

	saveScreen();

	oldColor = textcolor(color);
	oldReverse = revers(reverse);

	if(drawBorder)
	{
		drawBox(x, y, w, h, color, reverse);
	}
	else
	{
		strncpy(buffer, SPACES, w);
		buffer[w] = '\0';

		for(i=0; i<h; ++i)
		{
			gotoxy(x, y+i);
			cputs(buffer);
		}
	}

	if(title != NULL)
	{
#ifdef __C128__
		// Works around a bug in CC65's CONIO 
		// library on the VDC.
		textcolor(color);
		revers(reverse);
#endif
		sprintf(buffer, "[%s]", title);
		gotoxy(x+1, y);
		cputs(buffer);
	}

	revers(FALSE);

	okLeft = x + w - 2;
	if(ok != NULL)
	{
#ifdef __C128__
		// Works around a bug in CC65's CONIO 
		// library on the VDC.
		textcolor(color);
		revers(reverse);
#endif
		sprintf(buffer, "[%s]", ok);
		okLeft -= strlen(buffer);
		gotoxy(okLeft, y + h - 1);
		cputs(buffer);
	}

	cancelLeft = okLeft - 2;
	if(cancel != NULL)
	{
#ifdef __C128__
		// Works around a bug in CC65's CONIO 
		// library on the VDC.
		textcolor(color);
		revers(reverse);
#endif
		sprintf(buffer, "[%s]", cancel);
		cancelLeft -= strlen(buffer);
		gotoxy(cancelLeft, y + h - 1);
		cputs(buffer);
	}

	textcolor(oldColor);
	revers(oldReverse);
}

void __fastcall__ notImplemented(void)
{
	unsigned char h = 5, w = 23;
	unsigned char x, y;

	saveScreen();

	x = getCenterX(w);
	y = getCenterY(h);

	writePanel(TRUE, TRUE, COLOR_RED, x, y, h, w,
		"Sorry...", "OK", NULL);

	textcolor(COLOR_RED);
	revers(TRUE);
	gotoxy(x+2, y+2);
	cputs("Not yet implemented.");

	waitForEnterEsc();

	retrieveScreen();
}

enum results __fastcall__ drawDialog(
	unsigned char* message[],
	unsigned char lineCount,
	unsigned char* title,
	enum buttons button)
{
	unsigned char x, y, h, w, i, key;
	unsigned char okButton[4];
	unsigned char cancelButton[7];

	h = lineCount + 5;
	w = 20;
	for(i=0; i<lineCount; ++i);
	{
		if(strlen(message[i]) > w) 
			w = strlen(message[i]);
	}

	w += 3;

	x = getCenterX(w);
	y = getCenterY(h);

	if(button & OK) 
	{
		strcpy(okButton, "OK");
	}

	if(button & YES)
	{
		strcpy(okButton, "Yes");
	}

	if(button & CANCEL)
	{
		strcpy(cancelButton, "Cancel");
	}

	if(button & NO)
	{
		strcpy(cancelButton, "No");
	}

	writePanel(
		TRUE, FALSE, COLOR_GRAY2,
		x, y, h, w,
		title,
		(button & NO || button & CANCEL ? cancelButton : NULL),
		(button & OK || button & YES ? okButton : NULL));

	for(i=0; i<lineCount; ++i)
	{
		textcolor(COLOR_GRAY1);
		gotoxy(x+2, i+2+y);
		cputs(message[i]);
	}	

	while(TRUE)
	{
		key = cgetc();

		if(key == CH_ENTER) break;
		if(key == CH_ESC || key == CH_STOP) break;
		if(key == 'o' && button & OK) break;
		if(key == 'y' && button & YES) break;
		if(key == 'c' && button & CANCEL) break;
		if(key == 'n' && button & NO) break;
	}

	switch((int)key)
	{
	case CH_ESC: case CH_STOP: case (int)'n': case (int)'c':
		if(button & NO) return NO_RESULT;
		if(button & CANCEL) return CANCEL_RESULT;
		break;

	case CH_ENTER: case (int)'y': case (int)'o':
		if(button & YES) return YES_RESULT;
		if(button & OK) return OK_RESULT;
		break;
	}

	return CANCEL_RESULT;
}

unsigned __fastcall__ writeYesNo(
	unsigned char *title,
	unsigned char *message[],
	unsigned char lineCount)
{
	enum results result =
		drawDialog(message, lineCount, title, YES | NO);

	return result == YES_RESULT;
}

void writeStatusBarf(unsigned char format[], ...)
{
	unsigned char buffer[80];
	va_list ap;
	va_start(ap,  format);
	vsprintf(buffer, format, ap);
	va_end(ap);
	writeStatusBar(buffer);
}