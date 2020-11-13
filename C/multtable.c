/* Produce a multiplication table. Top left hand corner will show 1x1 and bottom
	right shows 12x12. */

#include <stdio.h>

int main(void) {
	int i, j;

	for (i = 1; i <= 12; i++) {	// i will end up being 13!
		for (j = 1; j <= 12; j++) {	// j will end up being 13!
			printf("%3d ", i * j);
		}
	putchar('\n');
	}

	printf("counter variable i: %d\n", i);
	printf("counter variable j: %d\n", j);
}
