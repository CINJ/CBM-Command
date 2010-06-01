#include <conio.h>

#include "Configuration.h"
#include "constants.h"
#include "globals.h"
#include "screen.h"

unsigned char  waitForEnterEsc(void)
{
	unsigned char key = 0;

	revers(TRUE); 
	textcolor(color_text_other); 
	cputsxy(size_x - 5, 0, "(RET)"); 
	revers(FALSE);

	while(key != CH_ESC
#if defined(__C128__) || defined(__C64__) || defined(__PET__) || defined(__VIC20__)
		&& key != CH_STOP
#endif
		&& key != CH_ENTER)
	{
		key = cgetc();
	}
	
	return key;
}