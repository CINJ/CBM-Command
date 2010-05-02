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

#ifndef _DRIVES_H
#define _DRIVES_H

#include "menus.h"

extern int currentLeftIndex;
extern int currentRightIndex;
extern enum menus currentPanel;

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
	int currentIndex;
	int displayStartAt;
	enum menus position;
};

extern unsigned areDrivesInitialized;
extern struct drive_status drives[12];
extern struct panel_drive leftPanelDrive;
extern struct panel_drive rightPanelDrive;

void __fastcall__ initializeDrives(void);

int __fastcall__ getDriveStatus(
	struct drive_status *drive);

void __fastcall__ listDrives(enum menus menu);

extern unsigned char __fastcall__ checkDrive(
	unsigned char length,
	unsigned char* file,
	unsigned char drive);

int __fastcall__ getDirectory(struct panel_drive *drive);

void __fastcall__ displayDirectory(struct panel_drive *drive);

unsigned char __fastcall__ getFileType(unsigned char type);
void __fastcall__ shortenSize(unsigned char* buffer, unsigned int value);
unsigned char* __fastcall__ shortenString(unsigned char* source);
#endif