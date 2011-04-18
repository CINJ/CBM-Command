/***************************************************************
Copyright (c) 2011, Payton Byrd
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

#ifdef __CBM__
#include <cbm.h>
#endif
#include <conio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Configuration.h"
#include "constants.h"
#include "drives.h"
#include "globalInput.h"
#include "globals.h"
#include "input.h"
#include "screen.h"
//#include "menus.h"

//static unsigned char drivesBuffer[80];

#ifdef __CBM__
static struct drive_status drives[] =
{
	{ 8 },	// 0
	{ 9 },	// 1
	{ 10 },	// 2
	{ 11 },	// 3
	{ 12 },	// 4
	{ 13 },	// 5
	{ 14 },	// 6
	{ 15 },	// 7
	{ 16 }	// 8
};
#endif

struct panel_drive  leftPanelDrive;
struct panel_drive rightPanelDrive;
struct panel_drive *selectedPanel;

static unsigned char currentLeft;
static unsigned char currentRight;

void initializeDrives(void)
{
	memset(& leftPanelDrive, 0, sizeof  leftPanelDrive);
	memset(&rightPanelDrive, 0, sizeof rightPanelDrive);

	 leftPanelDrive.drive = &(drives[currentLeft  = defaultLeftDrive  - 8]);
	rightPanelDrive.drive = &(drives[currentRight = defaultRightDrive - 8]);

#ifdef __VIC20__
	 leftPanelDrive.selectedEntries = (unsigned char *) 0xA100;
	rightPanelDrive.selectedEntries = (unsigned char *)(0xA100 + 8192 / 8);
#endif

	// XXX: This field is obsolete -- remove it.
	// leftPanelDrive.position =  left;
	//rightPanelDrive.position = right;

	selectedPanel = &leftPanelDrive;
}

static int __fastcall getDriveStatus(
	struct drive_status *drive)
{
	int size;
	//unsigned char dr = drive->drive;

	//if(dr < 8 || dr > 15)
	//{
	//	return -1;
	//}

	if(cbm_open(15, drive->drive, 15, "") != 0)
	{
		waitForEnterEscf("_oserror: %u", _oserror);
		cbm_close(15);

		return -1;
	}

	size = cbm_read(15, drive->message, (sizeof drive->message) - 1);
	if(size > 0)
	{
		cbm_write(15, "ui", 2);
		size = cbm_read(15, drive->message, (sizeof drive->message) - 1);
	}
	drive->message[size < 0 ? 0 : size] = '\0';

	cbm_close(15);
	return size;
}

//#ifdef __PLUS4__
//static unsigned char __fastcall checkDrivePlus4(unsigned char drive)
//{
//	unsigned char result = cbm_open(15, drive, 15, "ui");
//
//	cbm_close(15);
//	return result;
//}
//#endif

void __fastcall__ listDrives(const enum menus menu)
{
	static const unsigned char h = A_SIZE(drives) + 6;
	static const unsigned char w = size_x - 1u;
	//unsigned char x = getCenterX(w) + 1, y = getCenterY(h);
	unsigned char current = 0, original = 0, i = 0;
	unsigned char x, y;

	x = getCenterX(w) + 1;
	y = getCenterY(h);

	writePanel(true, false,
		color_text_borders,
		x - 1, y, h, w,
		"Drives", NULL, NULL);

	(void)textcolor(color_text_other);

	y += 2;

	for(i=0; i<A_SIZE(drives); ++i)
	{
		if(
			(i == currentLeft  && menu ==  left) ||
			(i == currentRight && menu == right)
		)
		{
			revers(true);
			original = current = i;
		}

		gotoxy(x, i + y);
		cprintf("%3u ", i + 8);

		drives[i].message[0] = '\0';
		if(
//#ifndef __PLUS4__
			checkDrive(i + 8)
//#else
//			checkDrivePlus4(i + 8)
//#endif
			== 0)
		{
			getDriveStatus(&(drives[i]));
			cputs(drives[i].message);
		}
		else
		{
			cputs("No device ");
		}

		revers(false);
	}

	(void)textcolor(color_text_highlight);
	cputsxy(x, y + 10, "Use Up/Down & RETURN  to pick drive");

	(void)textcolor(color_selector);
	for (;;)
	{
		cputcxy(x, current + y, '>');
		i = getKey();
		cputcxy(x, current + y, ' ');

		switch (i)
		{
		case CH_STOP:
			current = original;
			break;

		case CH_ENTER:
			if (drives[current].message[0] != '\0')
			{
				break;
			}
			continue;

		case CH_CURS_UP:
			if(current > 0)
			{
				--current;
			}
			continue;

		case CH_CURS_DOWN:
			if (current < A_SIZE(drives) - 1)
			{
				++current;
			}
			continue;

		default:
			continue;
		}
		break;
	}

	if(menu == left)
	{
		leftPanelDrive.drive = &(drives[currentLeft = current]);
		//currentLeft = leftPanelDrive.drive->drive - 8;
	}
	else
	{
		rightPanelDrive.drive = &(drives[currentRight = current]);
		//currentRight = rightPanelDrive.drive->drive - 8;
	}
}

unsigned int __fastcall getDirectory(
	struct panel_drive *drive,
	int slidingWindowStartAt)
{
#ifdef __CBM__
	struct cbm_dirent currentDE;
	unsigned char dr;
	int i;
	unsigned int counter=0;
	bool useDoubleBuffer = isDoubleBuffered;

	if(isDoubleBuffered) endDoubleBuffer();

	drive->slidingWindowStartAt = slidingWindowStartAt;

	drive->header.name[0] = '\0';		// start with no directory-name;
	drive->header.access  = '\0';		// and, no format-code

	memset(drive->slidingWindow, 0, SLIDING_WINDOW_SIZE);

	dr = drive->drive->drive;

	//if (drive->drive->message[0] == '\0')
	//{
	//	if (checkDrive(dr) != 0)
	//	{
	//		return 0;
	//	}
	//}

	writeStatusBar("Reading directory...");
	if (cbm_opendir(2, dr) == 0)
	{
		while (!(dr = cbm_readdir(2, &currentDE)))
		{
			if(counter == 0 && currentDE.type == CBM_T_HEADER)
			{
#ifdef __CBM__
				// .size holds drive/partition number
				// .access holds disk-format code
				drive->header = currentDE;
#else
				strcpy(drive->header.name, currentDE.name);
 				////strncat(drive->header.name, currentDE.name,
				////	(sizeof drive->header.name) - 1);
				//drive->header.type = CBM_T_HEADER;
				//drive->header.index = 0;
#endif
			}
			else
			{
				i = (signed int)(counter - 1 - slidingWindowStartAt);
				if(i >= 0 &&
					i < SLIDING_WINDOW_SIZE)
				{
					strcpy(drive->slidingWindow[i].name,
						currentDE.name);
 					//strncat(drive->slidingWindow[i].name, currentDE.name,
					//	(sizeof drive->slidingWindow[i].name) - 1);
					drive->slidingWindow[i].size = currentDE.size;
					drive->slidingWindow[i].type = currentDE.type;
					drive->slidingWindow[i].index = counter;
				}
			}
			++counter;
		}

		if (dr == 2)
		{
			/* "blocks free/used" line was read. */
			drive->header.size = currentDE.size;
		}

		writeStatusBarf("Read %d names", counter - 1);
	}
	cbm_closedir(2);

	// Other functions assume that a directory header always was counted!
	if (counter == 0)
	{
		counter = 1;
	}

	// Make sure that the selector won't point past the end of a directory,
	// in case a disk was swapped, and the new directory is shorter,
	// but the panel wasn't refreshed.
	if (drive->currentIndex >= (drive->length = counter) - 1)
	{
		if ((drive->currentIndex = counter - 2) < 0)
		{
			drive->currentIndex = 0;
		}
	}

	if(useDoubleBuffer) beginDoubleBuffer();

	return counter;
