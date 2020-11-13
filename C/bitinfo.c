/*******************************************************************************
 *
 * "for" problem. Count from 1 to 32 and list the range of unsigned integer
 * numbers that can be stored in each collection of bits. I.E. 8 bits can hold
 * the range 0 to 255.
 *
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

int main(void) {
	printf("#bits | [Min, Max]\n");
	for (int i = 1; i <= 32; i++) {
		printf("   %2d | [0,%u]\n", i, (unsigned int)pow(2,i) - 1);
	}
}
