#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

/* check_anagram: check if s2 is an anagram of s1, ignoring whitespace */
int check_anagram(const char *s1, const char *s2) {
	size_t i;
	int count1[CHAR_MAX] = {0};
	int count2[CHAR_MAX] = {0};

	/* generate the counts of each character */
	for (i = 0; s1[i] != '\0'; i++) {
		count1[(size_t)s1[i]]++;
	}
	for (i = 0; s2[i] != '\0'; i++) {
		count2[(size_t)s2[i]]++;
	}

	/* compare count1 and count2 */
	for (i = 0; i < CHAR_MAX; i++) {
		if (isspace(i)) {
			;
		}
		else if (count1[i] != count2[i]) {
			return 0; /* not an anagram */
		}
	}

	return 1;
}

int main(int argc, char *argv[]) {
	size_t result;

	if (argc != 3) {
		printf("usage: %s word1 word2\n", argv[0]);
		exit(EXIT_SUCCESS);
	}

	result = check_anagram(argv[1], argv[2]);
	printf("\"%s\" is %san anagram of \"%s\"\n", argv[2],
			result ? "" : "not ", argv[1]);

	return 0;
}