#else
	return 0;
#endif
}

void __fastcall__ resetSelectedFiles(struct panel_drive *panel)
{
#ifndef __VIC20__
	free(panel->selectedEntries);

	// This is a kludge.
	// If a directory is too long for the heap, then reduce its apparent size
	// by a screen page, until it fits.
	while ((panel->selectedEntries =
		// (This "- 1" is because "length" counted the directory header.)
		calloc((panel->length + (7 - 1)) / 8u, sizeof(unsigned char))) == NULL)
	{
		if ((panel->length -= size_y - 6u) < 1)
		{
			panel->length = 1;
			break;
		}
	}
#else
	memset(panel->selectedEntries, 0x00, 8192 / 8);
#endif
}

void __fastcall displayDirectory(
	struct panel_drive *drive)
{
	static const unsigned char w = size_x /
#if size_x < 40
		1u;						// only one panel at-a-time, on a VIC-20
// The function-key menu must be folded on the VIC-20's narrow screen.
// So, the panels are one line shorter.
#define panelHeight (size_y - 4u)
#else
		2u;
#define panelHeight (size_y - 3u)
#endif
	unsigned char x = 0;
	unsigned int i, start;
	char fileType;
	const struct dir_node *currentNode;
	char size[4];

	beginDoubleBuffer();

