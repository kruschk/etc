// Gives input a lisp!

#include <stdio.h>

int main(void) {
	char c;
	
	while ((c = getchar()) != EOF) {
		if (c == 's') {
			printf("th");
		}
		else if (c == 'S') {
			printf("Th");	
		}
		else {
			putchar(c);
		}
	}
	return 0;
}
