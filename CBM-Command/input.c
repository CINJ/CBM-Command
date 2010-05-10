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

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "drives.h"
#include "globals.h"
#include "input.h"
#include "menus.h"
#include "screen.h"

void __fastcall__ readKeyboard(void)
{
	unsigned char key;
//	unsigned char buffer[39];

	key = cgetc();

	switch((int)key)
	{
	case KEY_SH_SPACE: case KEY_SH_RETURN:
	case KEY_F3:
		selectCurrentFile();
		break;
	case CH_CURS_UP:
		moveSelectorUp(selectedPanel);
		break;
	case CH_CURS_DOWN:
		moveSelectorDown(selectedPanel);
		break;
	case CH_CURS_LEFT:
		if(selectedPanel == &rightPanelDrive
			&& leftPanelDrive.drive != NULL
			&& arePanelsOn)
		{
			selectedPanel = &leftPanelDrive;
			writeSelectorPosition(&leftPanelDrive, '>');
			writeSelectorPosition(&rightPanelDrive, ' ');
		}
		break;
	case CH_CURS_RIGHT:
		if(selectedPanel == &leftPanelDrive
			&& rightPanelDrive.drive != NULL
			&& arePanelsOn)
		{
			selectedPanel = &rightPanelDrive;
			writeSelectorPosition(&leftPanelDrive, ' ');
			writeSelectorPosition(&rightPanelDrive, '>');
		}
		break;
	case KEY_SH_PLUS:
		enterDirectory(selectedPanel);
		break;
	case KEY_SH_MINUS:
		leaveDirectory(selectedPanel);
		break;
	case 188: // C= C - Command Menu
		writeMenu(command);
		break;
	case 182: // C= L - Left Menu
		writeMenu(left);
		break;
	case 178: // C= R - Right Menu
		writeMenu(right);
		break;
	case 187: // C= F - File Menu
		writeMenu(file);
		break;
	case 185: // C= O - Options Menu
		writeMenu(options);
		break;
	case HK_REREAD_LEFT:
		rereadDrivePanel(left);
		break;
	case HK_REREAD_RIGHT:
		rereadDrivePanel(right);
		break;
	case HK_DRIVE_LEFT:
		writeDriveSelectionPanel(left);
		break;
	case HK_DRIVE_RIGHT:
		writeDriveSelectionPanel(right);
		break;
	case HK_SWAP_PANELS:
		swapPanels();
		break;
	case HK_TOGGLE_PANELS:
		togglePanels();
		break;
	case HK_ABOUT:
		writeAboutBox();
		break;
	case HK_HELP_128:
	case HK_HELP:
	case KEY_F1:
		writeHelpPanel();
		break;
	case HK_QUIT:
	case KEY_F2:
		quit();
		break;
#ifdef __C128__
	case HK_GO64:
		go64();
		break;
#endif
	case HK_COPY:
	case KEY_F5:
		copyFiles();
		break;
	case HK_RENAME:
	case KEY_F6:
		renameFile();
		break;
	case HK_DELETE:
	case KEY_F8:
		deleteFiles();
		break;
	case HK_FILE_INFO:
		writeFileInfoPanel();
		break;
	case HK_MAKE_DIRECTORY:
	case KEY_F7:
		makeDirectory();
		break;
	default:
		writeStatusBarf("%c", key);
	}
}

unsigned char __fastcall__ waitForEnterEsc(void)
{
	unsigned char key = 0;

	while(key != CH_ESC
		&& key != CH_STOP
		&& key != CH_ENTER)
	{
		key = cgetc();
	}
	
	return key;
}