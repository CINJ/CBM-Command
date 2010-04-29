#ifndef _MENUS_H
#define _MENUS_H

//#define MENU_LEFT		0;
//#define MENU_RIGHT		1;
//#define MENU_FILE		2;
//#define MENU_COMMAND	3;
//#define MENU_OPTIONS	4;

extern unsigned char currentMenuX;
extern unsigned char currentMenuLine;

enum menus
{
	left, right, file, command, options
};

void writeMenu(enum menus);

void drawFileMenu(unsigned char);
void drawDriveMenu(unsigned char);
void drawCommandMenu(unsigned char);
void drawOptionsMenu(unsigned char);
void drawMenu(unsigned char, unsigned char, unsigned char, char*[], unsigned char[]);
void drawMenuLine(unsigned, unsigned char, char*, unsigned char, unsigned char);
#endif