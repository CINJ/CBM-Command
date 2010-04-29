#ifndef __PlatformSpecific_H
#define __PlatformSpecific_H

#ifdef __C128__

void __fastcall__ writeVdcRegister(unsigned char, unsigned char);
unsigned char __fastcall__ readVdcRegister(unsigned char);
void __fastcall__ clearVdcScreen(unsigned char hi, unsigned char lo);
void __fastcall__ copyVdcScreen(unsigned char srcHi, unsigned char desHi);

#endif

#endif