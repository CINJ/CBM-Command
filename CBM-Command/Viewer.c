
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <cbm.h>
#include <string.h>

#include "Viewer.h"
#include "constants.h"
#include "globalInput.h"
#include "globals.h"
#include "drives.h"
#include "screen.h"
#include "menus.h"

void viewFile(
	unsigned char drive,
	unsigned char *filename)
{
//#ifndef __VIC20__
	int r = 0, bufferSize = 0, i = 0;
	
	unsigned char 
		currentLine = 1, 
		counter = 0;

	unsigned printLine = FALSE;

	unsigned char file[22];
	unsigned char line[81];
	unsigned char word[81];
	unsigned char character = 0, last = 0;

	strcpy(file, filename);
	strcat(file, ",s,r");

	cbm_open(15,drive,15,"");

	r = cbm_open(2,drive,2,file);

	if(r == 0)
	{
		saveScreen();

		clrscr();

		counter = 0;
		memset(word, '\0', 81);
		memset(line, '\0', 81);
		bufferSize = sizeof(fileBuffer);
		do
		{
			memset(fileBuffer, '\0', bufferSize);

			r = cbm_read(2, fileBuffer, bufferSize);

			if(r > 0)
			{
				for(i=0; i<r; ++i)
				{
					last = character;
					character = fileBuffer[i];
					if(character == ' ' || 
						character == '\r' || 
						character == '\n')
					{

						if(character == ' ')
						{
							strcat(line, word);
							line[strlen(line)] = ' ';
							memset(word, '\0', 81);
							counter = 0;
						}
						else if(
							(character == '\r' && last != '\n') ||
							(character == '\n' && last != '\r'))
						{
							strcat(line, word);
							memset(word, '\0', 81);
							counter = 0;

							printLine = TRUE;
						}
					}
					else
					{
						word[counter] = character;
						++counter;

						if(strlen(line) + counter > size_x - 1)
						{
							printLine = TRUE;
						}
					}

					if(printLine == TRUE)
					{
						cputsxy(0, currentLine, line);
						++currentLine;
						printLine = FALSE;
						memset(line, '\0', 81);

						if(currentLine == size_y - 1)
						{
#ifndef __VIC20__
							writeStatusBar("RETURN to cont, STOP/ESC to end.");
#else
							writeStatusBar("STOP to end.");
#endif
							if(waitForEnterEsc() == CH_ENTER)
							{
								clrscr();
								currentLine = 1;
							}
							else
							{
								cbm_close(2); cbm_close(15);
								retrieveScreen();
								return;
							}
						}
					}
				} // FOR
			}
		}
		while(r == bufferSize);

		if(strlen(word) > 0)
		{
			strcat(line, word);
		}

		if(strlen(line) > 0)
		{
			if(currentLine >= size_y)
			{
				clrscr();
				currentLine = 1;
			}

			cputsxy(0, currentLine, line);
		}

		waitForEnterEscf("Done reading %s", filename);
		retrieveScreen();
	}
	else
	{
		cbm_read(15, buffer, 40);
		waitForEnterEscf(buffer); 
	}

	cbm_close(2); cbm_close(15);
//#endif
}