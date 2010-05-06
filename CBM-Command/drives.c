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

struct drive_status drives[8] =
{
	{ 8, "" },	// 0
	{ 9, "" },	// 1
	{ 10, "" },	// 2
	{ 11, "" },	// 3
	{ 12, "" },	// 4
	{ 13, "" },	// 5
	{ 14, "" },	// 6
	{ 15, "" }	// 7
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
	unsigned char dr;
	dr = drive->drive;

	if(dr < 8 || dr > 15)
	{
		return -1;
	}

	result = cbm_open(15, dr, 15, "");

	if(_oserror != 0)
	{
		cbm_close(15);

		return -1;
	}

	if(result == 0 && _oserror == 0)
	{
		size = cbm_read(15, drive->message, 38);
		if(size >=0) drive->message[size] = '\0';
		else drive->message[0] = '\0';
		
		if(strlen(drive->message) > 0)
		{
			cbm_write(15, "ui", 2); 

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
	unsigned selected = FALSE;
	const unsigned char h = 13;
	const unsigned char w = 39;

	unsigned char x, y, i;
	unsigned char status, current, original, key;
	unsigned char message[10];

	x = getCenterX(w);
	y = getCenterY(h);

	writePanel(TRUE, FALSE,
		COLOR_GRAY3, 
		x, y, h, w,
		"Drives", NULL, NULL);

	textcolor(COLOR_WHITE);

	current = 0;

	for(i=0; i<8; ++i)
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
	gotoxy(x + 1, y + 11); 
	cputs("Use arrow keys & enter to select drive");
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
				--current;
				gotoxy(x + 1, current + 2 + y); cputc('>');
			}
			break;

		case CH_CURS_DOWN:
			if(current < 11)
			{
				gotoxy(x + 1, current + 2 + y); cputc(' ');
				++current;
				gotoxy(x + 1, current + 2 + y); cputc('>');
			}
			break;
		}
	}

	if(menu == left)
	{
		leftPanelDrive.drive = &(drives[current]);
		currentLeft = leftPanelDrive.drive->drive;

		writeStatusBarf("Left is now drive %d", currentLeft);
	}
	else
	{
		rightPanelDrive.drive = &(drives[current]);
		currentRight = rightPanelDrive.drive->drive;

		writeStatusBarf("Right is now drive %d", currentRight);
	}
}

int __fastcall__ getDirectory(
	struct panel_drive *drive,
	int slidingWindowStartAt)
{
	unsigned int slidingWindowSize = 30;
	unsigned char* name;
	unsigned char result, dr, nameLength;
	unsigned int counter;
	struct cbm_dirent currentDE;
	struct dir_node *currentNode, *newNode, *nextNode;

	drive->slidingWindowStartAt = slidingWindowStartAt;

	currentNode = drive->head;
	while(currentNode != NULL)
	{
		nextNode = currentNode->next;
		free(currentNode->name);
		free(currentNode);
		currentNode = nextNode;
	}

	drive->head = NULL;
	drive->length = 0;
	drive->slidingWindowStartAt = slidingWindowStartAt;

	dr = drive->drive->drive;

	result = cbm_opendir(dr, dr);
	if(result == 0)
	{
		writeStatusBar("Reading directory...");
		counter = 0;
		currentNode = malloc(sizeof(struct dir_node));
		currentNode->name = NULL;
		currentNode->next = NULL;
		currentNode->index = counter;
		drive->head = currentNode;
		while(!cbm_readdir(dr, &currentDE))
		{
			++counter;
			if(currentDE.type == 10 ||
				(counter >= slidingWindowStartAt &&
				counter < slidingWindowStartAt + slidingWindowSize))
			{
				nameLength = strlen(currentDE.name) + 1;
				name = calloc(nameLength, sizeof(unsigned char));
				strcpy(name, currentDE.name);
				currentNode->name = name;
				currentNode->size = currentDE.size;
				currentNode->type = currentDE.type;
			}
			newNode = malloc(sizeof(struct dir_node));
			currentNode->next = newNode;
			newNode->index = counter;
			newNode->name = NULL;
			newNode->next = NULL;
			newNode->isSelected = FALSE;
			currentNode = newNode;
		}
		cbm_closedir(dr);
		drive->length = counter;
		if(drive->currentIndex >= drive->length)
		{
			drive->currentIndex = drive->length - 1;
		}
		writeStatusBarf("Finished reading %u files.", counter - 1);
	}

	return counter;
}

