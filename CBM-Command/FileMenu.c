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

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#ifdef __C128__
#include <c128.h>
#endif
#ifdef __CBM__
#include <cbm.h>
#endif

#include "Configuration.h"
#include "constants.h"
#include "globalInput.h"
#include "globals.h"
#include "drives.h"
#include "input.h"
#include "menus.h"
#include "screen.h"
#include "Viewer.h"
#include "CBM-REL.h"

#define D64_SIZE 689
#define D71_SIZE 1378
#define D81_SIZE 3226

static const char* const quit_message[] =
{
	"Quit CBM-Command?"
};
#define A_SIZE_QUIT A_SIZE(quit_message)

#if defined(__VIC20__) || defined(__C64__)
#define LINE_TABLE ((unsigned char[size_y])0xD9)
#define KB_COUNT (*(unsigned char*)198)
#define KB_QUEUE ((unsigned char[10])631)
#endif
#if defined(__C128__)
#define KB_COUNT (*(unsigned char*)0xD0)
#define KB_QUEUE ((unsigned char[10])0x034A)
#endif
#if defined(__PET__)
#define KB_COUNT (*(unsigned char*)0x9E)
#define KB_QUEUE ((unsigned char[10])0x026F)
#endif
#if defined(__PLUS4__)
#define KB_COUNT (*(unsigned char*)0xEF)
#define KB_QUEUE ((unsigned char[10])0x0527)
#endif


//#ifdef __C128__
//const char* FILE_MENU_LABELS[9];
//unsigned char FILE_MENU_KEYS[9];
//#else
//const char* FILE_MENU_LABELS[8];
//unsigned char FILE_MENU_KEYS[8];
//#endif
//
//void initFileMenu(void)
//{
//	static bool isInitialized = false;
//
//	if(!isInitialized)
//	{
//		FILE_MENU_LABELS[0] = FILE_MENU_ABOUT;
//		FILE_MENU_LABELS[1] = FILE_MENU_HELP;
//		FILE_MENU_LABELS[2] = FILE_MENU_COPY;
//		FILE_MENU_LABELS[3] = FILE_MENU_RENAME;
//		FILE_MENU_LABELS[4] = FILE_MENU_MAKE_DIR;
//		FILE_MENU_LABELS[5] = FILE_MENU_DELETE;
//		FILE_MENU_LABELS[6] = FILE_MENU_SEND_COMMAND;
//		FILE_MENU_LABELS[7] = FILE_MENU_QUIT;
//#ifdef __C128__
//		FILE_MENU_LABELS[8] = FILE_MENU_GO64;
//#endif
//
//		FILE_MENU_KEYS[0] = FILE_MENU_ABOUT_KEY;
//		FILE_MENU_KEYS[1] = FILE_MENU_HELP_KEY;
//		FILE_MENU_KEYS[2] = FILE_MENU_COPY_KEY;
//		FILE_MENU_KEYS[3] = FILE_MENU_RENAME_KEY;
//		FILE_MENU_KEYS[4] = FILE_MENU_MAKE_DIR_KEY;
//		FILE_MENU_KEYS[5] = FILE_MENU_DELETE_KEY;
//		FILE_MENU_KEYS[6] = FILE_MENU_SEND_COMMAND_KEY;
//		FILE_MENU_KEYS[7] = FILE_MENU_QUIT_KEY;
//#ifdef __C128__
//		FILE_MENU_KEYS[8] = FILE_MENU_GO64_KEY;
//#endif
//
//		isInitialized = true;
//	}
//}
//
//void handleFileMenu(void)
//{
//	char key;
//
//	for (;;)
//	{
//		key = getKey();
//		switch(key)
//		{
//		case CH_STOP:
//			retrieveScreen();
//			writeStatusBar("Erased menu.");
//			return;
//
//		case CH_CURS_UP:
//			if(currentMenuLine == 0) currentMenuLine = FILE_MENU_COUNT;
//			--currentMenuLine;
//			retrieveScreen();
//			drawFileMenu(currentMenuX);
//			continue;
//
//		case CH_CURS_DOWN:
//			if(++currentMenuLine == FILE_MENU_COUNT) currentMenuLine = 0;
//			retrieveScreen();
//			drawFileMenu(currentMenuX);
//			continue;
//
//		case CH_CURS_LEFT:
//			retrieveScreen();
//			writeMenu(left);
//			return;
//
//		case CH_CURS_RIGHT:
//			retrieveScreen();
//			writeMenu(options);
//			return;
//
//		case CH_ENTER:
//			key = FILE_MENU_KEYS[currentMenuLine];
//
//		default:
//			if(key == FILE_MENU_ABOUT_KEY)
//			{
//				retrieveScreen();
//				writeAboutBox();
//			}
//			else if(key == FILE_MENU_HELP_KEY)
//			{
//				retrieveScreen();
//				writeHelpPanel();
//			}
//			else if(key == FILE_MENU_COPY_KEY)
//			{
//				retrieveScreen();
//				copyFiles();
//			}
//			else if(key == FILE_MENU_RENAME_KEY)
//			{
//				retrieveScreen();
//				renameFile();
//			}
//			else if(key == FILE_MENU_MAKE_DIR_KEY)
//			{
//				retrieveScreen();
//				makeDirectory();
//			}
//			else if(key == FILE_MENU_DELETE_KEY)
//			{
//				retrieveScreen();
//				deleteFiles();
//			}
//			else if(key == FILE_MENU_SEND_COMMAND_KEY)
//			{
//				retrieveScreen();
//				inputCommand();
//			}
//			else if(key == FILE_MENU_QUIT_KEY)
//			{
//				retrieveScreen();
//				quit();
//			}
//#ifdef __C128__
//			else if(key == FILE_MENU_GO64_KEY)
//			{
//				retrieveScreen();
//				go64();
//			}
//#endif
//			else
//			{
//				continue;
//			}
//		}
//		break;
//	}
//}

