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

#ifndef _MENUS_H
#define _MENUS_H

// Menu Globals
extern unsigned char currentMenuX;
extern unsigned char currentMenuLine;
enum menus
{
	left, right, file, command, options
};


// Option Menu Externals
extern char OPTION_MENU_OPTIONS[];
extern const unsigned char OPTION_MENU_OPTIONS_KEY;
extern char OPTION_MENU_SAVE[];
extern const unsigned char OPTION_MENU_SAVE_KEY;
extern const unsigned char OPTION_MENU_COUNT;
extern const unsigned char OPTION_MENU_WIDTH;
extern char* OPTION_MENU_LABELS[2];
extern unsigned char OPTION_MENU_KEYS[2];

// File Menu Externals
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
extern char FILE_MENU_SEND_COMMAND[];
extern const unsigned char FILE_MENU_SEND_COMMAND_KEY;
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

// Drive Menu Externals
extern char DRIVE_MENU_REREAD[];
extern const unsigned char DRIVE_MENU_REREAD_KEY;
extern char DRIVE_MENU_DRIVE[];
extern const unsigned char DRIVE_MENU_DRIVE_KEY;
extern const unsigned char DRIVE_MENU_COUNT;
extern const unsigned char DRIVE_MENU_WIDTH;
extern char* DRIVE_MENU_LABELS[2];
extern unsigned char DRIVE_MENU_KEYS[2];

// Command Menu Externals
extern char COMMAND_MENU_SWAP_PANELS[];
extern const unsigned char COMMAND_MENU_SWAP_PANELS_KEY;
extern char COMMAND_MENU_PANELS_ON_OFF[];
extern const unsigned char COMMAND_MENU_PANELS_ON_OFF_KEY;
extern const unsigned char COMMAND_MENU_COUNT;
extern const unsigned char COMMAND_MENU_WIDTH;
extern char* COMMAND_MENU_LABELS[2];
extern unsigned char COMMAND_MENU_KEYS[2];

// Initialize menus
void __fastcall__ initOptionMenu(void);
void __fastcall__ initFileMenu(void);
void __fastcall__ initDriveMenu(void);
void __fastcall__ initCommandMenu(void);

// Handle menus
void __fastcall__ handleOptionMenu(void);
void __fastcall__ handleFileMenu(void);
void __fastcall__ handleCommandMenu(void);
void __fastcall__ handleDriveMenu(enum menus);

// Menu actions
void __fastcall__ inputCommand(void);
void __fastcall__ executeSelectedFile(void);
void __fastcall__ rereadDrivePanel(enum menus menu);
void __fastcall__ rereadSelectedPanel(void);
void __fastcall__ reloadPanels(void);
void __fastcall__ writeDriveSelectionPanel(enum menus menu);
void __fastcall__ writeAboutBox(void);
void __fastcall__ displayPanels(void);
void __fastcall__ writeMenu(enum menus);
void __fastcall__ writeOptionsPanel(void);
void __fastcall__ saveOptions(void);
void __fastcall__ swapPanels(void);
void __fastcall__ togglePanels(void);
void __fastcall__ writeHelpPanel(void);
void __fastcall__ copyFiles(void);
void __fastcall__ renameFile(void);
void __fastcall__ makeDirectory(void);
void __fastcall__ deleteFiles(void);
void __fastcall__ quit(void);
#ifdef __C128__
void __fastcall__ go64(void);
#endif

// Menu drawing
void __fastcall__ drawFileMenu(unsigned char);
void __fastcall__ drawDriveMenu(unsigned char);
void __fastcall__ drawCommandMenu(unsigned char);
void __fastcall__ drawOptionsMenu(unsigned char);
void __fastcall__ drawMenu(unsigned char, unsigned char, unsigned char, char*[], unsigned char[]);
void __fastcall__ drawMenuLine(unsigned, unsigned char, char*, unsigned char, unsigned char);
void writeMenuBar(void);
#endif