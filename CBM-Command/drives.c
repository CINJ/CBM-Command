#include <cbm.h>
#include <conio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "drives.h"
#include "input.h"
#include "screen.h"
#include "menus.h"

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

int getDriveStatus(
	struct drive_status *drive)
{
	int result;
	int size;
	unsigned char buffer[39];
	unsigned char dr;
	dr = drive->drive;

	if(dr < 8 || dr > 19)
	{
		sprintf(drive->message, "Cannot open drive %d", dr);
		writeStatusBar(drive->message, wherex(), wherey());
		return -1;
	}

	result = cbm_open(15, dr, 15, "");

	if(_oserror == 0)
	{
		sprintf(buffer, "Opened drive %d", dr);
		writeStatusBar(buffer, wherex(), wherey());
	}
	else
	{
		cbm_close(15);

		sprintf(buffer, "_oserror = %d, closed channel.", _oserror);
		writeStatusBar(buffer, wherex(), wherey());

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

void listDrives(enum menus menu)
{
	unsigned char x, y, i, status;
	const unsigned char h = 15;
	const unsigned char w = 39;
	unsigned char message[40];

	x = getCenterX(w);
	y = getCenterY(h);

	writePanel(TRUE, FALSE,
		COLOR_GRAY3, 
		x, y, h, w,
		"Drives", NULL, NULL);

	textcolor(COLOR_WHITE);

	for(i=0; i<12; i++)
	{
		if( 
			(currentLeft > 0 && drives[i].drive == currentLeft && menu == left) ||
			(currentRight > 0 && drives[i].drive == currentRight && menu == right)
		)
		{
			revers(TRUE);
		}

		gotoxy(x + 2, i + 2 + y);
		sprintf(message, "%d", i + 8);
		cputs(message);

		status = checkDrive(2, "UJ", i + 8);
		sprintf(message, "Drive %d returns %d", i + 8, status);
		writeStatusBar(message, wherex(), wherey());

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

	waitForEnterEsc();
}

