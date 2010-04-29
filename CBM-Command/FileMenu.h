#ifndef _FILEMENU_H
#define _FILEMENU_H

extern char FILE_MENU_ABOUT[];
extern const unsigned char FILE_MENU_ABOUT_KEY;

extern char FILE_MENU_HELP[];
extern const unsigned char FILE_MENU_HELP_KEY;

extern char FILE_MENU_COPY[];
extern const unsigned char FILE_MENU_COPY_KEY;

extern char FILE_MENU_RENAME[];
extern const unsigned char FILE_MENU_RENAME_KEY;

extern char FILE_MENU_MAKE_DIR[];
extern const unsigned char FILE_MENU_MAKE_DIR_KEY;

extern char FILE_MENU_DELETE[];
extern const unsigned char FILE_MENU_DELETE_KEY;

extern char FILE_MENU_FILE_INFO[];
extern const unsigned char FILE_MENU_FILE_INFO_KEY;

extern char FILE_MENU_QUIT[];
extern const unsigned char FILE_MENU_QUIT_KEY;

#ifdef __C128__
extern char FILE_MENU_GO64[];
extern const unsigned char FILE_MENU_GO64_KEY;
#endif

extern const unsigned char FILE_MENU_COUNT;

extern const unsigned char FILE_MENU_WIDTH;

#ifdef __C128__
extern char* FILE_MENU_LABELS[9];
extern unsigned char FILE_MENU_KEYS[9];
#else
extern char* FILE_MENU_LABELS[8];
extern unsigned char FILE_MENU_KEYS[8];
#endif

void initFileMenu(void);
void handleFileMenu();
void __fastcall__ writeAboutBox(void);
#endif