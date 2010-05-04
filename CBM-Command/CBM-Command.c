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



int main(void)
{
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



