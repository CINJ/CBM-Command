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

//#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

//#include "constants.h"
#include "drives.h"
#include "globals.h"
#include "input.h"
#include "menus.h"
#include "globalInput.h"
//#include "screen.h"

void readKeyboard(void)
{
	//char buffer[39];
	//char key = cgetc();

	switch(cgetc())
	{
	case CH_F4:
		rereadSelectedPanel();
		break;
//#ifdef __CBM__
//	case KEY_SH_RETURN:
//		executeSelectedFile();
//		break;
//#endif
	case CH_F3:
		selectCurrentPanelDrive();
		break;
	case HK_SELECT:
		selectCurrentFile();
		break; // don't fall through -- yet
	case CH_CURS_DOWN:
		moveSelectorDown(selectedPanel);
		break;
	case CH_CURS_UP:
		moveSelectorUp(selectedPanel);
		break;
	case CH_CURS_LEFT:
		if(selectedPanel == &rightPanelDrive
			&& leftPanelDrive.visible
			&& arePanelsOn)
		{
			selectedPanel = &leftPanelDrive;
#ifdef __VIC20__
			displayDirectory(selectedPanel);
#endif
			writeCurrentFilename(selectedPanel);
			writeSelectorPosition(&leftPanelDrive, '>');
#ifndef __VIC20__
			writeSelectorPosition(&rightPanelDrive, ' ');
#endif
		}
		break;
	case CH_CURS_RIGHT:
		if(selectedPanel == &leftPanelDrive
#ifndef __VIC20__
			&& rightPanelDrive.visible
#endif
			&& arePanelsOn)
		{
			selectedPanel = &rightPanelDrive;
#ifdef __VIC20__
			displayDirectory(selectedPanel);
#endif
			writeCurrentFilename(selectedPanel);
			writeSelectorPosition(&rightPanelDrive, '>');
#ifndef __VIC20__
			writeSelectorPosition(&leftPanelDrive, ' ');
#endif
		}
		break;
#ifdef __CBM__
	case KEY_SH_PLUS:
		enterDirectory(selectedPanel);
		break;
	case KEY_SH_MINUS:
		leaveDirectory(selectedPanel);
		break;
	//case 188: // C= C - Command Menu
	//	writeMenu(command);
	//	break;
	//case 182: // C= L - Left Menu
	//	writeMenu(left);
	//	break;
	//case 178: // C= R - Right Menu
	//	writeMenu(right);
	//	break;
	//case 187: // C= F - File Menu
	//	writeMenu(file);
	//	break;
	//case 185: // C= O - Options Menu
	//	writeMenu(options);
	//	break;
#endif
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
	//case HK_TOGGLE_PANELS:
	//	togglePanels();
	//	break;
	case HK_SELECT_ALL:
		selectAllFiles(selectedPanel, true);
		break;
	case HK_DESELECT_ALL:
		selectAllFiles(selectedPanel, false);
		break;
#ifdef __C128__
	case HK_HELP_128:
#endif
	case CH_F1:
		writeHelpPanel();
#ifdef __VIC20__
		rereadSelectedPanel();
#endif
		break;
#ifdef __CBM__
	case HK_QUIT:
		quit(FALSE);
		break;
#endif
	case CH_F2:
		quit(TRUE);
		break;
#ifdef __C128__
	case HK_GO64:
		go64();
		break;
#endif
	case HK_COPY:
	case CH_F5:
		copyFiles();
		break;
	case HK_RENAME:
	case CH_F6:
		renameFile();
		break;
//	case HK_DELETE:
	case CH_F8:
		deleteFiles();
		break;
//#ifdef __C64__
	//case HK_FILE_INFO:
	//	writeFileInfoPanel();
	//	break;
//#endif
	case KEY_AT:
		inputCommand();
		break;
#ifdef __CBM__
	case HK_MAKE_DIRECTORY:
#endif
	case CH_F7:
		makeDirectory();
		break;
	case HK_TO_TOP:
		moveTop(selectedPanel);
		break;
	case HK_TO_BOTTOM:
		moveBottom(selectedPanel);
		break;
	case HK_PAGE_UP:
		movePageUp(selectedPanel);
		break;
	case HK_PAGE_DOWN:
		movePageDown(selectedPanel);
		break;
//#ifndef __VIC20__
	case KEY_SH_SPACE:
		writeD64();
		break;
	case HK_CREATE_D64:
		createD64();
		break;
//#endif
	default:
		//writeStatusBarf("%c", key);
		break;
	}
}
