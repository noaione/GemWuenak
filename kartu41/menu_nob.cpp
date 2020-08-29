#include <stdio.h>

int main() {
	int n;
	printf("1. play");
	printf("2. how to play");
	printf("3. exit");
	scanf("%d", &n);
	
	switch(n) {
		case 1:
			printf("play");
			break;
		case 2:
			printf("how to play");
			break;
		case 3:
			printf("exit");
			break;
	}
	
}
