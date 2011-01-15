/***************************************************************
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

#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

/* Drive Configuration */
extern unsigned char defaultLeftDrive;		// Left Panel drive on start-up
extern unsigned char defaultRightDrive;		// Right Panel drive on start-up

/* Color Configuration */
extern unsigned char color_background;		// Background color for application
extern unsigned char color_border;			// Border color (does nothing on C= 128)
extern unsigned char color_selector;		// Color of the drive-/file-selector glyph
extern unsigned char color_text_borders;	// Color of panel borders
extern unsigned char color_text_menus;		// Color of the function-key and other menues
extern unsigned char color_text_files;		// Color of the filenames in the directory
extern unsigned char color_text_status;		// Color of the status bar and its text
extern unsigned char color_text_highlight;	// Color of text that needs to stand out
extern unsigned char color_text_other;		// Color for areas not covered above

/* Keys Configuration */
unsigned char keyMap[];
// Key Map Indices
#define KM_COPY				0u
#define KM_CREATE_D64		1u
#define KM_WRITE_D64		2u
#define KM_DELETE			3u
#define	KM_DRIVE_LEFT		4u
#define KM_DRIVE_RIGHT		5u
#define KM_DRIVE_CURRENT	6u
#define KM_DRIVE_COMMAND	7u
#define KM_HELP				8u
#define KM_MAKE_DIRECTORY	9u
#define KM_ENTER_DIRECTORY	10u
#define KM_LEAVE_DIRECTORY	11u
#define KM_PAGE_DOWN		12u
#define KM_PAGE_UP			13u
#define KM_QUIT				14u
#define KM_RENAME			15u
#define KM_REREAD_LEFT		16u
#define KM_REREAD_RIGHT		17u
#define KM_REREAD_SELECTED	18u
#define KM_SELECT			19u
#define KM_SELECT_ALL		20u
#define KM_DESELECT_ALL		21u
#define KM_TO_BOTTOM		22u
#define KM_TO_TOP			23u
#define KM_EXECUTE_SELECTED	24u
#define KM_COPY_DISK		25u


/* Methods */
void load(void);				// Loads configuration
void save(void);				// Saves configuration

#endif
