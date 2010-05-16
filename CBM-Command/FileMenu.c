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

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <errno.h>
#include <peekpoke.h>
#ifdef __C128__
#include <c128.h>
#endif

#include "Configuration.h"
#include "constants.h"
#include "globalInput.h"
#include "globals.h"
#include "drives.h"
#include "input.h"
#include "menus.h"
#include "screen.h"

unsigned char *quit_message[1] =
{
	"Quit CBM-Command?"
};
	

//#ifdef __C128__
//char* FILE_MENU_LABELS[9];
//unsigned char FILE_MENU_KEYS[9];
//#else
//char* FILE_MENU_LABELS[8];
//unsigned char FILE_MENU_KEYS[8];
//#endif
//
//void __fastcall__ initFileMenu(void)
//{
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
//
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
//
//#ifdef __C128__
//		FILE_MENU_KEYS[8] = FILE_MENU_GO64_KEY;
//#endif
//
//		isInitialized = TRUE;
//	}
//}
//
//void __fastcall__ handleFileMenu(void)
//{
//	unsigned char key;
//	unsigned handleKeys = TRUE;
//
//	while(handleKeys)
//	{
//		key = cgetc();
//		handleKeys = FALSE;
//		switch((int)key)
//		{
//#ifdef __C128__
//		case CH_ESC:
//#endif
//		case CH_STOP:
//			retrieveScreen();
//			writeStatusBar("Escaping menu...");
//			return;
//			break;
//
//		case CH_CURS_UP:
//			if(currentMenuLine == 0) currentMenuLine = FILE_MENU_COUNT - 1;
//			else currentMenuLine--;
//			retrieveScreen();
//			drawFileMenu(currentMenuX);
//			handleKeys = TRUE;
//			break;
//
//		case CH_CURS_DOWN:
//			if(currentMenuLine == FILE_MENU_COUNT - 1) currentMenuLine = 0;
//			else currentMenuLine++;
//			retrieveScreen();
//			drawFileMenu(currentMenuX);
//			handleKeys = TRUE;
//			break;
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
//				handleKeys = TRUE;
//			}
//			break;
//		}
//	}
//}

void __fastcall__ writeHelpPanel(void)
{
	writeStatusBar("cbmcommand.codeplex.com/documentation");
	//unsigned char* dialogMessage[] =
	//{
	//	{ "Please visit" },
	//	{ "http://cbmcommand.codeplex.com/" },
	//	{ "    documentation" }
	//};

	//saveScreen();

	//drawDialog(
	//	dialogMessage, 3, "Help",
	//	OK);

	//retrieveScreen();
}

