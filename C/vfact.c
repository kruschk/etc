#include <stdio.h>

int main(void) {
	int i, num, j;
	printf("Enter a number whose factorial shall be computed: ");
	scanf("%d", &num);

	for (i = 1, j = 1; i <= num; i++) {
		j = j * i;
	}

	printf("The factorial of %d is %d\n", num, j);
}
