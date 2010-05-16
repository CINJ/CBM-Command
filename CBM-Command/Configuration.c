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
#include <cbm.h>
#include <conio.h>
#include <errno.h>
#include <peekpoke.h>

#include "globalInput.h"
#include "globals.h"
#include "screen.h"

unsigned char defaultLeftDrive = 8;
unsigned char defaultRightDrive = 8;

#ifdef __C128__
unsigned char color_background	= COLOR_BLACK;
unsigned char color_border		= COLOR_BLACK;
unsigned char color_selector	= COLOR_WHITE;
unsigned char color_text_borders= COLOR_GRAY3;
unsigned char color_text_menus	= COLOR_WHITE;
unsigned char color_text_files	= COLOR_YELLOW;
unsigned char color_text_status = COLOR_GRAY3;
unsigned char color_text_other	= COLOR_WHITE;
unsigned char color_text_highlight = COLOR_YELLOW;
#else
unsigned char color_background	= COLOR_BLUE;
unsigned char color_border		= COLOR_BLUE;
unsigned char color_selector	= COLOR_WHITE;
unsigned char color_text_borders= COLOR_GRAY2;
unsigned char color_text_menus	= COLOR_GRAY3;
unsigned char color_text_files	= COLOR_GRAY3;
unsigned char color_text_status	= COLOR_GRAY2;
unsigned char color_text_other	= COLOR_GRAY3;
unsigned char color_text_highlight = COLOR_WHITE;
#endif

void __fastcall__ load(void)
{
	unsigned char r, d;
	//unsigned char *buffer;
	//buffer = calloc(11,sizeof(unsigned char));
	d = PEEK(0x00BA);
	cbm_open(15,d,15,"");
#ifdef __C64__
	r = cbm_open(1,d,2,"cbmcmd-cfg.c64,s,r");
#endif
#ifdef __C128__
	r = cbm_open(1,d,2,"cbmcmd-cfg.c128,s,r");
#endif

	if(r == 0)
	{
		r = cbm_read(1, buffer, 11);
		if(r == 11)
		{
			defaultLeftDrive = buffer[0];
			defaultRightDrive = buffer[1];
			color_background = buffer[2];
			color_border = buffer[3];
			color_selector = buffer[4];
			color_text_borders = buffer[5];
			color_text_menus = buffer[6];
			color_text_files = buffer[7];
			color_text_status = buffer[8];
			color_text_other = buffer[9];
			color_text_highlight = buffer[10];
		}
	}
	else
	{
		//free(buffer);
		//buffer = calloc(41, sizeof(unsigned char));
		r = cbm_read(15,buffer,39);
		buffer[r] = '\0';
		writeStatusBar(buffer);
		//free(buffer);
		waitForEnterEsc();
	}

	cbm_close(1);
	cbm_close(15);
}