void writeHelpPanel(void)
{
	viewFile(_curunit,"cbmcmd.help");
}

unsigned char fileBuffer[COPY_BUFFER_SIZE];
static struct panel_drive *targetPanel, *tempPanel;

void copyFiles(void)
{
	bool multipleSelected = false, RELOAD = false;
	unsigned numSelectors = (selectedPanel->length + (7 - 1)) / 8u;
	unsigned long totalBytes = 0;
	//clock_t timeStart;
	//time_t timeSpent;
	long timeStart = 0;
	long timeSpent = 0;
	unsigned i, k, index,  rel_current;
	char targetFilename[2 + 16 + 2 + 2 + 1], status[41], command[6];
	const struct dir_node *currentNode;
	unsigned char j, sd, td, r, rel_size;
	int bytes;
	static struct rel_file* relativeFile;
	static struct rel_file_rec relativeRecord;

	targetPanel =
		(selectedPanel == &leftPanelDrive) ? &rightPanelDrive : &leftPanelDrive;
	if (!targetPanel->visible)
	{
		return;
	}

	if ((td =   targetPanel->drive->drive) ==
		(sd = selectedPanel->drive->drive))
	{
		//saveScreen();
		writeStatusBar(
#if size_x < 40
			"Can't copy on 1 drive"
#else
			"Can't copy to the same drive"
#endif
			);
		//waitForEnterEsc();
		//retrieveScreen();
		return;
	}

	// XXX: This doesn't ignore the select-all-files overflow.  If you "select
	// all", then deselect every file one-by-one, this code still might think
	// that some files are chosen.  Fortunately, that event is rare; and,
	// "deselecting all" is the easy work-around.
	for(i=0; i<numSelectors; ++i)
	{
		if(selectedPanel->selectedEntries[i] != 0x00) multipleSelected = true;
	}
	if(!multipleSelected)
	{
		selectCurrentFile();
		writeSelectorPosition(selectedPanel, '>');
	}

#ifndef __VIC20__
#ifndef __PET__
	timeStart = time(NULL);
#endif
#endif
	for(i=0; i<numSelectors; ++i)
	{
		for(j=0; j<8; ++j)
		{
			if ((selectedPanel->selectedEntries[i] & (1 << j)) != 0x00
				&& (k = i*8+j) < selectedPanel->length - 1)
			{
				currentNode = getSpecificNode(selectedPanel, k);
				if(currentNode == NULL)
				{
					getDirectory(selectedPanel, k);
					currentNode = getSpecificNode(selectedPanel, k);
					//if(currentNode == NULL)
					//{
					//	waitForEnterEscf("Can't get file %u", k);
					//	return;
					//}
				}
#ifdef __CBM__
				/* Copy only sequential files. */
				if(currentNode->type < CBM_T_REL)
				{
					cbm_open(14, sd, 15, "");
					r = cbm_open(1, sd, 2, currentNode->name);
					if(r == 0)
					{
						sprintf(targetFilename,"@:%s,%c,w",currentNode->name,
							tolower(getFileType(currentNode->type)));
						cbm_open(15,td,15,"");
						r = cbm_open(2, td, 3, targetFilename);
						if(r == 0)
						{
							drawBox(
								getCenterX(20), getCenterY(3),
								19, 3,
								color_text_borders,
								false);

							for(index=0; index < currentNode->size; index+=(COPY_BUFFER_SIZE/254))
							{
								//writeStatusBarf("%s %u/%u",
								//	currentNode->name, index,
								//	currentNode->size);
								drawProgressBar(currentNode->name,
									index, currentNode->size);

								bytes = cbm_read(1, fileBuffer, COPY_BUFFER_SIZE);
								if(bytes <= 0)	// Catch errors
								{
									waitForEnterEscf("Problem (%u) reading %s",
										_oserror,
										currentNode->name);
									bytes = cbm_read(14,
										status, (sizeof status) - 1);
									status[bytes < 0 ? 0 : bytes] = '\0';
									writeStatusBar(status);
									waitForEnterEsc();
									break;
								}
								//if(bytes == 0)	// Catch end-of-file, too
								//{
								//	break;
								//}

								if(kbhit())
								{
									if(getKey() == CH_STOP)
									{
										cbm_close(2);
										cbm_close(1);
										cbm_close(15);
										cbm_close(14);

										reloadPanels();
										writeStatusBar("Aborted copy");
										return;
									}
								}

								if (cbm_write(2, fileBuffer, bytes) != bytes)
								{
									waitForEnterEscf("Problem (%u) writing %s",
										_oserror,
										currentNode->name);
									bytes = cbm_read(15,
										status, (sizeof status) - 1);
									status[bytes < 0 ? 0 : bytes] = '\0';
									writeStatusBar(status);
									waitForEnterEsc();
									break;
								}
#ifndef __VIC20__
#ifndef __PET__
								timeSpent = (time(NULL) - timeStart);
								writeStatusBarf("%u:%02u e.t. %d B/s",
									(unsigned)timeSpent/60u,
									(unsigned)timeSpent%60u,
									(unsigned)((totalBytes +=
										(unsigned long)bytes)/timeSpent));
#endif
#endif
							}
							//drawProgressBar("", index, currentNode->size);
							drawProgressBar("", 1, 1);	// 100%
							RELOAD = true;
						}
						else
						{
							waitForEnterEscf("Can't open %s for write (%u)",
								currentNode->name, r);
							bytes = cbm_read(15, status, (sizeof status) - 1);
							status[bytes < 0 ? 0 : bytes] = '\0';
							writeStatusBar(status);
							waitForEnterEsc();
						}
					}
					else
					{
						waitForEnterEscf("Can't open %s for read (%u)",
							currentNode->name, r);
						bytes = cbm_read(14, status, (sizeof status) - 1);
						status[bytes < 0 ? 0 : bytes] = '\0';
						writeStatusBar(status);
						waitForEnterEsc();
					}

					cbm_close(2);
					cbm_close(1);
					cbm_close(15);
					cbm_close(14);
				}
				else if(currentNode->type == CBM_T_REL)
				{
					cbm_open(127, sd, 15, "");
					cbm_open(126, td, 15, "");

					// Get record size
					rel_size = getRecordSize(127, 2, sd, 2, currentNode->name);

					// Make read filename string 
					sprintf(targetFilename, "%s,l", currentNode->name);

					// Open the source file
					r = cbm_open(2, sd, 2, targetFilename);

					// Make write filename string
					sprintf(targetFilename, "%s,l, ", currentNode->name);

					// Set the last byte to the size of the records
					targetFilename[strlen(targetFilename) - 1] = rel_size;

					// Open the target file
					cbm_open(3, td, 3, targetFilename);

					// Close it to make sure the file was created.
					cbm_close(3);

					// Reopen it
					cbm_open(3, td, 3, targetFilename);

					// Get status of target file operation
					cbm_read(126, status, sizeof status);

					// Get the first two bytes of the status
					status[2] = '\0';

					// Convert them to an integer
					r=atoi(status);

					// r == 0 means the target file was opened.
					if(r==0)
					{
						writeStatusBar("Copying file...");
						rel_current = 0;
						while(rel_current >= 0)
						{
							relativeRecord.record_number = ++rel_current;

							command[0] = 'p';
							command[1] = 98;
							command[2] = rel_current % 256;
							command[3] = rel_current / 256;
							command[4] = rel_size;

							cbm_write(127u, command, 5u);

							cbm_read(2, relativeRecord.record_data, rel_size);
								
							cbm_read(127u, status, sizeof status);
							status[2] = '\0';
							r=atoi(status);

							if(r == 0)
							{
								writeStatusBarf("Writing record %d", rel_current);

								cbm_write(3, relativeRecord.record_data, rel_size);

								totalBytes += rel_size;
							}
							else if(r == 50)
							{
								rel_current = -1;
								break;
							}
							else
							{
								waitForEnterEscf("Error - rec: %u - result: %u", rel_current, r);
								rel_current = -1;
								break;
							}

						}
					}

					writeStatusBarf("Closing ....");
					cbm_close(2); cbm_close(3);
					cbm_close(126); cbm_close(127);

					RELOAD = true;
				}
#endif
			}
		}
	}
	if(RELOAD)
	{
		reloadPanels();

#ifndef __VIC20__
#ifndef __PET__
		timeSpent = (time(NULL) - timeStart);
		writeStatusBarf("%u:%02u e.t. %d B/s",
			(unsigned)timeSpent/60u,
			(unsigned)timeSpent%60u,
			(unsigned)(totalBytes/timeSpent));
#endif
#endif
	}
}

