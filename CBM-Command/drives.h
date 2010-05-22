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

/* STRUCTS */

/* Drive Status
 *-----------------------------
 *- Payton Byrd
 *-----------------------------
 * Used to store the drive number
 * and drive init message for 
 * each device.
 */
struct drive_status
{
	unsigned char drive;
	unsigned char message[39];
};

/* Directory Node
 *-----------------------------
 *- Payton Byrd
 *-----------------------------
 * Stores the name, type, size
 * and index of a section of the
 * sliding directory window.
 */
struct dir_node
{
	unsigned char name[17];
	unsigned char type;
	unsigned int size;
	int index;
};

/* Panel Drive
 *-----------------------------
 *- Payton Byrd
 *-----------------------------
 * Contains the "moving parts"
 * of the application.  There are
 * two Panels declared, each with
 * it's own data for selected 
 * entries, the drive that is 
 * associated with the panel,
 * the directory header, the 30
 * directory nodes for the sliding
 * window, the total length of the 
 * directory, where the directory
 * display starts from, where the
 * sliding window starts from and
 * the position (left or right) of
 * the panel.
 */
struct panel_drive
{
	unsigned char* selectedEntries;
	struct drive_status *drive;
	struct dir_node header;
	struct dir_node slidingWindow[30];
	int length;
	int currentIndex;
	int displayStartAt;
	int slidingWindowStartAt;
	enum menus position;
};

/* GLOBAL VARIABLES */
extern unsigned areDrivesInitialized;		// Has the drives been intialized?
extern struct drive_status drives[9];		// The collection of drive statuses
extern struct panel_drive leftPanelDrive;	// The left panel
extern struct panel_drive rightPanelDrive;	// The right panel
extern struct panel_drive *selectedPanel;	// The current panel

/* METHODS */
void  initializeDrives(void);

int  getDriveStatus(
	struct drive_status *drive);

void  listDrives(enum menus menu);

extern unsigned char  checkDrive(
	unsigned char length,
	unsigned char* file,
	unsigned char drive);

int  getDirectory(
	struct panel_drive *drive,
	int slidingWindowStartAt);

void  displayDirectory(
	struct panel_drive *drive);

unsigned char  getFileType(
	unsigned char type);

void  shortenSize(
	unsigned char* buffer, 
	unsigned int value);

unsigned char*  shortenString(
	unsigned char* source);

void  writeSelectorPosition(
	struct panel_drive *panel,
	unsigned char character);

void  moveSelectorUp(
	struct panel_drive *panel);

void  moveSelectorDown(
	struct panel_drive *panel);

void  selectCurrentFile(void);

void  writeCurrentFilename(
	struct panel_drive *panel);

void  enterDirectory(
	struct panel_drive *panel);

void  leaveDirectory(
	struct panel_drive *panel);

unsigned  isDiskImage(
	struct panel_drive *panel);

unsigned  isDirectory(
	struct panel_drive *panel);

struct dir_node*  getSelectedNode(
	struct panel_drive *panel);

struct dir_node*  getSpecificNode(
	struct panel_drive *panel, 
	int index);

unsigned char  sendCommand(
	struct panel_drive *panel,
	unsigned char *command);

void  resetSelectedFiles(
	struct panel_drive *panel);

void  selectAllFiles(
	struct panel_drive *panel, 
	unsigned select);

void  moveTop(
	struct panel_drive *panel);

void  movePageUp(
	struct panel_drive *panel);

void  movePageDown(
	struct panel_drive *panel);

void  moveBottom(
	struct panel_drive *panel);
#endif