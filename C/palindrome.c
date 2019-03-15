#include <stdio.h>
#include <stdlib.h>

/* checks if a string is a palindrome, returns 1 if it is, 0 if it's not */
int check_palindrome(const char *str) {
	size_t i = 0;
	size_t j;

	/* set i to the last character before the null-terminator in str */
	while (str[i] != '\0') {
		i++;
	}
	i--;

	/* check if 0th element matches the (n-1)th, 1st matches (n-2)th, etc. */
	for (j = 0; j < i; i--, j++) {
		if (str[i] != str[j]) {
			return 0;
		}
	}

	return 1;
}

int main(int argc, char *argv[]) {
	size_t result;

	if (argc != 2) {
		printf("usage: %s word\n", argv[0]);
		exit(EXIT_SUCCESS);
	}

	result = check_palindrome(argv[1]);
	printf("\"%s\" is %sa palindrome\n", argv[1],
			result ? "": "not ");

	return 0;
}
