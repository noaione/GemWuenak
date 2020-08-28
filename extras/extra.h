#ifndef EXTRA_STUFF_H
#define EXTRA_STUFF_H

int checkAndCreateFolder(const char *folderName);
void checkAndCreateDummy(const char *fileName);
char *getSaveGameFolder();
void hideCursor();
void reshowCursor();
void setCursorPosition(int x, int y);
void clearScreen();
void to_lower(char *ch);

#endif /* EXTRA_STUFF_H */