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
//#include <stdbool.h>
#include <conio.h>

//#include "constants.h"
#include "Configuration.h"
#include "drives.h"
#include "globals.h"
#include "input.h"
#include "menus.h"
#include "globalInput.h"
//#include "screen.h"

void readKeyboard(void)
{
	//char buffer[39];
	char key = cgetc();

	if(key == CH_CURS_DOWN)
	{
		moveSelectorDown(selectedPanel);
	}
	else if(key == CH_CURS_UP)
	{
		moveSelectorUp(selectedPanel);
	}
	else if(key == CH_CURS_LEFT)
	{
		if(selectedPanel == &rightPanelDrive
			&& leftPanelDrive.visible
			/*&& arePanelsOn*/)
		{
			selectedPanel = &leftPanelDrive;
#if size_x < 40
			displayDirectory(selectedPanel);
#endif
			writeCurrentFilename(selectedPanel);
			writeSelectorPosition(& leftPanelDrive, '>');
#if size_x > 22
			writeSelectorPosition(&rightPanelDrive, ' ');
#endif
		}
	}
	else if(key == CH_CURS_RIGHT)
	{
		if(selectedPanel == &leftPanelDrive
#if size_x > 22
			&& rightPanelDrive.visible
#endif
			/*&& arePanelsOn*/)
		{
			selectedPanel = &rightPanelDrive;
#if size_x < 40
			displayDirectory(selectedPanel);
#endif
			writeCurrentFilename(selectedPanel);
			writeSelectorPosition(&rightPanelDrive, '>');
#if size_x > 22
			writeSelectorPosition(& leftPanelDrive, ' ');
#endif
		}
	}
	else if(key == CH_F4 || key == keyMap[KM_REREAD_SELECTED])
	{
		rereadSelectedPanel();
	}
#ifdef __CBM__
	else if(key == keyMap[KM_EXECUTE_SELECTED])
	{
		executeSelectedFile();
	}
#endif
	else if(key == CH_F3 || key == keyMap[KM_DRIVE_CURRENT])
	{
		selectCurrentPanelDrive();
	}
	else if(key == keyMap[KM_SELECT])
	{
		selectCurrentFile();
		moveSelectorDown(selectedPanel);
	}
	else if(key == keyMap[KM_ENTER_DIRECTORY])
	{
		enterDirectory(selectedPanel);
	}
	else if(key == keyMap[KM_LEAVE_DIRECTORY])
	{
		leaveDirectory(selectedPanel);
	}
	else if(key == keyMap[KM_REREAD_LEFT])
	{
		rereadDrivePanel(left);
	}
	else if(key == keyMap[KM_REREAD_RIGHT])
	{
		rereadDrivePanel(right);
	}
	else if(key == keyMap[KM_DRIVE_LEFT])
	{
		writeDriveSelectionPanel(left);
	}
	else if(key == keyMap[KM_DRIVE_RIGHT])
	{
		writeDriveSelectionPanel(right);
	}
	else if(key == keyMap[KM_SELECT_ALL])
	{
		selectAllFiles(selectedPanel, 0xFF);
	}
	else if(key == keyMap[KM_DESELECT_ALL])
	{
		selectAllFiles(selectedPanel, 0x00);
	}
	else if(
		key == CH_F1 ||
#ifdef __C128__
		key == HK_HELP_128 ||
#endif
		key == keyMap[KM_HELP])
	{
		writeHelpPanel();
	}
	else if(key == CH_F2 || key == keyMap[KM_QUIT])
	{
		quit();
	}
	else if(key == CH_F5 || key == keyMap[KM_COPY])
	{
		copyFiles();
	}
	else if(key == CH_F6 || key == keyMap[KM_RENAME])
	{
		renameFile();
	}
	else if(key == CH_F8 || key == keyMap[KM_DELETE])
	{
		deleteFiles();
	}
	else if(key == keyMap[KM_DRIVE_COMMAND])
	{
		inputCommand();
	}
	else if(key == CH_F7 || key == keyMap[KM_MAKE_DIRECTORY])
	{
		makeDirectory();
	}
	else if(key == keyMap[KM_TO_TOP])
	{
		moveTop(selectedPanel);
	}
	else if(key == keyMap[KM_TO_BOTTOM])
	{
		moveBottom(selectedPanel);
	}
	else if(key == keyMap[KM_PAGE_UP])
	{
		movePageUp(selectedPanel);
	}
	else if(key == keyMap[KM_PAGE_DOWN])
	{
		movePageDown(selectedPanel);
	}
#if defined(__CBM__)
	else if(key == keyMap[KM_WRITE_D64])
	{
		writeDiskImage();
	}
	else if(key == keyMap[KM_CREATE_D64])
	{
		createDiskImage();
	}
#endif
#ifdef __C128__
	else if(key == HK_GO64)
	{
		go64();
	}
#endif
	else if(key == keyMap[KM_COPY_DISK])
	{
		copyDisk();
	}
}
