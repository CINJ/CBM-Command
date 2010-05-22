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

#if defined(__C128__) || defined(__C64__)
#include <cbm.h>
#endif
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "drives.h"
#include "globals.h"
#include "input.h"
#include "menus.h"
#include "screen.h"


//char* COMMAND_MENU_LABELS[2];
//unsigned char COMMAND_MENU_KEYS[2];
//
//void  initCommandMenu(void)
//{
//	if(!isInitialized)
//	{
//		COMMAND_MENU_LABELS[0] = COMMAND_MENU_SWAP_PANELS;
//		COMMAND_MENU_LABELS[1] = COMMAND_MENU_PANELS_ON_OFF;
//
//		COMMAND_MENU_KEYS[0] = COMMAND_MENU_SWAP_PANELS_KEY;
//		COMMAND_MENU_KEYS[1] = COMMAND_MENU_PANELS_ON_OFF_KEY;
//
//		isInitialized = TRUE;
//	}
//}
//
//void  handleCommandMenu(void)
//{
//	unsigned char key;
//	unsigned handleKeys = TRUE;
//	
//	while(handleKeys)
//	{
//		key = cgetc();
//		handleKeys = FALSE;
//		switch((int)key)
//		{
//#ifdef __C128__
//		case CH_ESC:
//#endif
//		case CH_STOP:
//			retrieveScreen();
//			writeStatusBarf("Escaping menu...");
//			return;
//			break;
//
//		case CH_CURS_UP:
//			if(currentMenuLine == 0) currentMenuLine = COMMAND_MENU_COUNT - 1;
//			else currentMenuLine--;
//			retrieveScreen();
//			drawCommandMenu(currentMenuX);
//			handleKeys = TRUE;
//			break;
//
//		case CH_CURS_DOWN:
//			if(currentMenuLine == COMMAND_MENU_COUNT - 1) currentMenuLine = 0;
//			else currentMenuLine++;
//			retrieveScreen();
//			drawCommandMenu(currentMenuX);
//			handleKeys = TRUE;
//			break;
//
//		case CH_CURS_LEFT:
//			retrieveScreen();
//			writeMenu(options);
//			return;
//			break;
//
//		case CH_CURS_RIGHT:
//			retrieveScreen();
//			writeMenu(right);
//			return;
//			break;
//
//		case CH_ENTER:
//			key = COMMAND_MENU_KEYS[currentMenuLine];
//
//		default:
//			if(key == COMMAND_MENU_SWAP_PANELS_KEY)
//			{
//				swapPanels();
//			}
//			else if(key == COMMAND_MENU_PANELS_ON_OFF_KEY)
//			{
//				togglePanels();
//			}
//			else
//			{
//				handleKeys = TRUE;
//			}
//			break;
//		}
//	}
//}

void  togglePanels(void)
{
	if(arePanelsOn)
	{
		setupScreen();
		writeMenuBar();
		arePanelsOn = FALSE;
	}
	else
	{
		retrieveScreen();
		displayPanels();
		arePanelsOn = TRUE;
	}
}

void  displayPanels(void)
{
	if(leftPanelDrive.drive != NULL)
	{
		rereadDrivePanel(left);
	}
	if(rightPanelDrive.drive != NULL)
	{
		rereadDrivePanel(right);
	}
}

