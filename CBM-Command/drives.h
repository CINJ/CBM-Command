#ifndef _DRIVES_H
#define _DRIVES_H

#include "menus.h"

struct drive_status
{
	unsigned char drive;
	unsigned char message[39];
	unsigned selected_left;
	unsigned selected_right;
};

struct panel_drive
{
	struct drive_status *drive;
	struct cbm_dirent *dir_entry[];
};

extern struct drive_status drives[12];
extern struct panel_drive leftPanelDrive;
extern struct panel_drive rightPanelDrive;

int getDriveStatus(
	struct drive_status *drive);

void listDrives(enum menus menu);

extern unsigned char __fastcall__ checkDrive(
	unsigned char length,
	unsigned char* file,
	unsigned char drive);
#endif