static void reloadPanels(void)
{
	tempPanel = selectedPanel;
	selectedPanel = targetPanel;
	rereadSelectedPanel();
	selectedPanel = tempPanel;
	rereadSelectedPanel();
	//writeSelectorPosition(targetPanel, ' ');
	//writeSelectorPosition(selectedPanel, '>');
	//writeCurrentFilename(selectedPanel);
}

void renameFile(void)
{
	enum results dialogResult;
	const struct dir_node *selectedNode;
	char command[41];
	char filename[17];
	static const char* const dialogMessage[] =
	{
		{ "Enter new name" },
		{ "for file:" }
	};

	//if(selectedPanel != NULL)
	{
		selectedNode = getSelectedNode(selectedPanel);
		if(selectedNode != NULL)
		{
#if size_x > 22
			writeStatusBarf("Old name: %s",
				strcpy(filename, selectedNode->name));
#else
			writeStatusBar(
				strcpy(filename, selectedNode->name));
#endif

			//saveScreen();
			dialogResult = drawInputDialog(
				A_SIZE(dialogMessage), (sizeof filename) - 1,
				dialogMessage,
				"Rename",
				filename);
			retrieveScreen();

			if((unsigned char)dialogResult == OK_RESULT && filename[0] != '\0')
			{
				sprintf(command, "r:%s=%s",
					filename, selectedNode->name);
				sendCommand(selectedPanel, command);

				//rereadSelectedPanel();
				getDirectory(selectedPanel, selectedPanel->slidingWindowStartAt);
				displayDirectory(selectedPanel);
				writeSelectorPosition(selectedPanel, '>');

				writeStatusBarf("Renamed to %s", filename);
			}
		}
	}
}

