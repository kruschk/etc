/*******************************************************************************
 *
 * Generate the Fibonacci sequence. Starting with 0 and 1, add them up then
 * take the result and add it to the last number and repeat.
 *
 ******************************************************************************/

/***********************************COMPLETE***********************************/

#include <stdio.h>

/*
int main(void) {
	int i;
	unsigned int first = 0;
	unsigned int second = 1;
	unsigned int current;

	printf("%u ", first);
	printf("%u ", second);

	for (i = 3; i <= 50; i++) {
		printf("%u ", current = first + second);
		first = second;
		second = current;
	}

	putchar('\n');
	printf("That was the first %d numbers of the Fibonacci sequence!\n", --i);
}
*/

/*
int main(void) {
	unsigned int first = 0;
	unsigned int second = 1;
	unsigned int current;

	printf("%u ", first);
	printf("%u ", second);

	for (current=first+second; current<=4000000000; current=first+second) {
		printf("%u ", current);
		first = second;
		second = current;
	}

	putchar('\n');
}
*/

int main(void) {
	#define ARRAY 49

	int i;
	unsigned int fib[ARRAY];

	printf("%u ", fib[0] = 0);
	printf("%u ", fib[1] = 1);

	for (i = 2; i <= ARRAY; i++) {
		printf("%u ", fib[i] = fib[i-2] + fib[i-1]);
	}

	printf("\nThat was the first %d numbers of the Fibonacci sequence!\n", i);
}
