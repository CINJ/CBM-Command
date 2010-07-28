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

#ifndef _INPUT_H
#define _INPUT_H

#include "constants.h"

// Global Hotkeys
#define HK_REREAD_LEFT		KEY_CTRL_E
#define HK_REREAD_RIGHT		KEY_ALT_E	// C=-E
#define HK_DRIVE_LEFT		KEY_CTRL_D
#define HK_DRIVE_RIGHT		KEY_ALT_D	// C=-D
#define HK_TOGGLE_PANELS	KEY_CTRL_T
#define HK_SELECT_ALL		KEY_CTRL_A
#define HK_DESELECT_ALL		KEY_CTRL_S
#define HK_QUIT				95
#define HK_COPY				KEY_CTRL_C
#define HK_RENAME			KEY_CTRL_R
#ifdef __CBM__
#define HK_DELETE			KEY_CTRL('^')
#else
#define HK_DELETE			KEY_CTRL_L
#endif
//#define HK_FILE_INFO		KEY_CTRL_I
#define HK_MAKE_DIRECTORY	KEY_CTRL_K
#ifdef __CBM__
#define HK_TO_TOP			'^'
#define HK_TO_BOTTOM		('^'|0x80)	// SHIFT-^
#else
#define HK_TO_TOP			'{'
#define HK_TO_BOTTOM		'}'
#endif
#ifdef __CBM__
#define HK_PAGE_UP			'+'
#define HK_PAGE_DOWN		'-'
#else
#define HK_PAGE_UP			'['
#define HK_PAGE_DOWN		']'
#endif

#define HK_SELECT			' '

#ifdef __CBM__
#define HK_CREATE_D64		KEY_CTRL_X
#endif

#ifdef __C128__
#define HK_HELP_128			0x84	// HELP key
#define HK_GO64				KEY_CTRL_G
#endif

void readKeyboard(void);

#endif
