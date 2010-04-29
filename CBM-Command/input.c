#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "input.h"
#include "menus.h"
#include "screen.h"

void readKeyboard(void)
{
	unsigned char key;
	unsigned char buffer[39];

	key = cgetc();

	switch((int)key)
	{
	case 188: // C= C - Command Menu
		writeMenu(command);
		break;
	case 182: // C= L - Left Menu
		writeMenu(left);
		break;
	case 178: // C= R - Right Menu
		writeMenu(right);
		break;
	case 187: // C= F - File Menu
		writeMenu(file);
		break;
	case 185: // C= O - Options Menu
		writeMenu(options);
		break;
	default:
		sprintf(buffer, "%c", key);
		writeStatusBar(buffer, 0, 20);
	}
}