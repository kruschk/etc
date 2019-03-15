#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *generate(size_t length) {
	char *res;  /* result */
	/* seed for random number generator */
	srand(time(NULL));
	/* allocate memory for string */
	res = malloc((length + 1)*sizeof *res);
	/* assign a random character (1 or 0) to each element of res */
	for (unsigned i = 0; i < length; i++) {
		res[i] = rand()%2 + '0';
	}
	res[length] = '\0';
	/* return generated string */
	return res;
}

int main(void) {
	char *str = generate(16);
	printf("%s\n", str);
	free(str);
	return 0;
}
