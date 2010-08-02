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
#include <string.h>
#include <conio.h>
#include <_heap.h>

#include "Configuration.h"
#include "constants.h"
#include "drives.h"
#include "globals.h"
#include "globalInput.h"
#include "menus.h"
#include "screen.h"
#include "input.h"
#include "PlatformSpecific.h"

#if defined(__C128__)
#include <c128.h>
#endif

/* CBM-Command Main Function
 * --------------------------
 * - Payton Byrd 
 * --------------------------
 * Prepares application and 
 * provides main loop.
 */
int main(void)
{
#if defined(__VIC20__)
	//_heapptr = _heaporg = 0xA100;
	//_heapend = 0xBFFF;
#endif

#if defined(__C128__)
	// Set screen to 80 columns.
	// 40 columns is not supported
	// on the C= 128 due memory 
	// constraints.
	videomode(VIDEOMODE_80COL);

	// Set system to 2mhz
	fast();
#endif

	// Prepares the application
	initialize();

	// Loads configuration from
	// drive that the application
	// was started from.
#ifndef __PET__
	load();
#endif

	// Initializes the disk drives
	// which sets up structures for
	// the disk panels.
	initializeDrives();

	// Prepares the screen for use.
	setupScreen();

	// Writes the function key bar
	// to the screen.
	writeMenuBar();

	// Reads the directory of the 
	// default drive and displays
	// it in the left panel.
	rereadSelectedPanel();
#ifndef __VIC20__
	writeStatusBarf("CBM-Command Build: %s %s", __DATE__, __TIME__);
#else
	writeStatusBarf("%s %s", __DATE__, __TIME__);
#endif

	// Main Loop
	while(TRUE)
	{
		// Reads the keyboard
		// and exits the application
		// when necessary.
		readKeyboard();
	}

	// We should never get here,
	// but just in case we do...
	return EXIT_SUCCESS;
}
