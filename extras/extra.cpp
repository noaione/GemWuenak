#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "extra.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

int checkAndCreate(const char *folderName) {
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
    checkAndCreate(saveFolder);
    return saveFolder;
}


int main() {
    char *gamefolder = getSaveGameFolder();
    printf("%s", gamefolder);
}