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


//// Option Menu Externals
//extern char OPTION_MENU_OPTIONS[];
//extern const unsigned char OPTION_MENU_OPTIONS_KEY;
//
//extern const unsigned char OPTION_MENU_COUNT;
//extern const unsigned char OPTION_MENU_WIDTH;
//extern char* OPTION_MENU_LABELS[1];
//extern unsigned char OPTION_MENU_KEYS[1];
//
//// File Menu Externals
//extern char FILE_MENU_ABOUT[];
//extern const unsigned char FILE_MENU_ABOUT_KEY;
//extern char FILE_MENU_HELP[];
//extern const unsigned char FILE_MENU_HELP_KEY;
//extern char FILE_MENU_COPY[];
//extern const unsigned char FILE_MENU_COPY_KEY;
//extern char FILE_MENU_RENAME[];
//extern const unsigned char FILE_MENU_RENAME_KEY;
//extern char FILE_MENU_MAKE_DIR[];
//extern const unsigned char FILE_MENU_MAKE_DIR_KEY;
//extern char FILE_MENU_DELETE[];
//extern const unsigned char FILE_MENU_DELETE_KEY;
//extern char FILE_MENU_SEND_COMMAND[];
//extern const unsigned char FILE_MENU_SEND_COMMAND_KEY;
//extern char FILE_MENU_QUIT[];
//extern const unsigned char FILE_MENU_QUIT_KEY;
//#ifdef __C128__
//extern char FILE_MENU_GO64[];
//extern const unsigned char FILE_MENU_GO64_KEY;
//#endif
//extern const unsigned char FILE_MENU_COUNT;
//extern const unsigned char FILE_MENU_WIDTH;
//#ifdef __C128__
//extern char* FILE_MENU_LABELS[9];
//extern unsigned char FILE_MENU_KEYS[9];
//#else
//extern char* FILE_MENU_LABELS[8];
//extern unsigned char FILE_MENU_KEYS[8];
//#endif
//
//// Drive Menu Externals
//extern char DRIVE_MENU_REREAD[];
//extern const unsigned char DRIVE_MENU_REREAD_KEY;
//extern char DRIVE_MENU_DRIVE[];
//extern const unsigned char DRIVE_MENU_DRIVE_KEY;
//extern const unsigned char DRIVE_MENU_COUNT;
//extern const unsigned char DRIVE_MENU_WIDTH;
//extern char* DRIVE_MENU_LABELS[2];
//extern unsigned char DRIVE_MENU_KEYS[2];
//
//// Command Menu Externals
//extern char COMMAND_MENU_SWAP_PANELS[];
//extern const unsigned char COMMAND_MENU_SWAP_PANELS_KEY;
//extern char COMMAND_MENU_PANELS_ON_OFF[];
//extern const unsigned char COMMAND_MENU_PANELS_ON_OFF_KEY;
//extern const unsigned char COMMAND_MENU_COUNT;
//extern const unsigned char COMMAND_MENU_WIDTH;
//extern char* COMMAND_MENU_LABELS[2];
//extern unsigned char COMMAND_MENU_KEYS[2];
//
//// Initialize menus
//void  initOptionMenu(void);
//void  initFileMenu(void);
//void  initDriveMenu(void);
//void  initCommandMenu(void);
//
//// Handle menus
//void  handleOptionMenu(void);
//void  handleFileMenu(void);
//void  handleCommandMenu(void);
//void  handleDriveMenu(enum menus);

// Menu actions
void  inputCommand(void);
void  executeSelectedFile(void);
void  rereadDrivePanel(enum menus menu);
void  rereadSelectedPanel(void);
void  reloadPanels(void);
void  writeDriveSelectionPanel(enum menus menu);
void  writeAboutBox(void);
void  displayPanels(void);
void  writeMenu(enum menus);
void  writeOptionsPanel(void);
void  saveOptions(void);
void  swapPanels(void);
void  togglePanels(void);
void  writeHelpPanel(void);
void  copyFiles(void);
void  renameFile(void);
void  makeDirectory(void);
void  deleteFiles(void);
void  writeD64(void);
void  createD64(void);
void  quit(void);
#ifdef __C128__
void  go64(void);
#endif

// Menu drawing
void  drawFileMenu(unsigned char);
void  drawDriveMenu(unsigned char);
void  drawCommandMenu(unsigned char);
void  drawOptionsMenu(unsigned char);
void  drawMenu(unsigned char, unsigned char, unsigned char, char*[], unsigned char[]);
void  drawMenuLine(unsigned, unsigned char, char*, unsigned char, unsigned char);
void writeMenuBar(void);
#endif