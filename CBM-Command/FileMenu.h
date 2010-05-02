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

#ifndef _FILEMENU_H
#define _FILEMENU_H

extern char FILE_MENU_ABOUT[];
extern const unsigned char FILE_MENU_ABOUT_KEY;

extern char FILE_MENU_HELP[];
extern const unsigned char FILE_MENU_HELP_KEY;

extern char FILE_MENU_COPY[];
extern const unsigned char FILE_MENU_COPY_KEY;

extern char FILE_MENU_RENAME[];
extern const unsigned char FILE_MENU_RENAME_KEY;

extern char FILE_MENU_MAKE_DIR[];
extern const unsigned char FILE_MENU_MAKE_DIR_KEY;

extern char FILE_MENU_DELETE[];
extern const unsigned char FILE_MENU_DELETE_KEY;

extern char FILE_MENU_FILE_INFO[];
extern const unsigned char FILE_MENU_FILE_INFO_KEY;

extern char FILE_MENU_QUIT[];
extern const unsigned char FILE_MENU_QUIT_KEY;

#ifdef __C128__
extern char FILE_MENU_GO64[];
extern const unsigned char FILE_MENU_GO64_KEY;
#endif

extern const unsigned char FILE_MENU_COUNT;

extern const unsigned char FILE_MENU_WIDTH;

#ifdef __C128__
extern char* FILE_MENU_LABELS[9];
extern unsigned char FILE_MENU_KEYS[9];
#else
extern char* FILE_MENU_LABELS[8];
extern unsigned char FILE_MENU_KEYS[8];
#endif

void initFileMenu(void);
void handleFileMenu();
void __fastcall__ writeAboutBox(void);
#endif