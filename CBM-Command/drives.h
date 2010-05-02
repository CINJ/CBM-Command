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

struct dir_node
{
	struct cbm_dirent *dir_entry;
	struct dir_node *prev;
	struct dir_node *next;
	unsigned isSelected;
};

struct panel_drive
{
	struct drive_status *drive;
	struct dir_node *head;
	struct dir_node *tail;
	int length;
};

extern struct drive_status drives[12];
extern struct panel_drive leftPanelDrive;
extern struct panel_drive rightPanelDrive;

int __fastcall__ getDriveStatus(
	struct drive_status *drive);

void __fastcall__ listDrives(enum menus menu);

extern unsigned char __fastcall__ checkDrive(
	unsigned char length,
	unsigned char* file,
	unsigned char drive);

int __fastcall__ getDirectory(struct panel_drive *drive);

void __fastcall__ displayDirectory(struct panel_drive *drive, enum menus menu);

unsigned char __fastcall__ getFileType(unsigned char type);
void __fastcall__ shortenSize(unsigned char* buffer, unsigned int value);
unsigned char* __fastcall__ shortenString(unsigned char* source);
#endif