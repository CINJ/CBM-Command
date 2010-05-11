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

#ifndef _INPUT_H
#define _INPUT_H

// Global Hotkeys
#define HK_REREAD_LEFT		0x05	// CTRL-E
#define HK_REREAD_RIGHT		0xB1	// C=-E
#define HK_DRIVE_LEFT		0x04	// CTRL-D
#define HK_DRIVE_RIGHT		0xAC	// C=-D
#define HK_SWAP_PANELS		0x17	// CTRL-W
#define HK_TOGGLE_PANELS	0x14	// CTRL-T
#define HK_ABOUT			0x01	// CTRL-A
#define HK_HELP_128			0x84	// HELP
#define HK_QUIT				0x15	// CTRL-U
#define HK_GO64				0x07	// CTRL-G
#define HK_TOGGLE_4080		0x0F	// CTRL-O
#define HK_COPY				0x03	// CTRL-C
#define HK_RENAME			0x12	// CTRL-R
#define HK_DELETE			0x1E	// CTRL-^
#define HK_FILE_INFO		0x09	// CTRL-I
#define HK_MAKE_DIRECTORY	0x0B	// CTRL-K

#define KEY_AT				0x40	// @
#define KEY_SH_SPACE		0xA0
#define KEY_SH_RETURN		0x8D
#define KEY_F1				0x85
#define KEY_F3				0x86
#define KEY_F5				0x87
#define KEY_F7				0x88
#define KEY_F2				0x89
#define KEY_F4				0x8A
#define KEY_F6				0x8B
#define KEY_F8				0x8C
#define KEY_SH_PLUS			0xDB
#define KEY_SH_MINUS		0xDD

void __fastcall__ readKeyboard(void);
unsigned char __fastcall__ waitForEnterEsc(void);
#endif