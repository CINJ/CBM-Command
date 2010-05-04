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

#include <cbm.h>
#include <conio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "drives.h"
#include "globals.h"
#include "input.h"
#include "screen.h"
#include "menus.h"

unsigned char drivesBuffer[80];

struct drive_status drives[12] =
{
	{ 8, "", FALSE, FALSE },	// 0
	{ 9, "", FALSE, FALSE },	// 1
	{ 10, "", FALSE, FALSE },	// 2
	{ 11, "", FALSE, FALSE },	// 3
	{ 12, "", FALSE, FALSE },	// 4
	{ 13, "", FALSE, FALSE },	// 5
	{ 14, "", FALSE, FALSE },	// 6
	{ 15, "", FALSE, FALSE },	// 7
	{ 16, "", FALSE, FALSE },	// 8
	{ 17, "", FALSE, FALSE },	// 9
	{ 18, "", FALSE, FALSE },	// 10
	{ 19, "", FALSE, FALSE },	// 11
};

unsigned areDrivesInitialized = FALSE;
struct panel_drive leftPanelDrive; 
struct panel_drive rightPanelDrive;
struct panel_drive *selectedPanel;

unsigned char currentLeft = 0;
unsigned char currentRight = 0;


int currentLeftIndex = 0;
int currentRightIndex = 0;
enum menus currentPanel = left;

void __fastcall__ initializeDrives(void)
{
	if(!areDrivesInitialized)
	{
		leftPanelDrive.currentIndex = 0;
		leftPanelDrive.displayStartAt = 0;
		leftPanelDrive.position = left;

		rightPanelDrive.currentIndex = 0;
		rightPanelDrive.displayStartAt = 0;
		rightPanelDrive.position = right;

		areDrivesInitialized = TRUE;
		selectedPanel = &leftPanelDrive;
	}
}

int __fastcall__ getDriveStatus(
	struct drive_status *drive)
{
	int result;
	int size;
	//unsigned char buffer[39];
	unsigned char dr;
	dr = drive->drive;

	if(dr < 8 || dr > 19)
	{
		//sprintf(drive->message, "Cannot open drive %d", dr);
		//writeStatusBar(drive->message, wherex(), wherey());
		return -1;
	}

	result = cbm_open(15, dr, 15, "");

	if(_oserror == 0)
	{
		//sprintf(buffer, "Opened drive %d", dr);
		//writeStatusBar(buffer, wherex(), wherey());
	}
	else
	{
		cbm_close(15);

		//sprintf(buffer, "_oserror = %d, closed channel.", _oserror);
		//writeStatusBar(buffer, wherex(), wherey());

		return -1;
	}

	if(result == 0 && _oserror == 0)
	{
		size = cbm_read(15, drive->message, 38);
		if(size >=0) drive->message[size] = '\0';
		else drive->message[0] = '\0';
		
		if(strlen(drive->message) > 0)
		{
			cbm_write(15, "uj", 2); 

			size = cbm_read(15, drive->message, 38);
			if(size >=0) drive->message[size] = '\0';
			else drive->message[0] = '\0';
		}

		cbm_close(15);

		return size;
	}

	return result;
}

void __fastcall__ listDrives(enum menus menu)
{
	unsigned char x, y, i;
	unsigned char status, current, original, key;
	unsigned selected = FALSE;
	const unsigned char h = 17;
	const unsigned char w = 39;
	unsigned char message[40];

	x = getCenterX(w);
	y = getCenterY(h);

	writePanel(TRUE, FALSE,
		COLOR_GRAY3, 
		x, y, h, w,
		"Drives", NULL, NULL);

	textcolor(COLOR_WHITE);

	current = 0;

	for(i=0; i<12; i++)
	{
		if( 
			(currentLeft > 0 && drives[i].drive == currentLeft && menu == left) ||
			(currentRight > 0 && drives[i].drive == currentRight && menu == right)
		)
		{
			revers(TRUE);
			original = current = i;
		}

		gotoxy(x + 2, i + 2 + y);
		sprintf(message, "%d", i + 8);
		cputs(message);

		status = checkDrive(2, "UI", i + 8);
		//sprintf(message, "Drive %d returns %d", i + 8, status);
		//writeStatusBar(message, wherex(), wherey());

		gotoxy(x + 5, i + 2 + y);

		if(status !=5)
		{
			getDriveStatus(&(drives[i]));
			cputs(drives[i].message);
		}
		else
		{
			cputs("No device present.");
		}

		revers(FALSE);
	}

	textcolor(COLOR_YELLOW);
	gotoxy(x + 1, y + 15); cputs("Use arrow keys & enter to select drive");
	textcolor(COLOR_RED);

	gotoxy(x + 1, current + 2 + y); cputc('>');

	while(!selected)
	{
		key = cgetc();

		switch((int)key)
		{
		case CH_ESC: 
		case CH_STOP:
			selected = TRUE;
			current = original;
			break;

		case CH_ENTER:
			selected = TRUE;
			break;

		case CH_CURS_UP:
			if(current > 0)
			{
				gotoxy(x + 1, current + 2 + y); cputc(' ');
				current--;
				gotoxy(x + 1, current + 2 + y); cputc('>');
			}
			break;

		case CH_CURS_DOWN:
			if(current < 11)
			{
				gotoxy(x + 1, current + 2 + y); cputc(' ');
				current++;
				gotoxy(x + 1, current + 2 + y); cputc('>');
			}
			break;
		}
	}

	if(menu == left)
	{
		leftPanelDrive.drive = &(drives[current]);
		currentLeft = leftPanelDrive.drive->drive;

		sprintf(message, "Left is now drive %d", currentLeft);
		writeStatusBar(message, wherex(), wherey());
	}
	else
	{
		rightPanelDrive.drive = &(drives[current]);
		currentRight = rightPanelDrive.drive->drive;

		sprintf(message, "Right is now drive %d", currentRight);
		writeStatusBar(message, wherex(), wherey());
	}

	//waitForEnterEsc();
}

