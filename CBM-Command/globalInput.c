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

#include "Configuration.h"
#include "constants.h"
#include "globals.h"
#include "screen.h"

unsigned char  waitForEnterEsc(void)
{
	unsigned char key = 0;

	revers(TRUE); 
	textcolor(color_text_other); 
	cputsxy(size_x - 5, 0, "(RET)"); 
	revers(FALSE);

	while(key != CH_ESC
#if defined(__C128__) || defined(__C64__) || defined(__PET__) || defined(__VIC20__)
		&& key != CH_STOP
#endif
		&& key != CH_ENTER)
	{
		key = cgetc();
	}
	
	return key;
}

unsigned char waitForEnterEscf(unsigned char* pattern, ...)
{
	unsigned char buffer[80];
	va_list ap;
	va_start(ap,  pattern);
	vsprintf(buffer, pattern, ap);
	va_end(ap);
	writeStatusBar(buffer);
	return waitForEnterEsc();
}