unsigned char fileBuffer[COPY_BUFFER_SIZE];
struct panel_drive *targetPanel = NULL, *tempPanel = NULL;
void __fastcall__ copyFiles(void)
{
	unsigned char i = 0, j = 0, sd = 0, td = 0, bit = 0, r = 0;
	unsigned int index = 0, bytes = 0;
	unsigned RELOAD = FALSE;
	unsigned char targetFilename[21], type[2], status[40];
	struct dir_node *currentNode;

	if(selectedPanel == &leftPanelDrive)
	{
		targetPanel = &rightPanelDrive;
	}
	else
	{
		targetPanel = &leftPanelDrive;
	}

	sd = selectedPanel->drive->drive;
	td = targetPanel->drive->drive;

	if(sd == td)
	{
		saveScreen();
		writeStatusBar("Cannot copy to the same drive.");
		waitForEnterEsc();
		retrieveScreen();
		return;
	}

	for(i=0; i<selectedPanel->length / 8 + 1; ++i)
	{
		for(j=0; j<8; ++j)
		{
			bit = 1 << j;
			r = selectedPanel->selectedEntries[i] & bit;
			if(r != 0)
			{
				currentNode = getSpecificNode(selectedPanel, i*8+j);
				if(currentNode->type < 4)
				{
					if(currentNode == NULL)
					{
						getDirectory(selectedPanel, i*8+j);
						currentNode = getSpecificNode(selectedPanel, i*8+j);
						{
							if(currentNode == NULL)
							{
								writeStatusBarf("Cannot get file %u", i*8+j); 
								waitForEnterEsc();
								return;
							}
						}
					}

					cbm_open(15, sd, 15, "");
					r = cbm_open(1, sd, 2, currentNode->name);					
					if(r == 0)
					{
						sprintf(type, "%c", getFileType(currentNode->type));
						strlower(type);
						sprintf(targetFilename,"@0:%s,%s,w",currentNode->name,type);
						cbm_open(14,td,15,"");
						r = cbm_open(2, td, 3, targetFilename);
						if(r == 0)
						{
							for(index=0; index < currentNode->size; index+=(COPY_BUFFER_SIZE/254))
							{
								bytes = cbm_read(1, fileBuffer, COPY_BUFFER_SIZE);
								if(bytes == -1)
								{
									writeStatusBarf("Problem (%d) reading %s", 
										_oserror, 
										currentNode->name); 
									waitForEnterEsc();
									cbm_read(15, status, 40);
									writeStatusBar(status); waitForEnterEsc();
									break;
								}
								else if(bytes == EOF)
								{
									break;
								}

								if(kbhit())
								{
									r = cgetc();
									if(r == CH_ESC || r == CH_STOP)
									{
										cbm_close(2); 
										cbm_close(1);
										cbm_close(15);
										cbm_close(14);

										reloadPanels();

										writeStatusBar("Aborted copy.");
										return;
									}

								}

								r = cbm_write(2, fileBuffer, bytes);
								if(r == -1)
								{
									writeStatusBarf("Problem (%d) writing %s", 
										_oserror, 
										currentNode->name); 
									waitForEnterEsc();
									cbm_read(14, status, 40);
									writeStatusBar(status); waitForEnterEsc();
									break;
								}
								writeStatusBarf("%s - %d of %d.", currentNode->name, index, currentNode->size);
							}
							RELOAD = TRUE;
						}
						else
						{
							writeStatusBarf("Cannot open %s for write (%d)", 
								currentNode->name, r); 
							waitForEnterEsc();
							cbm_read(14, status, 40);
							writeStatusBar(status); waitForEnterEsc();
						}
					}
					else
					{
						writeStatusBarf("Cannot open %s for read (%d)", 
							currentNode->name, r); 
						waitForEnterEsc();
						cbm_read(15, status, 40);
						writeStatusBar(status); waitForEnterEsc();
					}
					cbm_close(2); 
					cbm_close(1);
					cbm_close(15);
					cbm_close(14);
				}
			}
		}
	}
	if(RELOAD == TRUE)
	{
		reloadPanels();
	}
}

void __fastcall__ reloadPanels(void)
{
	tempPanel = selectedPanel;
	selectedPanel = targetPanel;
	rereadSelectedPanel();
	selectedPanel = tempPanel;
	rereadSelectedPanel();
	writeSelectorPosition(selectedPanel, '>');
	writeSelectorPosition(targetPanel, ' ');
	writeCurrentFilename(selectedPanel);
}

void __fastcall__ renameFile(void)
{
	enum results dialogResult;
	struct dir_node *selectedNode = NULL;
	unsigned char command[40];
	unsigned char filename[17];
	unsigned char* dialogMessage[] =
	{
		{ "Enter new name" },
		{ "for file:" }
	};

	if(selectedPanel != NULL)
	{
		selectedNode = getSelectedNode(selectedPanel);
		if(selectedNode != NULL)
		{
			saveScreen();

			writeStatusBarf("Old name: %s", selectedNode->name);

			dialogResult = drawInputDialog(
				2, 16,
				dialogMessage,
				"Rename File",
				filename);

			retrieveScreen();

			if(dialogResult == OK_RESULT)
			{
				writeStatusBarf("Renaming to %s", filename);

				sprintf(command, "r0:%s=%s",
					filename, selectedNode->name);

				sendCommand(selectedPanel, command);

				rereadSelectedPanel();

				writeStatusBarf("Renamed to %s", filename);
			}
		}
	}
}

void __fastcall__ makeDirectory(void)
{
	enum results dialogResult;
	struct dir_node *selectedNode = NULL;
	unsigned char command[40];
	unsigned char filename[17];
	unsigned char* dialogMessage[] =
	{
		{ "Enter name for" },
		{ "new directory:" }
	};

	if(selectedPanel != NULL)
	{
			saveScreen();

			dialogResult = drawInputDialog(
				2, 16,
				dialogMessage,
				"New Directory",
				filename);

			retrieveScreen();

			if(dialogResult == OK_RESULT)
			{
				sprintf(command, "md:%s",
					filename);

				sendCommand(selectedPanel, command);

				getDirectory(selectedPanel, 
					selectedPanel->slidingWindowStartAt);
				displayDirectory(selectedPanel);
			}
	}
}

