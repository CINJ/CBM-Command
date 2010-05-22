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

#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

/* Drive Configuration */
extern unsigned char defaultLeftDrive;		// Left Panel drive on startup
extern unsigned char defaultRightDrive;		// Right Panel drive on startup

/* Color Configuration */
extern unsigned char color_background;		// Background color for application
extern unsigned char color_border;			// Border color (does nothing on C= 128)
extern unsigned char color_selector;		// Color of the drive/file selector glyph
extern unsigned char color_text_borders;	// Color of panel borders
extern unsigned char color_text_menus;		// Color of the function key and other menus
extern unsigned char color_text_files;		// Color of the filenames in the directory
extern unsigned char color_text_status;		// Color of the status bar and its text
extern unsigned char color_text_highlight;  // Color of text that needs to stand out
extern unsigned char color_text_other;		// Color for areas not covered above

/* Methods */
void  load(void);				// Loads configuration
void  save(void);				// Saves configuration

#endif