#ifndef _OPTIONMENU_H
#define _OPTIONMENU_H

extern char OPTION_MENU_OPTIONS[];
extern const unsigned char OPTION_MENU_OPTIONS_KEY;

extern char OPTION_MENU_SAVE[];
extern const unsigned char OPTION_MENU_SAVE_KEY;

#ifdef __C128__
extern char OPTION_MENU_TOGGLE[];
extern const unsigned char OPTION_MENU_TOGGLE_KEY;
#endif

extern const unsigned char OPTION_MENU_COUNT;

extern const unsigned char OPTION_MENU_WIDTH;

#ifdef __C128__
extern char* OPTION_MENU_LABELS[3];
extern unsigned char OPTION_MENU_KEYS[3];
#else
extern char* OPTION_MENU_LABELS[2];
extern unsigned char OPTION_MENU_KEYS[2];
#endif

void initOptionMenu(void);
void handleOptionMenu();

#endif