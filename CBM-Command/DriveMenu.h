#ifndef _DRIVEMENU_H
#define _DRIVEMENU_H

extern char DRIVE_MENU_ON_OFF[];
extern const unsigned char DRIVE_MENU_ON_OFF_KEY;

extern char DRIVE_MENU_REREAD[];
extern const unsigned char DRIVE_MENU_REREAD_KEY;

extern char DRIVE_MENU_DRIVE[];
extern const unsigned char DRIVE_MENU_DRIVE_KEY;

extern const unsigned char DRIVE_MENU_COUNT;

extern const unsigned char DRIVE_MENU_WIDTH;

extern char* DRIVE_MENU_LABELS[3];
extern unsigned char DRIVE_MENU_KEYS[3];

void initDriveMenu(void);
void handleDriveMenu(enum menus);

#endif