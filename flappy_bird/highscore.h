#ifndef FLAPPY_HIGHSCORE_H
#define FLAPPY_HIGHSCORE_H

typedef struct highscore
{
	char name[20];
	int score;
};

void listName();
void listScore();
void processScore(highscore a);
void inputUsername(int score);
void printLeaderboardTitle(int *num);
void printLeaderboard();

#endif /* FLAPPY_HIGHSCORE_H */