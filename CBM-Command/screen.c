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

#ifdef __CBM__
#include <cbm.h>
#endif
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "screen.h"
#include "Configuration.h"
#include "constants.h"
#include "globalInput.h"
#include "globals.h"
#include "PlatformSpecific.h"
#include "input.h"

#if defined(__PET__)
#define screenMemoryStart 0x8000
static unsigned char SCREEN_BUFFER[1000];
//static unsigned char COLOR_BUFFER[1000];
#endif

#if defined(__VIC20__)
#define screenMemoryStart 4096
#define colorMemoryStart 37388
static unsigned char SCREEN_BUFFER[506];
static unsigned char COLOR_BUFFER[506];
#endif

// Prepares the screen
void setupScreen(void)
{
	textcolor(color_text_other);
	bgcolor(color_background);
	bordercolor(color_border);

	clrscr();
}

#ifndef __C64__
void saveScreen(void)
{
#ifdef __C128__
	copyVdcScreen(0x00, 0x10);
#elif defined(__PET__) || defined(__VIC20__)
	memcpy(SCREEN_BUFFER, screenMemoryStart, sizeof(SCREEN_BUFFER));
#endif
//#ifdef __VIC20__
//	memcpy(COLOR_BUFFER, colorMemoryStart, sizeof(COLOR_BUFFER));
//#endif
}

void retrieveScreen(void)
{
#ifdef __C128__
	copyVdcScreen(0x10, 0x00);
#elif defined(__PET__) || defined(__VIC20__)
	memcpy(screenMemoryStart, SCREEN_BUFFER, sizeof(SCREEN_BUFFER));
#endif
//#ifdef __VIC20__
//	memcpy(colorMemoryStart, COLOR_BUFFER, sizeof(COLOR_BUFFER));
//#endif
}
#endif

void  writeStatusBar(
	unsigned char message[])
{
	unsigned char oldX, oldY;

	oldX = wherex();
	oldY = wherey();

	textcolor(color_text_status);
	revers(TRUE);

	cclearxy(0, 0, size_x);

	cputsxy(0, 0, message);
	
	revers(FALSE);

	gotoxy(oldY, oldY);
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
#if defined(__C128__) || defined(__C64__) || defined(__PET__) || defined(__VIC20__)
		cputcxy(x, i, CH_VLINE);
		cclearxy(x + 1, i, w - 1);
		cputcxy(x+w, i, CH_VLINE);
#else
		cclearxy(x, i, w);
#endif
	}

	// draw bottom line
	cputcxy(x, y+h, CH_LLCORNER);
	chlinexy(x + 1, y+h, w - 1);
	cputcxy(x+w, y+h, CH_LRCORNER);
}

unsigned char  getCenterX(unsigned char w)
{
	return (size_x / 2) - (w / 2) - 1;
}

unsigned char  getCenterY(unsigned char h)
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
		//strncpy(buffer, SPACES, w);
		//buffer[w] = '\0';

		for(i=0; i<h; ++i)
		{
			//cputsxy(x, y+i,buffer);
			cclearxy(x,y+i,w);
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
		cputsxy(x+1, y,buffer);
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
		cputsxy(okLeft, y + h - 1, buffer);
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
		cputsxy(cancelLeft, y + h - 1,buffer);
	}
}

void  notImplemented(void)
{
	//unsigned char h = 5, w = 23;
	//unsigned char x, y;

	//saveScreen();

	//x = getCenterX(w);
	//y = getCenterY(h);

	//writePanel(TRUE, TRUE, color_border, x, y, h, w,
	//	"Sorry...", "OK", NULL);

	//textcolor(color_text_other);
	//revers(TRUE);
	//cputsxy(x+2, y+2, "Not yet implemented.");

	//waitForEnterEsc();

	//retrieveScreen();
	saveScreen();
	writeStatusBar("Not implemented...");
	waitForEnterEsc();
	retrieveScreen();
}

enum results  drawDialog(
	unsigned char* message[],
	unsigned char lineCount,
	unsigned char* title,
	enum buttons button)
{
	unsigned char x = 0, y = 0, h = 0, w = 0, i = 0, key = 0, l = 0;
	unsigned char okButton[4];
	unsigned char cancelButton[7];

	h = lineCount + 5;
	w = 33;

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
		cputsxy(x+2, i+2+y,message[i]);
	}	

	while(TRUE)
	{
		key = cgetc();

		if(key == CH_ENTER) break;
		if(key == CH_ESC 
#if defined(__C128__) || defined(__C64__) || defined(__PET__) || defined(__VIC20__)
			|| key == CH_STOP
#endif
			) break;
		if(key == 'o' && button & OK) break;
		if(key == 'y' && button & YES) break;
		if(key == 'c' && button & CANCEL) break;
		if(key == 'n' && button & NO) break;
	}

	switch((int)key)
	{
	case CH_ESC: 
#if defined(__C128__) || defined(__C64__) || defined(__PET__) || defined(__VIC20__)
	case CH_STOP: 
#endif
	case (int)'n': 
	case (int)'c':
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

enum results  drawInputDialog(
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
		cputsxy(x+2, i+2+y,message[i]);
	}	
	++i;
	
	gotoxy(x+2, i+2+y);
	revers(TRUE);
	textcolor(color_text_other);
	
	cclearxy(x+2, i+2+y, length + 1);
	cputcxy(x+2, i+2+y, '<');
	count = 0;
	key = cgetc();
	while(key != CH_ESC 
#if defined(__C128__) || defined(__C64__) || defined(__PET__) || defined(__VIC20__)
		&& key != CH_STOP 
#endif
		&& key != CH_ENTER)
	{
		if( count < length &&
			(
				(key >= 32 && key <= 95) ||
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
		else if(
#if defined(__C128__) || defined(__C64__) || defined(__PET__) || defined(__VIC20__)
			key == CH_DEL 
#else
			key == 127
#endif
			&& count > 0)
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

unsigned  writeYesNo(
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
