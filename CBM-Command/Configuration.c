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

//#include <stdlib.h>
//#include <stdio.h>
//#include <conio.h>
//#include <errno.h>
#ifdef __CBM__
#include <cbm.h>
#include "Configuration-CBM.h"
#endif

#include "Configuration.h"
#include "globalInput.h"
#include "globals.h"
#include "screen.h"

/* Drive Configuration */
unsigned char defaultLeftDrive;
unsigned char defaultRightDrive;

/* Color Configuration */

// Choose useful default colors for each model.
#if defined(__C128__)
unsigned char color_background	= COLOR_BLACK;
unsigned char color_border		= COLOR_BLACK;
unsigned char color_selector	= COLOR_WHITE;
unsigned char color_text_borders= COLOR_GRAY3;
unsigned char color_text_menus	= COLOR_WHITE;
unsigned char color_text_files	= COLOR_YELLOW;
unsigned char color_text_status = COLOR_GRAY3;
unsigned char color_text_other	= COLOR_WHITE;
unsigned char color_text_highlight = COLOR_YELLOW;
#elif defined(__C64__) || defined(__CBM510__)
unsigned char color_background	= COLOR_BLUE;
unsigned char color_border		= COLOR_BLUE;
unsigned char color_selector	= COLOR_WHITE;
unsigned char color_text_borders= COLOR_GRAY2;
unsigned char color_text_menus	= COLOR_GRAY3;
unsigned char color_text_files	= COLOR_GRAY3;
unsigned char color_text_status	= COLOR_GRAY2;
unsigned char color_text_other	= COLOR_GRAY3;
unsigned char color_text_highlight = COLOR_WHITE;
#elif defined(__VIC20__)
unsigned char color_background	= COLOR_WHITE;
unsigned char color_border		= COLOR_WHITE;
unsigned char color_selector	= COLOR_RED;
unsigned char color_text_borders= COLOR_BLACK;
unsigned char color_text_menus	= COLOR_BLUE;
unsigned char color_text_files	= COLOR_BLUE;
unsigned char color_text_status	= COLOR_BLUE;
unsigned char color_text_other	= COLOR_BLACK;
unsigned char color_text_highlight = COLOR_RED;
#elif defined(__PLUS4__)
unsigned char color_background	= COLOR_WHITE;
unsigned char color_border		= (BCOLOR_BLUE | CATTR_LUMA6);
unsigned char color_selector	= BCOLOR_RED;
unsigned char color_text_borders= (BCOLOR_BLUE | CATTR_LUMA6);
unsigned char color_text_menus	= BCOLOR_BLUE;
unsigned char color_text_files	= BCOLOR_BLUE;
unsigned char color_text_status	= BCOLOR_BLUE;
unsigned char color_text_other	= BCOLOR_BLACK;
unsigned char color_text_highlight = BCOLOR_YELLOW;
#else
// We don't need to define most of them on non-color systems
// because nothing on those systems will touch them.
unsigned char color_text_borders;
#endif

/* Load configuration
 * --------------------------
 * - Payton Byrd
 * --------------------------
 * Loads the configuration
 * from disk.
 */
void load(void)
{
#if defined(__CBM__)
	loadCBM();
#endif
}

#if defined(__CBM__)
void loadCBM(void)
{
#ifdef __VIC20__
	defaultLeftDrive	= *VIC_DRIVE_REGISTER & 0x0F;
	if(defaultLeftDrive < 8)
	{
		defaultLeftDrive = 8;
		*(int *)VIC_DRIVE_REGISTER = 8 + (*VIC_DRIVE_REGISTER &0xF0);
	}
	//waitForEnterEscf("LeftDrive: %u", defaultLeftDrive);
	defaultRightDrive	= (*VIC_DRIVE_REGISTER >> 4) & 0x0F;
	if(defaultRightDrive < 8)
	{
		defaultRightDrive = 8;
		*(int *)VIC_DRIVE_REGISTER = (*VIC_DRIVE_REGISTER &0x0F) + (8 << 4);
	}
	//waitForEnterEscf("RightDrive: %u", defaultRightDrive);
#else
	//cbm_open(15, _curunit, 15, "");	// open the status channel
	if (cbm_open(1,
		// Get the drive from which the program was loaded.
		defaultLeftDrive = defaultRightDrive = _curunit,
		2, ":cbmcmd-cfg."

	// We use different filenames for the various
	// models, so that different versions can be
	// on the same disk, and not have to share
	// the same configuration.
#ifdef __C64__
		"c64"
#endif
#ifdef __C128__
		"c128"
#endif
#ifdef __PET__
		"pet"
#endif
#ifdef __PLUS4__
		"plus4"
#endif
		) == 0)
	{
		// Change from the default settings only
		// if the configuration file can be read.
		if (cbm_read(1, buffer,
#ifdef COLOR_RED
			11) == 11	// expecting drives and colors on color systems
#else
			2) == 2		// expecting only drive numbers on monochrome systems
#endif
		   )
		{
			// Set the values from the configuration bytes.

			/* Drive Settings */
			defaultLeftDrive	= buffer[0];
			defaultRightDrive	= buffer[1];

// The CBM/PET clan (except the CBM510) doesn't support color.
// Don't change colors if only black and white are defined.
#ifdef COLOR_RED
			/* Color settings */
			color_background	= buffer[2];
			color_border		= buffer[3];
			color_selector		= buffer[4];
			color_text_borders	= buffer[5];
			color_text_menus	= buffer[6];
			color_text_files	= buffer[7];
			color_text_status	= buffer[8];
			color_text_other	= buffer[9];
			color_text_highlight= buffer[10];
#endif
		}
	}
	else
	{
		// The configuration drive couldn't be reached;
		// tell the user about that unusual condition.
		writeStatusBar("Config. drive failed");
		waitForEnterEsc();
	}

	// Close the channels
	cbm_close(1);
	//cbm_close(15);
#endif
}
#endif
