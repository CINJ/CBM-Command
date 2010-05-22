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

#ifndef _SCREEN_H
#define _SCREEN_H



enum results { OK_RESULT, CANCEL_RESULT, YES_RESULT, NO_RESULT };
enum buttons { OK = 1, CANCEL = 2, YES = 4, NO = 8 };

//enum buttonTypes { cancel, ok, other };
//typedef void *ButtonCallback(enum buttonTypes buttonType);

void setupScreen(void);
void  writeStatusBar(unsigned char[]);

void writeStatusBarf(
	unsigned char[], ...);
	

void writePanel(
	unsigned drawBorder,
	unsigned reverse,
	unsigned char color,
	unsigned char x, unsigned char y,
	unsigned char h, unsigned char w,
	unsigned char *title,
	unsigned char *cancel,
	unsigned char *ok);


void drawBox(
	unsigned char, unsigned char,
	unsigned char, unsigned char,
	unsigned char, unsigned);

enum results  drawDialog(
	unsigned char* message[],
	unsigned char lineCount,
	unsigned char* title,
	enum buttons button);

unsigned  writeYesNo(
	unsigned char *title,
	unsigned char *message[],
	unsigned char lineCount);

enum results  drawInputDialog(
	unsigned char lineCount,
	unsigned char length,
	unsigned char *message[],
	unsigned char *title,
	unsigned char *resultText);

void  saveScreen(void);
void  retrieveScreen(void);

void  notImplemented(void);

unsigned char  getCenterX(unsigned char w);
unsigned char  getCenterY(unsigned char h);
#endif