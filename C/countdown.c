#include <stdio.h>

int main (void) {

	printf("T-minus: ");
	int i = 10;
	while (i >= 0) {
		printf("%d... ", i--);
	}
	putchar('\n');

	return 0;
}
