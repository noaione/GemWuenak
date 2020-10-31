#include <stdio.h>
#include <windows.h>

#include "kartu41.h"
#include "../extras/extra.h"

void kartu41TitleCard(int skip_wait = 0)
{
	printf("\n/ $$   /$$ /$$$$$$  /$$$$$$$  /$$$$$$$$ /$$   /$$       /$$   /$$   /$$\n");
	if (!skip_wait)
	{
		Sleep(250);
	}
	printf("| $$  /$$ /$$__  $$| $$__  $$|__  $$__/| $$  | $$      | $$  | $$ /$$$$\n");
	if (!skip_wait)
	{
		Sleep(250);
	}
  printf("| $$ /$$/| $$   \\$$| $$  \\$$    | $$   | $$  | $$      | $$  | $$|_  $$\n");
	if (!skip_wait)
	{
		Sleep(250);
	}
	printf("| $$$$$/ | $$$$$$$$| $$$$$$$/   | $$   | $$  | $$      | $$$$$$$$  | $$\n");
	if (!skip_wait)
	{
		Sleep(250);
	}
	printf("| $$  $$ | $$__  $$| $$__  $$   | $$   | $$  | $$      |_____  $$  | $$\n");
	if (!skip_wait)
	{
		Sleep(250);
	}
	printf("| $$\\  $$| $$  | $$| $$  \\$$    | $$   | $$  | $$            | $$  | $$\n");
	if (!skip_wait)
	{
		Sleep(250);
	}
	printf("| $$ \\$$ | $$  | $$| $$  | $$   | $$   |  $$$$$$/            | $$ /$$$$$$\n");
	if (!skip_wait)
	{
		Sleep(250);
	}
  printf("|__/  \\__/|__/ |__/|__/  |__/   |__/    \\______/             |__/|______/\n");
}

void howToPlay()
{
	puts("			How To Play");
	puts("");
	puts("1. Dalam setiap permainan kartu 41 terdapat 4 pemain.");
	puts("2. Masing - masing pemain akan mendapatkan 4 buah kartu secara acak.");
	puts("3. Pemain pertama akan mengambil sebuah kartu dari deck.");
	puts("4. Lalu pemain akan memilih salah satu kartu untuk dibuang ke pemain lain");
	puts("5. Pemain berikutnya bisa memilih antara mengambil kartu buangan atau");
	puts("   mengambil satu kartu dari deck.");
	puts("6. Pemain dengan kartu nilai 41 atau dengan kartu tertinggi setelah deck");
	puts("   habis adalah pemenang.");
}

void aimOfTheGame()
{
	puts("				Aim of The Game");
	puts("");
	puts("	Dalam permainan kartu 41, pemain bersaing untuk mendapatkan kartu berjumlah 41");
	puts("duluan. Pemain harus mengumpulkan kartu dengan jenis yang sama(hati, diamond, sekop,");
	puts("atau keriting). Setiap kartu memiliki nilai sesuai angka di kartunya. Lalu untuk kartu");
	puts("tanpa angka skornya yaitu : ");
	puts("1. Kartu As (ace) bernilai 11 poin.");
	puts("2. Kartu King, Queen, dan Jack masing masing bernilai 10 poin.");
	puts("3. Kartu 2 - 10 bernilai sama dengan angka.");
	puts("");
	puts("Pemenang adalah pemain yang mendapatkan kartu 41 pertama, atau yang memiliki total");
	puts("poin paling banyak setelah deck habis.");
}

int kartu41_game()
{
	int do_exit = 0, first_run = 1, after_tut = 0;
	char trash;

	while (!do_exit)
	{
		if (first_run)
		{
			first_run = false;
			clearScreen();
			hideCursor();
			setCursorPosition(0, 0);
			kartu41TitleCard();
			reshowCursor();
		}
		else
		{
			if (after_tut)
			{
				after_tut = 1;
				clearScreen();
				setCursorPosition(0, 0);
			}
			kartu41TitleCard(1);
		}
		puts("");
		printf("\t1. Play\n");
		printf("\t2. How to Play\n");
		printf("\t3. Exit\n");

		int do_break_loop = 0;
		int gameCursor = -1;
		while (gameCursor == -1)
		{
			int inp = 0;
			printf("\tMasukan angka: ");
        	scanf("%[^\n]", &inp);
			getchar();
			inp -= 48;
#ifdef DEBUGGAME
        	printf("\nUser input for menu: %d\n", inp);
#endif
			switch (inp)
			{
			case 1:
				gameCursor = 1;
				break;
			case 2:
				gameCursor = 2;
				break;
			case 3:
				gameCursor = 3;
				do_exit = 1;
				break;
			default:
				gameCursor = -1;
				break;
			}
		}
		if (do_exit)
		{
			break;
		}

		switch (gameCursor)
		{
		case 1:
		{
			clearScreen();
			setCursorPosition(0, 0);
			Kartu41 kartu41game;
			kartu41game.start_game();
			break;
		}
		case 2:
		{
			puts("");
			howToPlay();
			for (int i = 0; i < 3; i++)
			{
				puts("");
			}
			aimOfTheGame();
			printf("\nEnter untuk selesai.");
			getchar();
			after_tut = 1;
			break;
		}
		case 3:
		{
			do_exit = 1;
			break;
		}
		}
		if (do_exit)
		{
			break;
		}
	}
	return 0;
}
