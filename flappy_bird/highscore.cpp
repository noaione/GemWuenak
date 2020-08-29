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

void swap(highscore *a, highscore *b)
{
	highscore temp = *a;
	*a = *b;
	*b = temp;
}

void listName()
{
	FILE *fptr;
	fptr = fopen("flappy_scorename.txt", "r");

	currIdx = 0;
	while (fscanf(fptr, "%s", leaderboard[currIdx].name) != EOF)
	{
		currIdx++;
	}

	fclose(fptr);
}

void listScore()
{
	FILE *fptr;
	fptr = fopen("flappy_scores.txt", "r");

	currIdx = 0;
	while (fscanf(fptr, "%d", &leaderboard[currIdx].score) != EOF)
	{
		currIdx++;
	}

	fclose(fptr);
}

void processScore(highscore a, bool dont_save = false)
{ // masukkan a ke leaderboard, sort.
	FILE *fptr1, *fptr2;

	listName();
	listScore();
	leaderboard[currIdx] = a;
	if (currIdx < 10)
		currIdx++;

	for (int i = 0; i < currIdx + 1; i++)
	{
		for (int j = 0; j < currIdx - i; j++)
		{
			if (leaderboard[j].score < leaderboard[j + 1].score)
			{
				swap(&leaderboard[j], &leaderboard[j + 1]);
			}
		}
	}

	if (dont_save)
	{
		fptr1 = fopen("flappy_scorename.txt", "w");
		fptr2 = fopen("flappy_scores.txt", "w");

		for (int i = 0; i < currIdx; i++)
		{
			fprintf(fptr1, "%s\n", leaderboard[i].name);
			fprintf(fptr2, "%d\n", leaderboard[i].score);
		}

		fclose(fptr1);
		fclose(fptr2);
	}
}

void inputUsername(int score)
{
	/* VARIABLE */
	char username[20];
	int len;

	clearScreen();
	setCursorPosition(0, 0);

	puts("");

	reshowCursor();
	puts("\tInput username: (length must be between 2 - 16 characters)");
	do
	{
		printf("\t");
		scanf("%s", username);
		len = strlen(username);

		if (len < 2 or len > 16)
		{
			printf("\tLength must be between 2 - 16 characters! Press Enter to retry.");

			do
			{
				// can only continue if enter key is pressed
			} while (getch() != 13);

			for (int i = 0; i < 63; i++)
				printf("\b");
			for (int i = 0; i < 63; i++)
				printf(" ");
			printf("\033[A"); // balik ke atas
			for (int i = 0; i < len + 64; i++)
				printf("\b");
			for (int i = 0; i < len + 64; i++)
				printf(" ");
			printf("\r");
		}
	} while (len < 2 or len > 16);
	hideCursor();

	highscore player;
	strcpy(player.name, username);
	player.score = score;
	processScore(player, true);
}

void printLeaderboardTitle()
{
	int title[5][69] = {{1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
						{1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
						{1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
						{1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
						{1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}};

	hideCursor();
	puts(""); // kasih jarak dari pojok atas
	for (int i = 0; i < 5; i++)
	{ // print tulisan hangman
		printf("\t");
		for (int j = 0; j < 69; j++)
		{
			if (title[i][j])
			{ // kalau titleScreen[i][j] = 1 --> merupakan bagian text
				printf("#");
			}
			else
			{
				printf(" ");
			}
		}
		puts("");
	}
}

void printLeaderboard()
{
	clearScreen();
	setCursorPosition(0, 0);

	highscore dummy; // trigger dia process leaderboard
	strcpy(dummy.name, "------");
	dummy.score = -1;
	processScore(dummy, false);

	char s[255];
	int is_first = 1;

	do
	{
		if (is_first)
		{
			printLeaderboardTitle();
			printf("\t");
			for (int i = 0; i < 68; i++)
				printf("=");
			puts("");
			for (int i = 0; i < 10; i++)
			{
				if (strcmp(leaderboard[i].name, "------") != 0)
				{
					printf("\t");
					for (int i = 0; i < 68; i++)
					{
						if (i == 0)
#ifdef FALLBACKASCII
							printf("%c", char(201));
#else
							printf("╔");
#endif
						else if (i == 33)
#ifdef FALLBACKASCII
							printf("%c", char(203));
#else
							printf("╦");
#endif
						else if (i == 67)
#ifdef FALLBACKASCII
							printf("%c", char(187));
#else
							printf("╗");
#endif
						else
#ifdef FALLBACKASCII
							printf("%c", char(205));
#else
							printf("═");
#endif
					}
					puts("");

#ifdef FALLBACKASCII
					printf("\t%c", char(186));
#else
					printf("\t║");
#endif
					printf("  %s", leaderboard[i].name);

					int len = strlen(leaderboard[i].name);
					for (int j = len; j < 16; j++)
						printf(" ");
#ifdef FALLBACKASCII
					printf("\t\t %c                            ", char(186));
#else
					printf("\t\t ║                            ");
#endif

					printf("%03d  ", leaderboard[i].score);
#ifdef FALLBACKASCII
					printf("%c", char(186));
#else
					printf("║");
#endif
					puts("");

					printf("\t");
					for (int i = 0; i < 68; i++)
					{
						if (i == 0)
#ifdef FALLBACKASCII
							printf("%c", char(200));
#else
							printf("╚");
#endif
						else if (i == 33)
#ifdef FALLBACKASCII
							printf("%c", char(202));
#else
							printf("╩");
#endif
						else if (i == 67)
#ifdef FALLBACKASCII
							printf("%c", char(188));
#else
							printf("╝");
#endif
						else
#ifdef FALLBACKASCII
							printf("%c", char(205));
#else
							printf("═");
#endif
					}
					puts("");
				}
			}

			puts("\n");
			puts("\t\t\t     Press Enter to go back.");
			is_first = false;
		}

		if (kbhit())
		{
			if (getch() == keyEnter)
			{
				clearScreen();
				return;
			}
		}

	} while (1);
}