void __fastcall__ displayDirectory(
	struct panel_drive *drive)
{
	unsigned char w = 19, x = 0;
	unsigned char fileType;
	unsigned int i;
	struct dir_node *currentNode;
	unsigned char size[4];

	currentNode = drive->head;

	if(currentNode->name == NULL)
	{
		getDirectory(drive, 0);
	}

	if(size_x > 40) w=39;
	if(drive->position == right) x=w + 1;
	
	writePanel(TRUE, FALSE, COLOR_GRAY3, x, 1, 21, w, 
		currentNode->name, NULL, NULL);
	
	currentNode = getSpecificNode(drive, drive->displayStartAt);

	for(i = currentNode->index; i < drive->length; ++i)
	{
		if(i+1 == drive->displayStartAt + 22) break;
		
		if(currentNode->name == NULL
			&& i < drive->length - 1)
		{
			drive->slidingWindowStartAt = i - 5;
			getDirectory(drive, drive->slidingWindowStartAt);
			currentNode = getSpecificNode(drive, i);
		}
		else if(currentNode->next != NULL
			&& currentNode->next->name == NULL
			&& i < drive->length - 1)
		{
			drive->slidingWindowStartAt += 5;
			getDirectory(drive, drive->slidingWindowStartAt);
			currentNode = getSpecificNode(drive, i - 1);
		}

		gotoxy(x + 2, i - drive->displayStartAt +1);
		
		shortenSize(size, currentNode->size);
		fileType = getFileType(currentNode->type);

		textcolor(COLOR_YELLOW);
		if(currentNode->isSelected == TRUE)
		{
			revers(TRUE);
		}
		else
		{
			revers(FALSE);
		}		

		sprintf(drivesBuffer, "%c %s %s", 
			fileType, 
			size,
			shortenString(currentNode->name)
			);

		cputs(drivesBuffer);

		revers(FALSE);

		currentNode = currentNode->next;
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
	unsigned int i;

	if(panel != NULL)
	{
		if(panel->drive != NULL)
		{
			currentDirNode = panel->head;
			for(
				i=0; 
				i<=panel->currentIndex
					&& currentDirNode != NULL; 
				++i)
			{
				currentDirNode = currentDirNode->next;
			}

			if(currentDirNode != NULL)
			{
				writeStatusBarf("Idx: %3u Sz: %5u Nm: %s",
					currentDirNode->index,
					currentDirNode->size,
					currentDirNode->name);
			}
		}
	}
}

void __fastcall__ moveSelectorUp(struct panel_drive *panel)
{
	unsigned char diff;
	unsigned firstPage;

	writeSelectorPosition(panel, ' ');
	firstPage = panel->displayStartAt == 0;
	diff = panel->currentIndex - panel->displayStartAt;

	if(!firstPage && diff == 1)
	{
		panel->displayStartAt--;
		panel->currentIndex--;
		displayDirectory(panel);
	}
	else if(diff > 0)
	{
		panel->currentIndex--;
	}
	
	writeSelectorPosition(panel, '>');
	if(size_x <= 40) writeCurrentFilename(panel);
}

void __fastcall__ moveSelectorDown(struct panel_drive *panel)
{
	const unsigned char offset = 19;
	unsigned char diff;
	unsigned lastPage;

	writeSelectorPosition(panel, ' ');

	lastPage = panel->displayStartAt + offset + 2 >= panel->length;
	diff = panel->length - panel->displayStartAt;

	if(!lastPage && diff > offset &&
		((panel->currentIndex - panel->displayStartAt) == offset))
	{
		panel->displayStartAt++;
		panel->currentIndex++;
		displayDirectory(panel);
	}
	else if(lastPage && 
		(panel->currentIndex - panel->displayStartAt) < offset &&
		(panel->currentIndex + 2) < panel->length)
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
		sprintf(buffer, "%2dK", (value + 512)/1024);
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

	if(selectedPanel != NULL)
	{
		if(selectedPanel->drive != NULL)
		{
			currentDirNode = selectedPanel->head;
			for(
				i=0; 
				i<=selectedPanel->currentIndex
					&& currentDirNode != NULL; 
				++i)
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
		}
	}
}

void __fastcall__ enterDirectory(struct panel_drive *panel)
{
	unsigned char command[40];
	struct dir_node *node;

	node = getSelectedNode(panel);

	if(isDiskImage(panel) || isDirectory(panel))
	{
		strcpy(command, "cd:");
		strcat(command, node->name);
		sendCommand(panel, command);
		panel->currentIndex = 0;
		panel->displayStartAt = 0;
		getDirectory(panel, 0);
		displayDirectory(panel);
	}
}

void __fastcall__ leaveDirectory(struct panel_drive *panel)
{
	unsigned char buffer[4];
	buffer[0] = 'c';
	buffer[1] = 'd';
	buffer[2] = 95;
	buffer[3] = '\0';

	sendCommand(panel, buffer);
	panel->currentIndex = 0;
	panel->displayStartAt = 0;
	getDirectory(panel, 0);
	displayDirectory(panel);
}

unsigned __fastcall__ isDiskImage(struct panel_drive *panel)
{
	unsigned result = FALSE;
	struct dir_node *currentDirNode = NULL;

	currentDirNode = getSelectedNode(panel);

	if(currentDirNode != NULL)
	{
		if(strstr(currentDirNode->name, ".D64") > 0
			|| strstr(currentDirNode->name, ".D81") > 0
			|| strstr(currentDirNode->name, ".D71") > 0
			|| strstr(currentDirNode->name, ".DNP") > 0
			|| strstr(currentDirNode->name, ".d64") > 0
			|| strstr(currentDirNode->name, ".d81") > 0
			|| strstr(currentDirNode->name, ".d71") > 0
			|| strstr(currentDirNode->name, ".dnp") > 0
		)
		{
			result = TRUE;
		}
		else
		{
			result = FALSE;
		}
	}

	return result;
}

unsigned __fastcall__ isDirectory(struct panel_drive *panel)
{
	unsigned result = FALSE;
	struct dir_node *currentDirNode = NULL;

	currentDirNode = getSelectedNode(panel);

	if(currentDirNode != NULL)
	{
		if(currentDirNode->type == 6)
		{
			result = TRUE;
		}
		else
		{
			result = FALSE;
		}
	}

	return result;
}

struct dir_node* __fastcall__ getSelectedNode(struct panel_drive *panel)
{
	return getSpecificNode(panel, panel->currentIndex);
}

struct dir_node* __fastcall__ getSpecificNode(struct panel_drive *panel, int index)
{
	unsigned int i;
	struct dir_node *currentDirNode = NULL;

	if(panel != NULL)
	{
		if(panel->drive != NULL)
		{
			currentDirNode = panel->head;
			for(
				i=0; 
				i<=index
					&& currentDirNode != NULL; 
				++i)
			{
				currentDirNode = currentDirNode->next;
			}
		}
	}

	return currentDirNode;
}

unsigned char __fastcall__ sendCommand(
	struct panel_drive *panel,
	unsigned char *command)
{
	char result;
	unsigned char drive;
	unsigned char buffer[40];

	drive = panel->drive->drive;

	result = cbm_open(drive, drive, 15, "");

	result = cbm_write(drive, command, strlen(command));

	if(result > 0)
	{
		cbm_read(drive, buffer, 39);
		writeStatusBarf(buffer);
	}

	cbm_close(drive);

	return result;
}