	if(drive->header.name[0] == '\0')
	{
		getDirectory(drive, 0);
		resetSelectedFiles(drive);
	}

	drive->visible = true;

	//if(size_x > 40) w=40;

#if size_x > 22
	if(drive == &rightPanelDrive) x=w;
#endif

	(void)textcolor(color_text_borders);
	cvlinexy(0, 1, panelHeight);
#if size_x > 22
	cvlinexy(w, 1, panelHeight);
#endif
	chlinexy(x+1, panelHeight, w - 1u);
	cclearxy(x+1, 1, w-1);
	gotoxy(x+1, 1); cprintf(
#ifdef __CBM__
		"[%s]%c", drive->header.name, drive->header.access
#else
		"[%s]", drive->header.name
#endif
		);
	gotoxy(x+1, panelHeight); cprintf("[%2u]", drive->drive->drive);
#if size_x < 40
	gotox(getCenterX(5)); cputs((drive == &leftPanelDrive) ? "Left" : "Right");
#endif

	gotox(x + w - 7); cprintf("[%5u]", drive->header.size);

	(void)textcolor(color_text_files);

	i = start = drive->displayStartAt;
	for(; i<start + (panelHeight - 2u) && i < drive->length - 1; i++)
	{
		currentNode = getSpecificNode(drive, i);
		if(currentNode == NULL ||
			currentNode->name[0] == '\0')
		{
			//endDoubleBuffer();
			//if(i == drive->length - 1) break;
			if(i != start)
			{
				// We are at bottom, and scrollable.
				getDirectory(drive, drive->slidingWindowStartAt + 5);
			}
			else
			{
				getDirectory(drive, (i > 5) ? i - 5 : 0);
			}
			currentNode = getSpecificNode(drive, i);
			//beginDoubleBuffer();

			(void)textcolor(color_text_files);
		}

		shortenSize(size, currentNode->size);
		fileType = getFileType(currentNode->type);

		revers(drive->selectedEntries[(currentNode->index - 1) / 8u]
			& (unsigned char)(1 << ((currentNode->index - 1) % 8u)));

		gotoxy(x + 1, i - start + 2);
		cprintf(
#if size_x < 40
			"%c%3s %-16s",
#elif size_x == 40
			"%3s %-14s%c",
#else
			// 80 columns
			"%4s   %-20s%c ",
#endif
#if size_x < 40
			fileType,
			size,
			currentNode->name
#else
			size,
			shortenString(currentNode->name),
			fileType
#endif
			);

		(void)revers(false);
	}

	while(i<start + (panelHeight - 2u))
	{
		// Draw the rest of the lines as blank.
		cclearxy(x  + 1, i - start + 2, w-1);
		++i;
	}

#if size_x > 40
	(void)textcolor(color_text_borders);
	cputcxy(x + 6, 22, CH_BTEE);
	gotox(x + 26); cputc(CH_BTEE);
	gotox(x + 30); cputc(CH_BTEE);
	cvlinexy(x +  6, 2, panelHeight - 2);
	cvlinexy(x + 26, 2, panelHeight - 2);
	cvlinexy(x + 30, 2, panelHeight - 2);
#endif
	endDoubleBuffer();
}

void __fastcall writeSelectorPosition(struct panel_drive *panel,
	char character)
{
	revers(false);
	(void)textcolor(color_selector);
	if(character == ' ')
	{
		(void)textcolor(color_text_borders);
		character = CH_VLINE;
	}
	cputcxy(
#if size_x < 40
		0u,
#else
		panel == &leftPanelDrive ? 0u : size_x / 2u,
#endif
		panel->currentIndex - panel->displayStartAt + 2,
		character);
}