void __fastcall__ deleteFiles(void)
{
	unsigned dialogResult;
	struct dir_node *selectedNode = NULL;
	unsigned char command[40];
	unsigned char* dialogMessage[] =
	{
		{ "Are you sure?" }
	};

	if(selectedPanel != NULL)
	{
		selectedNode = getSelectedNode(selectedPanel);
		if(selectedNode != NULL)
		{
			saveScreen();

			writeStatusBarf("File to delete: %s", selectedNode->name);

			dialogResult = writeYesNo(
				"Delete File",
				dialogMessage,
				1);

			retrieveScreen();

			if(dialogResult == TRUE)
			{
				writeStatusBarf("Deleting %s", selectedNode->name);

				if(selectedNode->type != 6)
				{
					sprintf(command, "s0:%s", selectedNode->name);
				}
				else
				{
					sprintf(command, "rd:%s", selectedNode->name);
				}

				sendCommand(selectedPanel, command);

				rereadSelectedPanel();
				//getDirectory(selectedPanel, 
				//	selectedPanel->slidingWindowStartAt);

				//displayDirectory(selectedPanel);
			}
		}
	}
}

#ifdef __C128__
void __fastcall__ go64(void)
{
	unsigned result;

	saveScreen();

	result = writeYesNo("Confirm GO64", quit_message, 1);
	
	if(result == TRUE)
	{
		writeStatusBar("Going to 64 mode.  Goodbye!");
		c64mode();
	}
}
#endif

void __fastcall__ quit(void)
{
	unsigned result;

	saveScreen();

	result = writeYesNo("Confirm", quit_message, 1);
	
	if(result == TRUE)
	{
		writeStatusBar("Goodbye!");
		exit(EXIT_SUCCESS);
	}

	retrieveScreen();
}

void __fastcall__ writeAboutBox(void)
{
//	unsigned char x, y, i;
//	unsigned char oldColor;
//	unsigned char oldReverse;
//
//	const unsigned char w = 25;
//	const unsigned char h = 11;
//	
//	unsigned char* lines[7] =
//		{
//			"Copyright 2010",
//			"Payton Byrd",
//			"version 2010-05-01",
//			"Thanks to Uz for CC65",
//			"and all the support!",
//			"",
//#ifdef __C128__
//			"C128 Edition"
//#else
//			"C64 Edition"
//#endif
//	};
//
//
//	x = getCenterX(w);
//	y = getCenterY(h);
//
//	writePanel(TRUE, TRUE,
//		COLOR_WHITE, 
//		x, y, h, w,
//		"About CBM-Command",
//		NULL, "OK");
//
//	oldReverse = revers(FALSE);
//	oldColor = textcolor(COLOR_WHITE);
//	y = getCenterY(7);
//	for(i=0; i<7; i++)
//	{
//		x = getCenterX(strlen(lines[i]));
//		gotoxy(x, y + i);
//		cputs(lines[i]);
//	}
//
//	revers(oldReverse);
//	textcolor(oldColor);
//
//	waitForEnterEsc();
//
//	retrieveScreen();
//
//	writeStatusBar("Thank you for using CBM Command.", 0, 10);
	writeStatusBarf("Thank You for using CBM-Command Alpa");
}

void __fastcall__ executeSelectedFile(void)
{
	struct dir_node *currentNode;
	unsigned result;

	if(selectedPanel != NULL)
	{
		currentNode = getSelectedNode(selectedPanel);

		if(currentNode != NULL && currentNode->type == 2)
		{
			saveScreen();

			result = writeYesNo("Confirm", quit_message, 1);

			retrieveScreen();
	
			if(result == TRUE)
			{
				clrscr();
#ifdef __C64__
				POKE(631,'r');
				POKE(632,'U');
				POKE(633,13);
				POKE(198,3);
#endif
#ifdef __C128__
				POKE(0x034A,'r');
				POKE(0x034B,'U');
				POKE(0x034C,13);
				POKE(0x00D0,3);
#endif
				writeStatusBarf("Loading %s", currentNode->name);
				cbm_load(currentNode->name, selectedPanel->drive->drive, NULL);
				exit(EXIT_SUCCESS);
			}
		}
	}
}

void __fastcall__ inputCommand(void)
{
	enum results dialogResult;
	struct dir_node *selectedNode = NULL;
	unsigned char command[77];
	unsigned char* dialogMessage[] =
	{
		{ "Enter Command for drive:" }
	};

	if(selectedPanel != NULL)
	{
		selectedNode = getSelectedNode(selectedPanel);
		if(selectedNode != NULL)
		{
			saveScreen();

			dialogResult = drawInputDialog(
				1, 
#ifdef __C64__
				36,
#endif
#ifdef __C128__
				76,
#endif
				dialogMessage,
				"Command",
				command
				);

			retrieveScreen();

			if(dialogResult == OK_RESULT)
			{
				sendCommand(selectedPanel, command);

				waitForEnterEsc();

				rereadSelectedPanel();				
			}
		}
	}
}