void makeDirectory(void)
{
	enum results dialogResult;
	char command[3 + 16 + 1];
	static const char* const dialogMessage[] =
	{
		{ "Enter name for" },
		{ "new directory:" }
	};

	//if(selectedPanel != NULL)
	{
		strcpy(command, "md:");

		//saveScreen();
		dialogResult = drawInputDialog(
			A_SIZE(dialogMessage), (sizeof command) - 3 - 1,
			dialogMessage,
			"New Directory",
			&command[3]);
		retrieveScreen();

		if((unsigned char)dialogResult == OK_RESULT)
		{
			sendCommand(selectedPanel, command);

			//getDirectory(selectedPanel,
			//	selectedPanel->slidingWindowStartAt);
			//displayDirectory(selectedPanel);
			rereadSelectedPanel();
		}
	}
}

static signed char removeFile(const struct dir_node *selectedNode)
{
	char command[41];

	writeStatusBarf(
#if size_x > 22
		"Deleting %s",
#else
		"Dltng %s",
#endif
		selectedNode->name);
#ifdef __CBM__
	sprintf(command,
		(selectedNode->type == CBM_T_DIR) ? "rd:%s" : "s:%s",
		 selectedNode->name);
#else
	command[0] = '\0';
#endif
	return sendCommand(selectedPanel, command);
}

void deleteFiles(void)
{
	const struct dir_node *selectedNode;
	unsigned i, k;
	unsigned char j;


	bool dialogResult, isBatch = false;
	static const char* const dialogMessage[] =
	{
		{ "Are you sure?" }
	};

	saveScreen();
	if(writeYesNo("Delete files", dialogMessage, 1))
	{
		retrieveScreen();
		writeStatusBar("Deleting files...");
		for(i=0; i<(selectedPanel->length + (7 - 1)) / 8u; ++i)

		{
			for(j=0; j<8; ++j)

			{
				if ((selectedPanel->selectedEntries[i] & (1 << j)) != 0x00
					&& (k = i*8+j) < selectedPanel->length - 1)


				{
					isBatch = true;

					selectedNode = getSpecificNode(selectedPanel, k);
					if(selectedNode == NULL)
					{
						getDirectory(selectedPanel, k);
						selectedNode = getSpecificNode(selectedPanel, k);
					}

					if (removeFile(selectedNode) < 0 ||
						// Let us change our minds, and stop a batch delete.
						kbhit() && getKey() == CH_STOP)
					{
						rereadSelectedPanel();
						return;
					}
				}
			}
		}

		if(!isBatch)
		{
			// No names are highlighted; delete the current file.
			selectedNode = getSelectedNode(selectedPanel);
			if(selectedNode != NULL)
			{
				//saveScreen();

				writeStatusBarf(
#if size_x > 22
					"File to delete: %s",
#else
					"DEL: %s",
#endif
					selectedNode->name);

				retrieveScreen();
				writeCurrentFilename(selectedPanel);

				removeFile(selectedNode);
				rereadSelectedPanel();
			}
		}
		else
		{
			rereadSelectedPanel();
		}

	}
	else
	{
		retrieveScreen();
	}
}

#ifdef __C128__
void go64(void)
{
	if (writeYesNo("Confirm GO64", quit_message, A_SIZE_QUIT))
	{
		writeStatusBar("Going to 64 mode. Bye!");
		c64mode();
	}

	retrieveScreen();
}
#endif

void quit(void)
{
	if (writeYesNo("Confirm", quit_message, A_SIZE_QUIT))
	{
		clrscr();
		writeStatusBar("Bye!");

		(void)bordercolor(outsideFrame);
		(void)bgcolor(outsideScreen);
		(void)textcolor(outsideText);

		exit(EXIT_SUCCESS);
	}

	retrieveScreen();
}

#if 0
void writeAboutBox(void)
{
	writeStatusBar("Thanks for using CBM-Command.");
}
#endif

