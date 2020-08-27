#include <iso646.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#include "highscore.h"
#include "../extras/extra.h"

#define keyEnter 13

highscore leaderboard[11];	
int currIdx;

void swap(highscore *a, highscore *b) {
	highscore temp = *a;
	*a = *b;
	*b = temp;
}

void listName() {
	FILE *fptr;
	char *flapScoreName = getSaveGameFolder();
	strcat(flapScoreName, "flappybird/");
	checkAndCreateFolder(flapScoreName);
	strcat(flapScoreName, "highscore_name.txt");
	checkAndCreateDummy(flapScoreName);
	fptr = fopen(flapScoreName, "r");

	currIdx = 0;
	while(fscanf(fptr, "%s", leaderboard[currIdx].name) != EOF) {
		currIdx++;
	}

	fclose(fptr);
}

void listScore() {
	FILE *fptr;
	char *flapScore = getSaveGameFolder();
	strcat(flapScore, "flappybird/");
	checkAndCreateFolder(flapScore);
	strcat(flapScore, "highscore_score.txt");
	checkAndCreateDummy(flapScore);
	fptr = fopen(flapScore, "r");

	currIdx = 0;
	while(fscanf(fptr, "%d", &leaderboard[currIdx].score) != EOF) {
		currIdx++;
	}

	fclose(fptr);
}

void processScore(highscore a) { // masukkan a ke leaderboard, sort.
	FILE *fptr1, *fptr2;

	listName();
	listScore();
	leaderboard[currIdx] = a;
	if(currIdx < 10) currIdx++;

	for(int i = 0; i < currIdx + 1; i++) {
		for(int j = 0; j < currIdx - i; j++) {
			if(leaderboard[j].score < leaderboard[j + 1].score) {
				swap(&leaderboard[j], &leaderboard[j + 1]);
			}
		}
	}

	char *flapScore = getSaveGameFolder();
	char *flapScoreName;
	strcat(flapScore, "flappybird/");
	checkAndCreateFolder(flapScore);
	strcpy(flapScoreName, flapScore);
	strcat(flapScore, "highscore_score.txt");
	strcat(flapScoreName, "highscore_name.txt");

	fptr1 = fopen(flapScoreName, "w");
	fptr2 = fopen(flapScore, "w");

	for(int i = 0; i < currIdx; i++) {
		fprintf(fptr1, "%s\n", leaderboard[i].name);
		fprintf(fptr2, "%d\n", leaderboard[i].score);
	}

	fclose(fptr1);
	fclose(fptr2);
}

void inputUsername(int score) {
	/* VARIABLE */
	char username[20];
	int len;

	clearScreen();
	setCursorPosition(0, 0);

	puts("");

	puts("\tInput username: (length must be between 2 - 16 characters)");
	do {
		printf("\t");
		scanf("%s", username);
		len = strlen(username);

		if(len < 2 or len > 16) {
			printf("\tLength must be between 2 - 16 characters! Press Enter to retry.");

			do {
				// can only continue if enter key is pressed
			} while(getch() != 13);

			for(int i = 0; i < 63; i++) printf("\b");
			for(int i = 0; i < 63; i++) printf(" ");
			printf("\033[A"); // balik ke atas
			for(int i = 0; i < len + 64; i++) printf("\b");
			for(int i = 0; i < len + 64; i++) printf(" ");
			printf("\r");
		}
	} while(len < 2 or len > 16);

	highscore player;
	strcpy(player.name, username);
	player.score = score;
	processScore(player);
}

void printLeaderboardTitle(int *num) {
	int title[5][69] = {{1,1,0,0,0,1,1,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0},
						{1,1,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0},
						{1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0},
						{1,1,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0},
						{1,1,0,0,0,1,1,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,0}};

	clearScreen();
	hideCursor(); // hide cursor
	// set cursor ke 0, 0
	setCursorPosition(0, 0); // gunanya sebagai alternatif dari clear screen, tapi lebih cepat	


	puts(""); // kasih jarak dari pojok atas
	for(int i = 0; i < 5; i++) { // print tulisan hangman
		printf("\t");
		for(int j = 0; j < 69; j++) {
			if(title[i][j]) { // kalau titleScreen[i][j] = 1 --> merupakan bagian text
				int state = (j + *num + 3 * i) % 69;
				if((0 <= state and state <= 9) or (60 <= state and state <= 69)) {
					printf("%c", char(176));
				}
				else if((10 <= state and state <= 19) or (50 <= state and state <= 59)) {
					printf("%c", char(177));
				}
				else if((20 <= state and state <= 29) or (40 <= state and state <= 49)) {
					printf("%c", char(178));
				}
				else {
					printf("%c", char(219));
				}
			}
			else printf(" ");
		}
		puts("");
	}
}

void printLeaderboard() {
	clearScreen();
	setCursorPosition(0, 0);

	highscore dummy; // trigger dia process leaderboard
	strcpy(dummy.name, "------");
	dummy.score = -1;
	processScore(dummy);
	
	char s[255];
	int num = 0;

	printLeaderboardTitle(&num);
	printf("\t");
	for(int i = 0; i < 68; i++) printf("=");
	puts("");
	for(int i = 0; i < 10; i++) {
		if(strcmp(leaderboard[i].name, "------") != 0) {
			printf("\t");
			for(int i = 0; i < 68; i++) {
				if(i == 0) printf("%c", char(201));
				else if(i == 33) printf("%c", char(203));
				else if(i == 67) printf("%c", char(187));
				else printf("%c", char(205));
			}
			puts("");

			printf("\t%c", char(186));
			printf("  %s", leaderboard[i].name);

			int len = strlen(leaderboard[i].name);
			for(int j = len; j < 16; j++) printf(" ");
			printf("\t\t %c                            ", char(186));

			printf("%03d  ", leaderboard[i].score);
			printf("%c", char(186));
			puts("");

			printf("\t");
			for(int i = 0; i < 68; i++) {
				if(i == 0) printf("%c", char(200));
				else if(i == 33) printf("%c", char(202));
				else if(i == 67) printf("%c", char(188));
				else printf("%c", char(205));
			}
			puts("");
		}
	}

	puts("\n");
	puts("\t\t\t     Press Enter to go back.");

	do {
		printLeaderboardTitle(&num);
		num += 1;

		if(kbhit()) {
			if(getch() == keyEnter) {
				clearScreen();
				return;
			}
		}

	} while(1);
}