void __fastcall writeCurrentFilename(struct panel_drive *panel)
{
	const struct dir_node *currentDirNode;

	//if(panel != NULL)
	{
		//if(panel->drive != NULL)
		{
			currentDirNode = getSelectedNode(panel);

			if(currentDirNode != NULL)
			{
				writeStatusBarf("%16s%6u",
					currentDirNode->name,
					currentDirNode->size);
			}
		}
	}
}

void __fastcall moveSelectorUp(struct panel_drive *panel)
{
	writeSelectorPosition(panel, ' ');

	if (panel->currentIndex > 0)
	{
		if (--(panel->currentIndex) < panel->displayStartAt)
		{
			--(panel->displayStartAt);
			displayDirectory(panel);
		}
	}

	writeSelectorPosition(panel, '>');
	writeCurrentFilename(panel);
}

#if size_x < 40
#define displayHeight (size_y - 5u)
#else
#define displayHeight (size_y - 4u)
#endif

void __fastcall moveSelectorDown(struct panel_drive *panel)
{
	writeSelectorPosition(panel, ' ');

	if (panel->currentIndex < panel->length - 2)
	{
		if (++(panel->currentIndex) >= panel->displayStartAt + displayHeight - 1)
		{
			++(panel->displayStartAt);
			displayDirectory(panel);
		}
	}

	writeSelectorPosition(panel, '>');
	writeCurrentFilename(panel);
}

char __fastcall getFileType(unsigned char type)
{
	if(type < CBM_T_OTHER) return "dSPURCDLV"[type];
	return 'O';
}

static void __fastcall shortenSize(char* buffer, unsigned int value)
{
	if(value < 1000u)
	{
		sprintf(buffer, "%u", value);
	}
	else
	{
		sprintf(buffer, "%uK", (unsigned int)((value + 1024uL/2)/1024uL));
	}
}

#if size_x > 22
static char* __fastcall shortenString(char* source)
{
#if size_x == 40
#define targetLength 13u
	// buffer[] must be static because it's passed back to the caller.
	static char buffer[targetLength + 1];

	//if(size_x == 40)
	//{
		if(strlen(source) > targetLength)
		{
			sprintf(buffer, "%.11s..", source);
			return buffer;
		}
	//}
#endif

	return source;
}
#endif

void selectCurrentFile(void)
{
	struct dir_node *currentDirNode;

	//if(selectedPanel != NULL)
	{
		if(selectedPanel->selectedEntries != NULL)
		{
			currentDirNode = getSelectedNode(selectedPanel);
			if(currentDirNode != NULL)
			{
				/* Toggle the selected entry. */
				selectedPanel->selectedEntries[(currentDirNode->index - 1) / 8u]
					^= 1 << ((currentDirNode->index - 1) % 8u);

				displayDirectory(selectedPanel);
				//moveSelectorDown(selectedPanel);
				//writeSelectorPosition(selectedPanel, '>');
			}
		}
	}
}

void __fastcall enterDirectory(struct panel_drive *panel)
{
	char command[41];

	if(isDiskImage(panel) || isDirectory(panel))
	{
		sprintf(command, "cd:%s", getSelectedNode(panel)->name);
		sendCommand(panel, command);
		//panel->currentIndex = panel->displayStartAt = 0;
		rereadSelectedPanel();
	}
}

void __fastcall leaveDirectory(struct panel_drive *panel)
{
	static const char buffer[] =
	{
		'c',
		'd',
		0x5f,					// PetSCII left-arrow
		'\0'
	};

	sendCommand(panel, buffer);
	//panel->currentIndex = panel->displayStartAt = 0;
	rereadSelectedPanel();
}

static bool __fastcall__ isDiskImage(struct panel_drive *panel)
{
	static char name[17];
	const struct dir_node *currentDirNode =
		getSelectedNode(panel);

	if(currentDirNode != NULL)
	{
		return strstr(
				// Make a copy of the name, and make that copy all lower-case.
				// Then, only half as many suffix tests are needed.
				strlower(strcpy(name, currentDirNode->name)), ".d64") != NULL
			|| strstr(name, ".d71") != NULL
			|| strstr(name, ".d81") != NULL
			|| strstr(name, ".d80") != NULL
			|| strstr(name, ".d82") != NULL
			|| strstr(name, ".dnp") != NULL
			|| strstr(name, ".d41") != NULL;
	}

	return false;
}

