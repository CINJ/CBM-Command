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
unsigned int vicRegister;
unsigned int screenMemoryStart;
#endif

// Prepares the screen 
void setupScreen(void)
{
	clrscr();

	textcolor(color_text_other);
	bgcolor(color_background);
	bordercolor(color_border);

	return;
}

void __fastcall__ saveScreen(void)
{
#ifdef __C128__
	copyVdcScreen(0x00, 0x10);
	return;
#else
	int vicRegister = 53272;
	int screenMemoryStart;
	int colorMemoryStart = 0xD800;

	screenMemoryStart = ((PEEK(vicRegister) & 0xF0) >> 4) * 1024;

	memcpy(SCREEN_BUFFER, screenMemoryStart, 1000);
	memcpy(COLOR_BUFFER, colorMemoryStart, 1000);
#endif
}

void __fastcall__ retrieveScreen(void)
{
#ifdef __C128__
	copyVdcScreen(0x10, 0x00);
	return;
#else
	int vicRegister = 53272;
	int screenMemoryStart;
	int colorMemoryStart = 0xD800;

	screenMemoryStart = ((PEEK(vicRegister) & 0xF0) >> 4) * 1024;
	memcpy(screenMemoryStart, SCREEN_BUFFER, 1000);
	memcpy(colorMemoryStart, COLOR_BUFFER, 1000);
#endif

}

void __fastcall__ writeStatusBar(
	unsigned char message[])
{
	unsigned char oldX, oldY;

	oldX = wherex();
	oldY = wherey();

	textcolor(color_text_status);
	revers(TRUE);

	gotoxy(0, size_y - 2);
	cputs(blank_line);

	gotoxy(0, size_y - 2);
	cputs(message);
	
	revers(FALSE);

	gotoxy(oldY, oldY);
}

// Writes the menu bar at the top of the screen
// which is scaled to the current screen size.
void writeMenuBar(void)
{
	unsigned char bottom = 0;
	textcolor(color_text_menus);
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

	bottom = size_y - 1;
	cclearxy(0, bottom, size_x);
#ifdef __C64__	
	gotoxy(0, bottom); cputs(" HLP  QUIT  SEL  REF  CPY  REN  MDR  DEL");

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
	gotoxy(0, bottom); 
	cputs("  HELP     QUIT    SELECT   REFRESH   COPY    RENAME    MAKE DIRECTORY    DELETE");

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

void drawBox(
	unsigned char x,
	unsigned char y,
	unsigned char w,
	unsigned char h,
	unsigned char color,
	unsigned reverse)
{
	unsigned int i = 0;
	
	textcolor(color);
	revers(reverse);

	// draw top line
	cputcxy(x, y, CH_ULCORNER);
	chlinexy(x + 1, y, w - 1);
	cputcxy(x+w, y, CH_URCORNER);

	// draw body
	for(i=y+1; i<y+h; ++i)
	{
		cputcxy(x, i, CH_VLINE);
		cclearxy(x + 1, i, w - 1);
		cputcxy(x+w, i, CH_VLINE);
	}

	// draw bottom line
	cputcxy(x, y+h, CH_LLCORNER);
	chlinexy(x + 1, y+h, w - 1);
	cputcxy(x+w, y+h, CH_LRCORNER);
}

unsigned char __fastcall__ getCenterX(unsigned char w)
{
	return (size_x / 2) - (w / 2) - 1;
}

unsigned char __fastcall__ getCenterY(unsigned char h)
{
	return (size_y / 2) - (h / 2) - 1;
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
	unsigned int i = 0, okLeft = 0, cancelLeft = 0;
	unsigned char buffer[80];

	saveScreen();

	textcolor(color);
	revers(reverse);

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
}

void __fastcall__ notImplemented(void)
{
	unsigned char h = 5, w = 23;
	unsigned char x, y;

	saveScreen();

	x = getCenterX(w);
	y = getCenterY(h);

	writePanel(TRUE, TRUE, color_border, x, y, h, w,
		"Sorry...", "OK", NULL);

	textcolor(color_text_other);
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
	unsigned char x = 0, y = 0, h = 0, w = 0, i = 0, key = 0, l = 0;
	unsigned char okButton[4];
	unsigned char cancelButton[7];

	h = lineCount + 5;
	w = 30;
	for(i=0; i<lineCount; ++i);
	{
		l = strlen(message[i]);
		if(l > w) w = l;
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
		TRUE, FALSE, color_text_borders,
		x, y, h, w,
		title,
		(button & NO || button & CANCEL ? cancelButton : NULL),
		(button & OK || button & YES ? okButton : NULL));

	for(i=0; i<lineCount; ++i)
	{
		textcolor(color_text_other);
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

enum results __fastcall__ drawInputDialog(
	unsigned char lineCount,
	unsigned char length,
	unsigned char *message[],
	unsigned char *title,
	unsigned char *resultText)
{
	unsigned char x = 0, y = 0, h = 0, w = 0, i = 0, 
		key = 0, count = 0;
	unsigned result;
	unsigned char *input;
	input = calloc(length+1, sizeof(unsigned char));
	h = lineCount + 6;
	w = length + 3;
	//for(i=0; i<lineCount; ++i);
	//{
	//	if(strlen(message[i]) > w) 
	//		w = strlen(message[i]);
	//}

	x = getCenterX(w);
	y = getCenterY(h);

	writePanel(
		TRUE, FALSE, color_text_borders,
		x, y, h, w,
		title,
		"Cancel",
		"Done");

	for(i=0; i<lineCount; ++i)
	{
		textcolor(color_text_other);
		gotoxy(x+2, i+2+y);
		cputs(message[i]);
	}	
	++i;
	
	gotoxy(x+2, i+2+y);
	revers(TRUE);
	textcolor(color_text_other);
	
	cclearxy(x+2, i+2+y, length + 1);
	cputcxy(x+2, i+2+y, '<');
	count = 0;
	key = cgetc();
	while(key != CH_ESC && key != CH_STOP && key != CH_ENTER)
	{
		if( count < length &&
			(
				(key >= 33 && key <= 95) ||
				(key >= 65 + 0x80 && key <= 90 + 0x80)
			)
		)
		{
			input[count] = key;
			input[count+1] = '\0';
			gotoxy(x+2+count, i+2+y);
			cputc(key);
			++count;
			gotoxy(x+2+count, i+2+y);
			cputc('<');
		}
		else if(key == CH_DEL && count > 0)
		{
			input[count] = '\0';
			gotoxy(x+2+count, i+2+y);
			cputc(' ');
			--count;
			gotoxy(x+2+count, i+2+y);
			cputc('<');
		}

		key = cgetc();
	}

	strcpy(resultText, input);

	switch((int)key)
	{
	case CH_ENTER: result = OK_RESULT; break;
	default: result = CANCEL_RESULT; break;
	}

	revers(FALSE);
	free(input);
	return result;
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