int __fastcall__ getDirectory(struct panel_drive *drive)
{
	unsigned char result, dr;
	int counter;
	struct cbm_dirent *currentDE;
	struct dir_node *currentNode, *newNode;

	currentNode = drive->tail;
	while(currentNode != NULL && currentNode->prev != NULL)
	{
		if(currentNode->next != NULL)
			free(currentNode->next);

		currentNode = currentNode->prev;
	}
	if(currentNode != NULL) 
		free(currentNode);

	drive->head = NULL;
	drive->tail = NULL;
	drive->length = 0;

	dr = drive->drive->drive;

	result = cbm_opendir(dr, dr);
	if(result == 0)
	{
		writeStatusBar("Reading directory...", wherex(), wherey());
		counter = 0;
		currentDE = malloc(sizeof(struct cbm_dirent));
		currentNode = malloc(sizeof(struct dir_node));
		currentNode->prev = NULL;
		currentNode->next = NULL;
		drive->head = currentNode;
		drive->tail = currentNode;
		while(!cbm_readdir(dr, currentDE))
		{
			//writeStatusBar(currentDE->name, wherex(), wherey());
			currentNode->dir_entry = currentDE;
			currentDE = malloc(sizeof(struct cbm_dirent));
			newNode = malloc(sizeof(struct dir_node));
			currentNode->next = newNode;
			drive->tail = newNode;
			newNode->prev = currentNode;
			newNode->next = NULL;
			newNode->isSelected = FALSE;
			currentNode = newNode;
			counter++;
		}
		cbm_closedir(dr);
		drive->length = counter;
		writeStatusBar("Finished reading directory.", 
			wherex(), wherey());
	
		drive->currentIndex = 0;
		drive->displayStartAt = 0;

	}

	return counter;
}

void __fastcall__ displayDirectory(
	struct panel_drive *drive)
{
	unsigned char fileType, w = 19, x = 0;
	int i;
	struct dir_node *currentNode;
	unsigned char size[4];

	currentNode = drive->head;

	if(size_x > 40) w=39;
	if(drive->position == right) x=w + 1;
	
	writePanel(TRUE, FALSE, COLOR_GRAY3, x, 1, 21, w, 
		currentNode->dir_entry->name, NULL, NULL);
	
	//textcolor(COLOR_YELLOW);
	
	currentNode = currentNode->next;

	for(i=0; i < drive->displayStartAt; i++)
	{
		currentNode = currentNode->next;
	}

	for(i=1; i + drive->displayStartAt < drive->length; i++)
	{
		if(i+1 == 22) break;
		
		gotoxy(x + 2, i+1);
		
		shortenSize(size, currentNode->dir_entry->size);
		fileType = getFileType(currentNode->dir_entry->type);
		//writeStatusBar(size, wherex(), wherey());

		textcolor(COLOR_YELLOW);
		if(currentNode->isSelected == TRUE)
		{
			//writeStatusBar("Reverse On", wherex(), wherey());
			revers(TRUE);
		}
		else
		{
			//writeStatusBar("Reverse Off", wherex(), wherey());
			revers(FALSE);
		}		
		//waitForEnterEsc();

		sprintf(drivesBuffer, "%c %s %s", 
			fileType, 
			size,
			shortenString(currentNode->dir_entry->name)
			);

		cputs(drivesBuffer);
		currentNode = currentNode->next;

		revers(FALSE);
	}
}

void __fastcall__ writeSelectorPosition(struct panel_drive *panel,
	unsigned char character)
{
	unsigned char x, y;
	y = (panel->currentIndex - panel->displayStartAt) + 2;
	x = (panel == &leftPanelDrive ? 1 : size_x / 2 + 1);
	gotoxy(x, y);
	textcolor(COLOR_RED);
	revers(FALSE);
	cputc(character);
}

