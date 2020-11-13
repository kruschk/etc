/*******************************************************************************
 *
 * Functions - write a program that calls bignum() and littlenum() which
 * determine, respectively, the highest and the smallest of a sequence of
 * numbers read in from the terminal.
 *
 ******************************************************************************/

/***********************************COMPLETE***********************************/

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000

double bignum(double array[], int arraysize);
double littlenum(double array[], int arraysize);

int main(int argc, char *argv[]) {
	if (argc < MAXSIZE && argc > 1) {
		int i;
		double container[MAXSIZE];
	
		for (i = 0; i <= (argc - 2); i++) {	// disregard argv[0] and argv[argc]
			container[i] = atof(argv[i+1]);
			printf("%f ", container[i]);
		}
		i--;

		printf("\n%f", bignum(container, i));
		printf("\n%f\n", littlenum(container, i));
		
		return 0;
	}
	else {
		printf("Insufficient input. Please enter a series of numbers separated \
by spaces.\n");

		return -1;
	}
}

double bignum(double array[], int arraysize) {
	double largest = array[0];

	for (int i = 1; i <= arraysize; i++) {
		largest = array[i] > largest ? array[i] : largest;
	}
	
	return largest;
}

double littlenum(double array[], int arraysize) {
	double smallest = array[0];

	for (int i = 1; i <= arraysize; i++) {
		smallest = array[i] < smallest ? array[i] : smallest;
	}
	
	return smallest;
}
