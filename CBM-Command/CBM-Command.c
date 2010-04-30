#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "constants.h"
#include "drives.h"
#include "AssemblerMethods.h"
#include "globals.h";
#include "menus.h";
#include "screen.h";
#include "input.h";
#include "PlatformSpecific.h";

#if defined(__C128__)
#include <c128.h>
#endif

void initialize(void);

int main(void)
{
	unsigned char i;
	unsigned char message[39];

#if defined(__C128__)
	// For testing only.  
	// Will remove for actual release.
	//videomode(VIDEOMODE_80COL);
	//fast();
#endif

	initialize();
	setupScreen();
	writeMenuBar();

	sprintf(message, 
			SCREEN_SIZE_FORMAT, 
			size_x, size_y);

	//writeStatusBar(message, 0, 10);
	gotoxy(0,1); cputs(message);

		
	while(TRUE)
	{
		readKeyboard();
	}

#ifdef __C128__
#endif

	return EXIT_SUCCESS;
}

// Obtains the screen size and sets up global
// strings as necessary.
void initialize()
{
#if defined(__C128__)
	getScreenSize(&size_x, &size_y);
#else
	screensize(&size_x, &size_y);
#endif

	strncpy(blank_line, SPACES, size_x);
	blank_line[size_x] = '\0';


}

