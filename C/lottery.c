/*******************************************************************************
 *
 * Random numbers. Produce a sequence of six random numbers between 1 and 49.
 * These can then be used to play the National lottery (in England). The odds on
 * getting the right numbers are 13,983,816 to 1 - GOOD LUCK SUCKER.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
int main(void) {
	srand((unsigned int)time(NULL));

	printf("%u\n", rand());
}
*/

int main(void) {
	for (int i = 0; i <= 100; i++) {
		printf("%d ", i % 4);
	}
}