void executeSelectedFile(void)
{
	const struct dir_node *currentNode;
	static const char* const message[] =
	{
		{ "Read as text?" }
	};

	//if(selectedPanel != NULL)
	{
		currentNode = getSelectedNode(selectedPanel);
		if(currentNode != NULL)
		{
			switch (currentNode->type)
			{
#ifdef __CBM__
			case CBM_T_PRG:
				//saveScreen();
				if(!writeYesNo(currentNode->name, message, A_SIZE(message)))
				{
					retrieveScreen();
#ifdef KB_COUNT
					if(writeYesNo("Confirm execute", quit_message, A_SIZE_QUIT))
					{
						(void)bordercolor(outsideFrame);
						(void)bgcolor(outsideScreen);
						(void)textcolor(outsideText);
						clrscr();

// Long file-names will cause line wrap-around on the VIC-20.
// Therefore, "LOAD ... RUN" must be printed differently.
#if size_x < 40
						cprintf("lO\"%s\",%u,1",
							currentNode->name, selectedPanel->drive->drive);
						LINE_TABLE[1] = 0x10;	// link top two physical lines

						KB_QUEUE[0] = 0x13;	/* HOME */
						KB_QUEUE[1] = '\n';
						KB_QUEUE[2] = 'r';
						KB_QUEUE[3] = 'U';
						KB_QUEUE[4] = '\n';

						KB_COUNT = 5;
#else
						cprintf("lO\"%s\",%u,1\r\n\n\n\n\nrU",
							currentNode->name, selectedPanel->drive->drive);

						KB_QUEUE[0] = 0x13;
						KB_QUEUE[1] = '\n';
						KB_QUEUE[2] = '\n';

						KB_COUNT = 3;
#endif

						exit(EXIT_SUCCESS);
					}
					retrieveScreen();
#endif
					break;
				}
				retrieveScreen();
				// fall through
			case CBM_T_SEQ:
			//case CBM_T_USR:
#endif
				viewFile(selectedPanel->drive->drive,
					currentNode->name);
				retrieveScreen();
			}
		}
	}
}

void inputCommand(void)
{
	enum results dialogResult;
	char command[size_x - 4];
	unsigned char key = '\0';
	unsigned char count = 0;
	unsigned char x = 3, 
#ifdef __VIC20__
		y=size_y - 3;
#else
		y=size_y - 2;
#endif
	static const char* const dialogMessage[] =
	{
		{ "Type drive-command" }
	};

	command[0] = '\0';

	//saveScreen();
	//dialogResult = drawInputDialog(
	//	A_SIZE(dialogMessage),
	//	size_x - 4,
	//	dialogMessage,
	//	"Command",
	//	command
	//	);
	//retrieveScreen();

	//if((unsigned char)dialogResult == OK_RESULT)
	//{
	//}

	gotoxy(0, y);
	cprintf("%2u>", selectedPanel->drive->drive);

		revers(true);
	//(void)textcolor(color_text_other);
	cclearxy(x, y, size_x - 3);
		
	do
	{
		cputcxy(count + x, y, '_');
		key = getKey();

		if (count < size_x - 3 &&
			(
				(key >= ' ' && key <= '^'+1) ||
				(key >= 'A' && key <= 'Z')
			)
		   )
		{
			cputcxy(count+x, y, command[count] = key);
			++count;
		}
		else if (key ==
#ifdef CH_DEL
			CH_DEL
#else
			'\x7F'				// CH_RUBOUT
#endif
			&& count > 0)
		{
			cputcxy(count+x, y, ' ');
			--count;
		}
		command[count] = '\0';
	}
	while (key != CH_ENTER && key != CH_STOP);

	revers(false);

	if(key != CH_STOP)
	{
		sendCommand(selectedPanel, command);
		rereadSelectedPanel();
	}

	cclearxy(0, y, size_x);
}

#if defined(__CBM__) //&& !defined(__VIC20__)
//static unsigned char temp[256];
static const unsigned char l[] =	// sectors per track on 1541/1571 disks
{	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,
	19,19,19,19,19,19,19,
	18,18,18,18,18,18,
	17,17,17,17,17,
	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,
	19,19,19,19,19,19,19,
	18,18,18,18,18,18,
	17,17,17,17,17
};