void  swapPanels(void)
{
	//unsigned char i=0;
	//struct panel_drive tempPanel;
	//
	//for(i=0; i<SLIDING_WINDOW_SIZE; ++i)
	//{
	//	tempPanel.slidingWindow[i].name = NULL;
	//	tempPanel.slidingWindow[i].size = 0u;
	//	tempPanel.slidingWindow[i].type = 0;
	//}

	//tempPanel.drive = leftPanelDrive.drive;
	//tempPanel.header.type = leftPanelDrive.header.type;
	//tempPanel.header.size = leftPanelDrive.header.size;
	//tempPanel.header.name = 
	//	calloc(strlen(tempPanel.header.name), sizeof(unsigned char));

	//strcpy(tempPanel.header.name, leftPanelDrive.header.name);
	//tempPanel.length = leftPanelDrive.length;
	//tempPanel.currentIndex = leftPanelDrive.currentIndex;
	//tempPanel.displayStartAt = leftPanelDrive.displayStartAt;
	//tempPanel.slidingWindowStartAt = leftPanelDrive.slidingWindowStartAt;
	//for(i=0; i<30; ++i)
	//{
	//	if(leftPanelDrive.slidingWindow[i] != NULL)
	//	{
	//		tempPanel.slidingWindow[i].type = 
	//			leftPanelDrive.slidingWindow[i].type;

	//		tempPanel.slidingWindow[i].size = 
	//			leftPanelDrive.slidingWindow[i].size;

	//		if(tempPanel.slidingWindow[i].name != NULL) 
	//			free(tempPanel.slidingWindow[i].name);

	//		tempPanel.slidingWindow[i].name = 
	//			calloc(strlen(leftPanelDrive.slidingWindow[i].name), sizeof(unsigned char));

	//		strcpy(tempPanel.slidingWindow[i].name, 
	//			leftPanelDrive.slidingWindow[i].name);
	//	}
	//	else
	//	{
	//		tempPanel.slidingWindow[i].name = NULL;
	//		tempPanel.slidingWindow[i].size = 0u;
	//		tempPanel.slidingWindow[i].type = 0;
	//	}
	//}

	//leftPanelDrive.drive = rightPanelDrive.drive;
	//leftPanelDrive.header.type = rightPanelDrive.header.type;
	//leftPanelDrive.header.size = rightPanelDrive.header.size;
	//if(leftPanelDrive.header.name != NULL)
	//{
	//	free(leftPanelDrive.header.name);
	//}

	//leftPanelDrive.header.name = 
	//	calloc(strlen(rightPanelDrive.header.name), sizeof(unsigned char));

	//strcpy(leftPanelDrive.header.name, rightPanelDrive.header.name);
	//leftPanelDrive.length = rightPanelDrive.length;
	//leftPanelDrive.currentIndex = rightPanelDrive.currentIndex;
	//leftPanelDrive.displayStartAt = rightPanelDrive.displayStartAt;
	//leftPanelDrive.slidingWindowStartAt = rightPanelDrive.slidingWindowStartAt;
	//for(i=0; i<30; ++i)
	//{
	//	if(rightPanelDrive.slidingWindow[i] != NULL)
	//	{
	//		leftPanelDrive.slidingWindow[i].type = 
	//			rightPanelDrive.slidingWindow[i].type;

	//		leftPanelDrive.slidingWindow[i].size = 
	//			rightPanelDrive.slidingWindow[i].size;

	//		if(leftPanelDrive.slidingWindow[i].name != NULL) 
	//			free(leftPanelDrive.slidingWindow[i].name);

	//		leftPanelDrive.slidingWindow[i].name = 
	//			calloc(strlen(rightPanelDrive.slidingWindow[i].name), sizeof(unsigned char));

	//		strcpy(leftPanelDrive.slidingWindow[i].name, 
	//			rightPanelDrive.slidingWindow[i].name);
	//	}
	//	else
	//	{
	//		leftPanelDrive.slidingWindow[i].name = NULL;
	//		leftPanelDrive.slidingWindow[i].size = 0u;
	//		leftPanelDrive.slidingWindow[i].type = 0;
	//	}
	//}

	//rightPanelDrive.drive = tempPanel.drive;
	//rightPanelDrive.header.type = tempPanel.header.type;
	//rightPanelDrive.header.size = tempPanel.header.size;
	//if(rightPanelDrive.header.name != NULL)
	//{
	//	free(rightPanelDrive.header.name);
	//}

	//if(tempPanel.header.name != NULL)
	//{
	//	rightPanelDrive.header.name = 
	//		calloc(strlen(tempPanel.header.name), sizeof(unsigned char));
	//	strcpy(rightPanelDrive.header.name, tempPanel.header.name);
	//}
	//else
	//{
	//	rightPanelDrive.header.name = NULL;
	//}
	//rightPanelDrive.length = tempPanel.length;
	//rightPanelDrive.currentIndex = tempPanel.currentIndex;
	//rightPanelDrive.displayStartAt = tempPanel.displayStartAt;
	//rightPanelDrive.slidingWindowStartAt = tempPanel.slidingWindowStartAt;
	//for(i=0; i<30; ++i)
	//{
	//	if(tempPanel.slidingWindow[i] != NULL)
	//	{
	//		rightPanelDrive.slidingWindow[i].type = 
	//			tempPanel.slidingWindow[i].type;

	//		rightPanelDrive.slidingWindow[i].size = 
	//			tempPanel.slidingWindow[i].size;

	//		if(rightPanelDrive.slidingWindow[i].name != NULL) 
	//			free(rightPanelDrive.slidingWindow[i].name);

	//		rightPanelDrive.slidingWindow[i].name = 
	//			calloc(strlen(tempPanel.slidingWindow[i].name), sizeof(unsigned char));
	//		strcpy(rightPanelDrive.slidingWindow[i].name, 
	//			tempPanel.slidingWindow[i].name);
	//	}
	//	else
	//	{
	//		rightPanelDrive.slidingWindow[i].name = NULL;
	//		rightPanelDrive.slidingWindow[i].size = 0u;
	//		rightPanelDrive.slidingWindow[i].type = 0;
	//	}
	//}
	//			
	//setupScreen();
	//writeMenuBar();
	//displayPanels();
	//arePanelsOn = TRUE;
	retrieveScreen();
	writeStatusBar("Swap Panels is being removed.  Sorry.");
}