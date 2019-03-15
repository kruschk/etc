#include <stdio.h>

int main(void) {
	int array[1024];
	int *array_p;

	array_p = array;
	array_p = &array[0];
	array_p = &array;

	return 0;
}