void createDiskImage(void)
{
	static const char* const message[] =
	{
		{ "Type a name for" },
		{ "the disk image" }
	};
	char name[17 + 4 + 1];
	unsigned char sd, td, i, j, sectorsThisTrack, tracks;
	//struct dir_node *currentNode;
	enum results result;
	int r;
	long timeStart = 0;
	long timeSpent = 0, timeLeft = 0;
	bool isD64 = true, isD71 = false;
	unsigned int p = 0, size = D64_SIZE;

	//if(selectedPanel != NULL && selectedPanel->drive != NULL)
	{
		targetPanel = (selectedPanel == &leftPanelDrive) ?
			&rightPanelDrive : &leftPanelDrive;

		if(
			//targetPanel->drive != NULL &&
			(td =   targetPanel->drive->drive) !=
			(sd = selectedPanel->drive->drive))
		{
			//currentNode = getSelectedNode(selectedPanel);

			name[0]='\0';
			//saveScreen();
			result = drawInputDialog(
				A_SIZE(message), 17,
				message, "Make Image",
				name);
			retrieveScreen();

			if((unsigned char)result == OK_RESULT)
			{
				strlower(name);
				//if(strstr(name,".d64") == NULL &&
				//	strstr(name,".d41") == NULL)
				//{
				//	strcat(name, ".d64");
				//}

				cbm_open(15, sd, 15, "ui");
				r = cbm_read(15, buffer, (sizeof buffer) - 1);
				if(r > 0)
				{
					buffer[r] = '\0';
					if (strstr(buffer,"1541") == NULL &&
						//strstr(buffer,"1571") == NULL &&
						strstr(buffer,"2031") == NULL
					   	// for quick debugging in VICE
						&& strstr(buffer,"virtual") == NULL
						)
					{
						if(strstr(buffer,"1581") == NULL  & strstr(buffer, "1571") == NULL)
						{
							writeStatusBar("Must be 1541-type, 1571 or 1581 drive");
							//waitForEnterEsc();
							cbm_close(15);
							return;
						}
						else if(strstr(buffer,"1581") != NULL)
						{
							isD64 = false;
							isD71 = false;
							size=D81_SIZE;
//							writeStatusBar("Making D81");
//							waitForEnterEsc();
							waitForEnterEscf("Making D81. %u", size);
						}
						else // 1571, find out from user if making a D71
						{
							isD64 = !(isD71 = selectDiskImageType());
							size=(isD64 ? D64_SIZE : D71_SIZE);
						}
					}
					else
					{
//						writeStatusBar("Making D64");
//						waitForEnterEsc();
						waitForEnterEscf("Making D64. %u  %u", size, isD64);
					}
				}
				else
				{
					writeStatusBar("Error openning drive");
					//waitForEnterEsc();
					cbm_close(15);
					return;
				}

				if(cbm_open(2, sd, 2, "#") == 0)
				{
					//saveScreen();
					drawBox(
						getCenterX(20), getCenterY(3),
						19, 3,
						color_text_borders,
						false);
#ifndef __VIC20__
#ifndef __PET__
					timeStart = time(NULL);
#endif
#endif
					cbm_open(14,td,15,"");
					if(cbm_open(3,td,3,strcat(name,",p,w")) == 0)
					{
						tracks = isD64 ? 35 : (isD71 ? 70 : 80);
						for(i=0;i<tracks;++i)
						{
							sectorsThisTrack = isD64 ? l[i%35] : (isD71 ? l[i%70] : 40);
							for(j=0;j<sectorsThisTrack;++j)
							{
								if(kbhit())
								{
									if (getKey() == CH_STOP)
									{
										i=81;
										break;
									}
								}

								drawProgressBar("Making image...", ++p, size);

								cbm_write(15, buffer,
									sprintf(buffer,"u1 2 0 %u %u", i+1, j));

#ifndef __VIC20__
#ifndef __PET__
								timeSpent = (time(NULL) - timeStart);
								timeLeft =
									//((long)(size - p) * 256L) // bytes remaining
									// / (((long)p * 256L)/timeSpent);
									(long)(size - p) * timeSpent / (long)p;
								writeStatusBarf(
#if size_x < 40
									"%u:%02u et %d Bs %u:%02u",
#elif size_x < 80
									"%u:%02u et %d Bs %u:%02u rem %4u/%4u",
#else
									"%u:%02u et %d Bs %u:%02u rem %4u/%4u - %2u:%2u",
#endif
									(unsigned)timeSpent/60u,
									(unsigned)timeSpent%60u,
									(unsigned)(((long)p * 256L)/timeSpent),
									(unsigned)timeLeft/60u,
									(unsigned)timeLeft%60u
#if size_x >= 40
									, p, size
#if size_x >= 80
									, i+1, j
#endif
									);
#endif
#endif
#endif

								r = cbm_read(2,fileBuffer, 256);
								// XXX: Check that r==256.
								cbm_write(3, fileBuffer, 256);
							}
						}
						cbm_close(2); cbm_close(3);
						cbm_close(15); cbm_close(14);
#ifndef __VIC20__
#ifndef __PET__
						timeSpent = (time(NULL) - timeStart);
						retrieveScreen();
						reloadPanels();
						writeStatusBarf(
							(i == 82) ? "Stopped" : "%u:%02u e.t. %d B/s",
							(unsigned)timeSpent/60u,
							(unsigned)timeSpent%60u,
							(unsigned)(((long)size * 256L)/timeSpent));
#endif
#endif
					}
					else
					{
						r = cbm_read(14, buffer, (sizeof buffer) - 1);
						buffer[r < 0 ? 0 : r] = '\0';
						retrieveScreen();
						writeStatusBarf("Target: %s", buffer);
						cbm_close(3); cbm_close(14);
					}
				}
				else
				{
					r = cbm_read(15, buffer, (sizeof buffer) - 1);
					buffer[r < 0 ? 0 : r] = '\0';
					retrieveScreen();
					writeStatusBarf("Source: %s", buffer);
				}
				cbm_close(2); cbm_close(15);
			}
			else
			{
				writeStatusBar("Stopped");
			}
		}
	}
}

