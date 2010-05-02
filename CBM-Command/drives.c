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

struct panel_drive leftPanelDrive;
struct panel_drive rightPanelDrive;

unsigned char currentLeft = 0;
unsigned char currentRight = 0;

int __fastcall__ getDriveStatus(
	struct drive_status *drive)
{
	int result;
	int size;
	unsigned char buffer[39];
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
			currentNode = newNode;
			counter++;
		}
		cbm_closedir(dr);
		drive->length = counter;
		writeStatusBar("Finished reading directory.", 
			wherex(), wherey());
	}

	return counter;
}

void __fastcall__ displayDirectory(struct panel_drive *drive, enum menus menu)
{
	unsigned char oldReverse, fileType, w = 19, x = 0;
	int i;
	struct dir_node *currentNode;
	unsigned char size[4];
	currentNode = drive->head;

	if(size_x > 40) w=39;
	if(menu == right) x=w + 1;
	
	writePanel(TRUE, FALSE, COLOR_GRAY3, x, 1, 21, w, 
		currentNode->dir_entry->name, NULL, NULL);
	
	textcolor(COLOR_YELLOW);
	currentNode = currentNode->next;
	for(i=1; i < drive->length; i++)
	{
		if(i+1 == 22) break;
		
		gotoxy(x + 2, i+1);
		
		shortenSize(size, currentNode->dir_entry->size);
		fileType = getFileType(currentNode->dir_entry->type);
		//writeStatusBar(size, wherex(), wherey());

#ifdef __C128__
		// Works around a bug in CC65's CONIO 
		// library on the VDC.
		textcolor(COLOR_YELLOW);
#endif
		sprintf(drivesBuffer, "%c %s %s", 
			fileType, 
			size,
			shortenString(currentNode->dir_entry->name)
			);

		cputs(drivesBuffer);
		currentNode = currentNode->next;
	}
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