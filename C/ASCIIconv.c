/*******************************************************************************
 *
 * Produce an ASCII conversion table (printable characters only, tabs &
 * newlines  ommitted, from 32 onward).
 *
 ******************************************************************************/

#include <stdio.h>

int main(void) {
	printf("This is an ASCII table, the decimal value is on the left, the \
character is on the right.\n");

	for (int i = 32; i < 127; i++) { // i will be 127 at the end
		printf("%3d: ", i);
		putchar(i);
		putchar('\n');
	}
}