unsigned char temp[256];
void __fastcall__ writeD64(void)
{
	unsigned confirmed = FALSE;
	unsigned char *message[] =
	{
		{ "Is a formatted, blank disk" },
		{ "in the target drive?" }
	};
	unsigned char sd, td,  i, j, t;
	int r,p;
	struct dir_node *currentNode;
	unsigned char l[] =
	{	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,
		19,19,19,19,19,19,19,
		18,18,18,18,18,18,
		17,17,17,17,17
	};

	if(selectedPanel != NULL && selectedPanel->drive != NULL)
	{
		if(selectedPanel == &leftPanelDrive)
		{
			targetPanel = &rightPanelDrive;
		}
		else
		{
			targetPanel = &leftPanelDrive;
		}

		if(targetPanel->drive != NULL &&
			targetPanel->drive->drive != 
				selectedPanel->drive->drive)
		{
			currentNode = getSelectedNode(selectedPanel);

			if(currentNode->size != 689)
			{
				saveScreen();
				writeStatusBarf("%s is not a valid D64.",
					currentNode->name);
				waitForEnterEsc();
				retrieveScreen();
				return;
			}

			saveScreen();
			confirmed = writeYesNo("Write D64", message, 2);
			retrieveScreen();

			if(confirmed == TRUE)
			{
				

				sd = selectedPanel->drive->drive;
				td = targetPanel->drive->drive;

				cbm_open(15, sd, 15, "");
				r = cbm_open(2, sd, 2, currentNode->name);
				if(r == 0)
				{
					/*

					100 OPEN 1,8,15
					110 OPEN 2,8,2, "#"
					120 PRINT#2, "TEST DATA"
					130 PRINT#1, "U2 2 0 10"
					140 CLOSE 2 : CLOSE 1

					*/
					cbm_open(14, td, 15, "");
					cbm_write(14,"n0:temp,00",10);
					writeStatusBar("Formatting disk...");
					cbm_open(3,td,3,"#");
					writeStatusBarf("Writing %s", currentNode->name);
					writePanel(TRUE, FALSE, color_text_borders,
						0, 1, 20, size_x - 1 
						,
						"Writing D64........", NULL, NULL);
					for(i=0;i<35;++i)
					{
						for(j=0;j<l[i];++j)
						{
							if(kbhit())
							{
								t = cgetc();
								if(t == CH_STOP || t == CH_ESC)
								{
									i=41;
									break;
								}
							}
							gotoxy(2,1); cprintf("Writing %2d,%2d", i+1, j);// waitForEnterEsc();

							r = cbm_read(2,fileBuffer,256);

							memcpy(temp, (fileBuffer + 1), r-1);
							temp[r-1] = fileBuffer[0];

							//textcolor(color_text_other);
							//for(p=0; p<r; ++p)
							//{
							//	/*if(p == 0) temp[r - 1] = fileBuffer[0];
							//	else temp[p-1] = fileBuffer[p];*/

							//	gotoxy(p%16*3+2, p/16+3); 
							//	cprintf("%2X ", fileBuffer[p]);
							//}

							//textcolor(color_text_menus);
							//for(p=0; p<r; ++p)
							//{
							//	gotoxy(p%16*3+2, p/16+3); 
							//	cprintf("%2X ", temp[p]);
							//}

							cbm_write(3,temp,256);

							sprintf(buffer, "u2 3 0 %d %d", i+1, j);
							cbm_write(14,buffer,strlen(buffer));
//waitForEnterEsc();

							sprintf(buffer, "u1 3 0 %d %d", i+1, j);
							cbm_write(14,buffer,strlen(buffer));
							cbm_read(3,fileBuffer,256);

							//textcolor(color_text_highlight);
							//for(p=0; p<256; ++p)
							//{

							//	gotoxy(p%16*3+2, p/16+3); 
							//	cprintf("%2X ", fileBuffer[p]);
							//}
//waitForEnterEsc();
						}
					}
					cbm_close(2);
					cbm_close(3);
					cbm_close(14);
					cbm_close(15);
					reloadPanels();
					writeStatusBarf("Done writing %s.", currentNode->name); //waitForEnterEsc();
				}
				else
				{
					cbm_read(15, buffer, 40);
					writeStatusBar(buffer); waitForEnterEsc();
				}
			}
		}
	}
}