void writeDiskImage(void)
{
	static const char* const message[] =
	{
		{ "Is a blank disk" },
		{ "in the target " },
		{ "drive?" }
	};
	bool confirmed;
	unsigned char sd, td, i, j;
	const struct dir_node *currentNode;
	long timeStart = 0;
	long timeSpent = 0, timeLeft = 0;
	int r;
	unsigned int p = 0;
	unsigned char tracks;
	unsigned char sectors;

	//if(selectedPanel != NULL && selectedPanel->drive != NULL)
	{
		targetPanel = (selectedPanel == &leftPanelDrive) ?
			&rightPanelDrive : &leftPanelDrive;

		if(
			//targetPanel->drive != NULL &&
			(td =   targetPanel->drive->drive) !=
			(sd = selectedPanel->drive->drive))
		{
			currentNode = getSelectedNode(selectedPanel);

			if(currentNode->size != D64_SIZE && currentNode->size != D81_SIZE 
				&& currentNode->size != D71_SIZE - 1
				)
			{
				saveScreen();
				writeStatusBar(
#if size_x < 40
					"Not valid image"
#else
					"Not a valid image"
#endif
					);
				waitForEnterEsc();
				retrieveScreen();
				return;
			}

			//saveScreen();
			confirmed = writeYesNo("Write image?", message, A_SIZE(message));
			retrieveScreen();

			if(confirmed)
			{
				cbm_open(15, sd, 15, "");
				if(cbm_open(2, sd, 2, currentNode->name) == 0)
				{
					/*
					100 OPEN 1,8,15
					110 OPEN 2,8,2, "#"
					120 PRINT#2, "TEST DATA"
					130 PRINT#1, "U2 2 0 10 0"
					140 CLOSE 2 : CLOSE 1
					*/

					writeStatusBar("Formatting disk...");
					cbm_open(14, td, 15, "n:temp,00");
					cbm_open(3,td,3,"#");

					drawBox(
						getCenterX(20), getCenterY(3),
						19, 3,
						color_text_borders,
						false);

					writeStatusBar("Making disk...");
#ifndef __VIC20__
#ifndef __PET__
					timeStart = time(NULL);
#endif
#endif

					(void)textcolor(color_text_other);

					switch(currentNode->size)
					{
					case D64_SIZE:
						tracks = 35u;
						break;
					case D71_SIZE:
					case D71_SIZE - 1u:
						tracks = 70u;
						break;
					case D81_SIZE:
						tracks = 80u;
						break;
					}

					//waitForEnterEscf("size: %4u  tracks: %2u", currentNode->size, tracks);

					for(i=0;i<tracks;++i)
					{
						switch(currentNode->size)
						{
						case D64_SIZE:
							sectors = l[i%35];
							break;
						case D71_SIZE:
						case D71_SIZE - 1u:
							sectors = l[i%70];
							break;
						case D81_SIZE:
							sectors = 40;
							break;
						}
						for(j=0;j<sectors;++j)
						{
							if(kbhit())
							{
								if (getKey() == CH_STOP)
								{
									i=81;
									break;
								}
							}

							drawProgressBar(currentNode->name,
								++p, currentNode->size);

							r = cbm_read(2,fileBuffer,256);
							// XXX: Check that r==256.

							//memcpy(temp, (fileBuffer + 1), 256-1);
							//temp[256-1] = fileBuffer[0];

							//cbm_write(3,temp,256);
							cbm_write(14, "b-p 3 0", 7);
							cbm_write(3,fileBuffer,256);
							cbm_write(14,buffer,
								sprintf(buffer, "u2 3 0 %u %u", i+1, j));
#ifndef __VIC20__
#ifndef __PET__
							timeSpent = (time(NULL) - timeStart);
							timeLeft =
								//((long)(currentNode->size - p) * 256L) // bytes remaining
								// / (((long)p * 256L)/timeSpent);
								(long)(currentNode->size - p) * timeSpent
								/ (long)p;
							writeStatusBarf(
#if size_x < 80
								"%u:%02u e.t. %d B/s, %u:%02u rem",
#else
								"%u:%02u e.t. %d B/s, %u:%02u rem - %2u:%2u of %2u:%2u",
#endif
								(unsigned)timeSpent/60u,
								(unsigned)timeSpent%60u,
								(unsigned)(((long)p * 256L)/timeSpent),
								(unsigned)timeLeft/60u,
								(unsigned)timeLeft%60u
#if size_x >= 80
								, i + 1, j, tracks, sectors - 1
#endif
								);
#endif
#endif
						}
					}
					cbm_close(2);
					cbm_close(3);
					cbm_close(14);
					cbm_close(15);
#ifndef __VIC20__ 
#ifndef __PET__
					timeSpent = (time(NULL) - timeStart);
					retrieveScreen();
					reloadPanels();
					writeStatusBarf(
						(i == 82) ? "Stopped" : "%u:%02u e.t. %d B/s",
						(unsigned)timeSpent/60u,
						(unsigned)timeSpent%60u,
						(unsigned)(((long)currentNode->size * 256uL)/timeSpent));
#endif
#endif
					//waitForEnterEsc();
					//retrieveScreen();
				}
				else
				{
					r = cbm_read(15, buffer, (sizeof buffer) - 1);
					buffer[r < 0 ? 0 : r] = '\0';
					retrieveScreen();
					writeStatusBar(buffer);
					//waitForEnterEsc();
				}
				cbm_close(2);
				cbm_close(15);
			}
		}
	}
}

