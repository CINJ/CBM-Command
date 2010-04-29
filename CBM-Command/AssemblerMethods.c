#include <6502.h>
#include "AssemblerMethods.h"

#if defined(__C128__)
unsigned char getScreenSize(
	unsigned char* x, 
	unsigned char* y)
{	
	struct regs r;
	r.pc = SCRORG;

	_sys(&r);
	
	(*x) = r.x + 1;
	(*y) = r.y + 1;

	return r.a;
}
#endif