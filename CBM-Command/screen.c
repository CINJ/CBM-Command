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

// Prepares the screen 
void setupScreen(void)
{
	clrscr();

	textcolor(COLOR_YELLOW);
	bgcolor(COLOR_BLACK);
	bordercolor(COLOR_BLACK);

	return;
}

void saveScreen(void)
{
	int vicRegister = 53272;
	int screenMemoryStart;
	int colorMemoryStart = 0xD800;

#ifdef __C128__
	if(size_x > 40)
	{
		copyVdcScreen(0x00, 0x10);
		return;
	}
	else
	{
		vicRegister = 2604;
	}
#endif

	screenMemoryStart = ((PEEK(vicRegister) & 0xF0) >> 4) * 1024;

	memcpy(SCREEN_BUFFER, screenMemoryStart, 1000);
	memcpy(COLOR_BUFFER, colorMemoryStart, 1000);
}

void retrieveScreen(void)
{
	int vicRegister = 53272;
	int screenMemoryStart;
	int colorMemoryStart = 0xD800;

#ifdef __C128__
	if(size_x > 40)
	{
		copyVdcScreen(0x10, 0x00);
		return;
	}
	else
	{
		vicRegister = 2604;
	}
#endif

	screenMemoryStart = ((PEEK(vicRegister) & 0xF0) >> 4) * 1024;
	memcpy(screenMemoryStart, SCREEN_BUFFER, 1000);
	memcpy(colorMemoryStart, COLOR_BUFFER, 1000);
}

void writeStatusBar(
	unsigned char message[], 
	unsigned char return_x, 
	unsigned char return_y)
{
	unsigned char oldColor;

	oldColor = textcolor(COLOR_GRAY3);
	revers(TRUE);

	gotoxy(0, size_y - 1);
	cputs(blank_line);

	gotoxy(0, size_y - 1);
	cputs(message);
	
	revers(FALSE);

	gotoxy(return_x, return_y);
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
	unsigned oldReverse;
	unsigned char line[39];
	unsigned char spcs[39];
	int i;
	
	for(i=0; i<w-1; i++)
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
	for(i=y+1; i<y+h; i++)
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
	int i, okLeft, cancelLeft;
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

		for(i=0; i<h; i++)
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
	unsigned char x, y, h = 5, w = 23;
	unsigned char buffer[39];

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