bool selectDiskImageType(void)
{
	bool result = false;

	static const char* const message[] =
	{
		{ "Is the disk" },
		{ "in the 1571 " },
		{ "double-sided?" }
	};

	result = writeYesNo("Image Type", message, A_SIZE(message));
}
#endif

void copyDisk(void)
{
	const char* const message[] =
	{
		{ "Are you ready?" }
	};

	const char* const message1571[] =
	{
		{ "Double Sided Source?" }
	};
	static bool yesNo;
	unsigned char i, j, sd, td;
	unsigned char sectorCount, currentSector;
	unsigned char trackCount, currentTrack;
	struct panel_drive *targetPanel;
	
	targetPanel = (selectedPanel == &leftPanelDrive ? &rightPanelDrive : &leftPanelDrive);

	saveScreen();
	yesNo = writeYesNo("Copy Disk", message, 1);
	retrieveScreen();

	if(yesNo)
	{
		if((strstr(selectedPanel->drive->message, "1541") != NULL && strstr(targetPanel->drive->message, "1541") != NULL)
			|| (strstr(selectedPanel->drive->message, "1541") != NULL && strcmp(targetPanel->drive->message, "1571") != NULL)
#ifdef __PLUS4__
			|| (strstr(selectedPanel->drive->message, "1551") != NULL && strcmp(targetPanel->drive->message, "1551") != NULL)
#endif
			|| (strstr(selectedPanel->drive->message, "1571") != NULL && strcmp(targetPanel->drive->message, "1571") != NULL)
			|| (strstr(selectedPanel->drive->message, "1581") != NULL && strcmp(targetPanel->drive->message, "1581") != NULL)
			)
		{
			if(strstr(selectedPanel->drive->message, "1541") != NULL) trackCount = 35;
			else if(strstr(selectedPanel->drive->message, "1571") != NULL)
			{
				saveScreen();
				trackCount = writeYesNo("1571 Detected", message1571, 1) ? 70 : 35;
				retrieveScreen();
			}
			else if(strstr(selectedPanel->drive->message, "1581") != NULL) trackCount = 80;
#ifdef __PLUS4__
			else if(strstr(selectedPanel->drive->message, "1551") != NULL) trackCount = 35;
#endif

			switch(trackCount)
			{
#ifdef __PLUS4__
			case 35: writeStatusBarf("1541/1551 Drive Copy..."); break;
#else
			case 35: writeStatusBarf("1541 Drive Copy..."); break;
#endif
			case 70: writeStatusBarf("1571 Drive Copy..."); break;
			case 80: writeStatusBarf("1581 Drive Copy..."); break;
			}
			
			sd = selectedPanel->drive->drive;
			td = targetPanel->drive->drive;

			cbm_open(15, sd, 15, "");

			cbm_open(14, td, 15, "");

			for(i = 0; i < trackCount; ++i)
			{
				sectorCount = (trackCount == 80 ? 40 : l[i]);

				cbm_open(2, sd, 2, "#");
				cbm_open(3, td, 3, "#");
				for(j = 0; j < sectorCount; ++j)
				{
					if(kbhit())
					{
						if (getKey() == CH_STOP)
						{
							i=81;
							break;
						}
					}

					cbm_write(15, buffer, sprintf(buffer,"u1 2 0 %u %u", i+1, j));

					cbm_read(2,fileBuffer, 256);

					cbm_write(14, "b-p 3 0", 7);
					cbm_write(3,fileBuffer,256);
					cbm_write(14,buffer,
						sprintf(buffer, "u2 3 0 %u %u", i+1, j));
#if size_x > 22
					writeStatusBarf("Track %u, Sector %u Copied.", i+1, j);
#else
					writeStatusBarf("%2u:%2u Copied", i+1, j);
#endif
				}
			}

			cbm_close(2);
			cbm_close(3);
			cbm_close(15);
			cbm_close(14);
		}
		else
		{
			writeStatusBarf("One or more invalid drives");
			return;
		}

		selectedPanel = targetPanel;	
		rereadSelectedPanel();
		writeSelectorPosition(selectedPanel, '>');

		writeStatusBarf("Disk copy complete.");
	}
	else
	{
		writeStatusBarf("Disk copy aborted.");
	}
}