static bool __fastcall__ isDirectory(struct panel_drive *panel)
{
	const struct dir_node *currentDirNode = getSelectedNode(panel);

	return currentDirNode != NULL && currentDirNode->type == CBM_T_DIR;
}

struct dir_node* __fastcall__ getSelectedNode(struct panel_drive *panel)
{
	return getSpecificNode(panel, panel->currentIndex);
}

struct dir_node* __fastcall__ getSpecificNode(
	struct panel_drive *panel, int index)
{
	static int offset;
	offset = index - panel->slidingWindowStartAt;

	return (offset >= 0 && offset < SLIDING_WINDOW_SIZE) ?
		&(panel->slidingWindow[offset]) : NULL;
}

signed char __fastcall__ sendCommand(
	const struct panel_drive *panel,
	const char *command)
{
#ifdef __CBM__
	static signed char result;

	cbm_open(15, panel->drive->drive, 15, command);

	result = cbm_read(15, buffer, (sizeof buffer) - 1);
	buffer[result < 0 ? 0 : result] = '\0';

	cbm_close(15);

	// Show error messages.
	if (buffer[0] != '0')
	{
		writeStatusBar(buffer);
		waitForEnterEsc();
		return -1;		// A negative return-value means that command failed.
	}
#endif
	return 0;
}

void __fastcall__ selectAllFiles(struct panel_drive *panel,
	unsigned char select)
{
	static unsigned int i;

	if(panel->selectedEntries != NULL)
	{
		for (i = 0; i < (panel->length + (7 - 1)) / 8u; ++i)
		{
			panel->selectedEntries[i] = select;
		}
		//// Deselect bits that don't represent entries.
		//if (i > 0)
		//{
		//	panel->selectedEntries[i - 1] &=
		//		(unsigned char)((1 << ((panel->length - 2) % 8u + 1)) - 1);
		//}
	}

	displayDirectory(panel);
	writeSelectorPosition(panel, '>');
	writeCurrentFilename(panel);
}

void __fastcall__ moveTop(struct panel_drive *panel)
{
	getDirectory(panel,
		//panel->slidingWindowStartAt =
		panel->currentIndex =
		panel->displayStartAt = 0);

	displayDirectory(panel);
	writeSelectorPosition(panel, '>');
	writeCurrentFilename(panel);
}

#if size_x < 40
#define indexJump (size_y - 7u)
#else
#define indexJump (size_y - 6u)
#endif

void __fastcall__ movePageUp(struct panel_drive *panel)
{
	if(panel->currentIndex < indexJump)
	{
		moveTop(panel);
	}
	else
	{
		getDirectory(panel,
			//panel->slidingWindowStartAt =
			panel->displayStartAt =
			panel->currentIndex -= indexJump);
		displayDirectory(panel);
		writeSelectorPosition(panel, '>');
		writeCurrentFilename(panel);
	}
}

void __fastcall__ movePageDown(struct panel_drive *panel)
{
	if(panel->currentIndex + (indexJump + 2) > panel->length)
	{
		moveBottom(panel);
	}
	else
	{
		//panel->slidingWindowStartAt =
			panel->displayStartAt = panel->currentIndex;
		panel->currentIndex += indexJump;

		getDirectory(panel, panel->displayStartAt);
		displayDirectory(panel);
		writeSelectorPosition(panel, '>');
		writeCurrentFilename(panel);
	}
}

void __fastcall__ moveBottom(struct panel_drive *panel)
{
	if ((panel->currentIndex = panel->length - 2) < 0)
	{
		panel->currentIndex = 0;
	}
	panel->displayStartAt =
		(panel->length > displayHeight) ?
			panel->length - displayHeight : 0;

	getDirectory(panel,
		(panel->length > SLIDING_WINDOW_SIZE) ?
			panel->length - SLIDING_WINDOW_SIZE : 0);
	displayDirectory(panel);
	writeSelectorPosition(panel, '>');
	writeCurrentFilename(panel);
}
