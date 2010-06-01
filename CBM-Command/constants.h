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

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

/* System BOOLEAN Values */
#define TRUE 1
#define FALSE 0

/* Drive Constants */
#define SLIDING_WINDOW_SIZE 30		// 30 directory entries are cached
#define COPY_BUFFER_SIZE	1018	// The data of 4 blocks

/* Keyboad Constants */
#define KEY_AT				'@'	// @
#if defined(__C128__) || defined(__C64__)
#define KEY_F1				0x85
#define KEY_F3				0x86
#define KEY_F5				0x87
#define KEY_F7				0x88
#define KEY_F2				0x89
#define KEY_F4				0x8A
#define KEY_F6				0x8B
#define KEY_F8				0x8C

#define KEY_SH_SPACE		0xA0
#define KEY_SH_RETURN		0x8D
#define KEY_SH_PLUS			0xDB
#define KEY_SH_MINUS		0xDD
#define KEY_ALT_D			0xAC
#define KEY_ALT_E			0xB1
#endif
#if defined(__PET__)
#define KEY_F1				0x21
#define KEY_F3				0x23
#define KEY_F5				0x25
#define KEY_F7				0x27
#define KEY_F2				0x22
#define KEY_F4				0x24
#define KEY_F6				0x26
#define KEY_F8				0x28

#define KEY_SH_SPACE		0xA0
#define KEY_SH_RETURN		0x8D
#define KEY_SH_PLUS			0xDB
#define KEY_SH_MINUS		0xDD
#define KEY_ALT_D			0xAC
#define KEY_ALT_E			0xB1
#endif

#define KEY_CTRL_A			0x01
#define KEY_CTRL_B			0x02
#define KEY_CTRL_C			0x03
#define KEY_CTRL_D			0x04
#define KEY_CTRL_E			0x05
#define KEY_CTRL_F			0x06
#define KEY_CTRL_G			0x07
#define KEY_CTRL_H			0x08
#define KEY_CTRL_I			0x09
#define KEY_CTRL_J			0x0A
#define KEY_CTRL_K			0x0B
#define KEY_CTRL_L			0x0C
#define KEY_CTRL_M			0x0D
#define KEY_CTRL_N			0x0E
#define KEY_CTRL_O			0x0F
#define KEY_CTRL_P			0x10
#define KEY_CTRL_Q			0x11
#define KEY_CTRL_R			0x12
#define KEY_CTRL_S			0x13
#define KEY_CTRL_T			0x14
#define KEY_CTRL_U			0x15
#define KEY_CTRL_V			0x16
#define KEY_CTRL_W			0x17
#define KEY_CTRL_X			0x18
#define KEY_CTRL_Y			0x19
#define KEY_CTRL_Z			0x1A

#endif