void __fastcall__ writeCurrentFilename(struct panel_drive *panel)
{
	struct dir_node *currentDirNode;
	int i;

	if(panel != NULL)
	{
		if(panel->drive != NULL)
		{
			currentDirNode = panel->head;
			for(
				i=0; 
				i<=panel->currentIndex
					&& currentDirNode != NULL; 
				i++)
			{
				currentDirNode = currentDirNode->next;
			}

			if(currentDirNode != NULL)
			{
				writeStatusBar(
					currentDirNode->dir_entry->name,
					wherex(), wherey());
			}
		}
	}
}

void __fastcall__ moveSelectorUp(struct panel_drive *panel)
{
	unsigned char diff;
	unsigned firstPage;
	//unsigned char buffer[79];

	writeSelectorPosition(panel, ' ');
	firstPage = panel->displayStartAt == 0;
	diff = panel->currentIndex - panel->displayStartAt;

	//sprintf(buffer, "fP: %d  diff: %d  dsa: %d  ci: %d  l: %d",
	//	firstPage, diff, panel->displayStartAt, 
	//	panel->currentIndex, panel->length);

	//writeStatusBar(buffer, wherex(), wherey());

	if(!firstPage && diff == 1)
	{
		panel->displayStartAt--;
		panel->currentIndex--;
		displayDirectory(panel);
	}
	else if(diff > 0)
	{
		panel->currentIndex--;
		//displayDirectory(panel);
	}
	
	writeSelectorPosition(panel, '>');
	if(size_x <= 40) writeCurrentFilename(panel);
}

void __fastcall__ moveSelectorDown(struct panel_drive *panel)
{
	const unsigned char offset = 19;
	unsigned char diff;
	unsigned lastPage;
	//unsigned char buffer[79];

	writeSelectorPosition(panel, ' ');

	lastPage = panel->displayStartAt + offset + 2 >= panel->length;
	diff = panel->length - panel->displayStartAt;

	//sprintf(buffer, "lP: %d  diff: %d  dsa: %d  ci: %d  l: %d",
	//	lastPage, diff, panel->displayStartAt, 
	//	panel->currentIndex, panel->length);

	//writeStatusBar(buffer, wherex(), wherey());

	if(!lastPage && diff > offset &&
		((panel->currentIndex - panel->displayStartAt) == offset))
	{
		panel->displayStartAt++;
		panel->currentIndex++;
		displayDirectory(panel);
	}
	else if(lastPage && 
		(panel->currentIndex - panel->displayStartAt) < offset &&
		(panel->currentIndex + 2 + panel->displayStartAt) < panel->length)
	{
		panel->currentIndex++;
	}
	else if(!lastPage)
	{
		panel->currentIndex++;
	}

	if(panel->currentIndex < 0) panel->currentIndex=0;
	writeSelectorPosition(panel, '>');
	if(size_x <= 40) writeCurrentFilename(panel);
}

unsigned char __fastcall__ getFileType(unsigned char type)
{
	switch((int)type)
	{
	case 0: return 'D';
	case 1: return 'S';
	case 2: return 'P';
	case 3: return 'U';
	case 4: return 'R';
	case 5: return 'C';
	case 6: return 'D';
	default: return 'O';
	}
}

void __fastcall__ shortenSize(unsigned char* buffer, unsigned int value)
{
	if(value < 1000)
	{
		sprintf(buffer, "%3d", value);
	}
	else
	{
		sprintf(buffer, "%2dK", value/1024);
	}
}

unsigned char* __fastcall__ shortenString(unsigned char* source)
{
	const int targetLength = 11;
	unsigned char buffer[18];

	if(size_x == 40)
	{
		if(strlen(source) > targetLength)
		{
			strncpy(buffer, source, targetLength - 3);
			buffer[targetLength - 3] = '.';
			buffer[targetLength - 2] = '.';
			buffer[targetLength - 1] = '.';
			buffer[targetLength] = '\0';
		}
		else
		{
			return source;
		}
	}
	else
	{
		return source;
	}

	return buffer;
}

void __fastcall__ selectCurrentFile(void)
{
	int i;
	struct dir_node *currentDirNode;
	//unsigned char buffer[39];
	//unsigned isSelected;

	if(selectedPanel != NULL)
	{
		if(selectedPanel->drive != NULL)
		{
			currentDirNode = selectedPanel->head;
			for(
				i=0; 
				i<=selectedPanel->currentIndex
					&& currentDirNode != NULL; 
				i++)
			{
				currentDirNode = currentDirNode->next;
			}

			if(currentDirNode != NULL)
			{
				if(currentDirNode->isSelected == TRUE)
					currentDirNode->isSelected = FALSE;
				else 
					currentDirNode->isSelected = TRUE;

				displayDirectory(selectedPanel);
				writeSelectorPosition(selectedPanel, '>');
			}
			else
			{
				writeStatusBar("currentDirNode is null!", wherex(), wherey());
			}
		}
		else
		{
			writeStatusBar("No drive selected.", wherex(), wherey());
		}
	}
	else
	{
		writeStatusBar("No panel selected.", wherex(), wherey());
	}
}