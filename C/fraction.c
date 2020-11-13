/* Structures - Use structures to add two fractions together */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {	
	if (argc == 5) {
		struct fraction {
			double num;
			double denom;
		} first;

		first = { 3.0, 4.0};
		
		/*
		struct fraction first = {
			atof(argv[1]),
			atof(argv[2])
		};
		*/
		struct fraction second = {
			atof(argv[3]),
			atof(argv[4])
		};

		printf("%f\n", first.num/first.denom + second.num/second.denom);

		return 0;
	}
}
