#ifndef _ASSEMBLERMETHODS_H
#define _ASSEMBLERMETHODS_H

#if defined(__C128__)
// Defines the Kernel Routine SCRORG which returns the current
// screen mode on the accumulator.
#define SCRORG 0xFFED
//#define getScreenSize   ((unsigned char (*)()) (SCRORG))
unsigned char getScreenSize(unsigned char*, unsigned char*);
#endif

#endif