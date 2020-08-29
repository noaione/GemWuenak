#include <stdio.h>

void howToPlay() {
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

void aimOfTheGame() {
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

int main() {
	howToPlay();
	for(int i = 0; i < 3; i++) {
		puts("");
	}
	aimOfTheGame();
	return 0;
}
