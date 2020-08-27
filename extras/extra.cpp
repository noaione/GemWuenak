#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "extra.h"

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#endif


int checkAndCreateFolder(const char *folderName) {
    struct stat fst = {0};
    int res;
    if (stat(folderName, &fst) == -1) {
#ifdef _WIN32
        res = mkdir(folderName);
#else
        res = mkdir(folderName, 0700);
#endif
    }
    return res;
}

void checkAndCreateDummy(const char *fileName) {
    struct stat fst = {0};
    if (stat(fileName, &fst) == -1) {
        FILE *fptr;
        fptr = fopen(fileName, "w");
        fprintf(fptr, "\0");
        fclose(fptr);
    }
}

char *getSaveGameFolder() {
#ifdef _WIN32
    char *saveFolder = getenv("APPDATA");
    strcat(saveFolder, "/GemWuenak/");
#else
    char *saveFolder = getenv("HOME");
    strcat(saveFolder, "/.GemWuenak/");
#endif
    checkAndCreateFolder(saveFolder);
    return saveFolder;
}

void hideCursor() {
#ifdef _WIN32
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
#else
    printf("\e[?25l");
#endif
}

void setCursorPosition(int x, int y) {
#ifdef _WIN32
	COORD cursorPosition; 
	cursorPosition.X = x; 
	cursorPosition.Y = y;	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
#else
    printf("\033[%d;%dH", x + 1, y + 1);
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls"); // In Windows
#else
    printf("\033[2J"); // In Linux/macOS hopefully.
#endif
}

void to_lower(char *ch)
{
    if (*ch >= 'A' && *ch <= 'Z')
    {
        *ch += 32;
    }
}


// int main() {
//     char *gamefolder = getSaveGameFolder();
//     printf("%s", gamefolder);
// }