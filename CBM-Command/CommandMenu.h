#ifndef _COMMANDMENU_H
#define _COMMANDMENU_H

extern char COMMAND_MENU_SWAP_PANELS[];
extern const unsigned char COMMAND_MENU_SWAP_PANELS_KEY;

extern char COMMAND_MENU_PANELS_ON_OFF[];
extern const unsigned char COMMAND_MENU_PANELS_ON_OFF_KEY;

extern const unsigned char COMMAND_MENU_COUNT;

extern const unsigned char COMMAND_MENU_WIDTH;

extern char* COMMAND_MENU_LABELS[2];
extern unsigned char COMMAND_MENU_KEYS[2];

void initCommandMenu(void);
void handleCommandMenu();

#endif