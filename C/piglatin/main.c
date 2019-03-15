/* Pig latin converter! Takes a string as a series of command-line arguments
 * and converts it to pig latin.
 *
 * Grammar for this program (this grammar is not actually used, but I wanted to
 * keep it here because I worked hard on it.):
 *
 * string:
 * 	convertible
 * 	not-convertible
 * convertible:
 * 	vowel consonant -> this will simply append "way" to the end
 * 	consonant vowel -> this will move the consonant to the end of the string
 * 	consonant consonant -> all consonants should be moved to the back
 * not-convertible:
 * 	character -> single char is the only case that's not convertible
 * 	converted-string -> can't convert if it's already been converted
 * word:
 * 	vowel string
 * 	consonant string
 * vowel:
 * 	'a', 'e', 'i', 'o', 'u'
 * consonant:
 * 	'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r',
 * 	's', 't', 'v', 'w', 'x', 'y', 'z'
 * character:
 * 	vowel
 * 	consonant
 *
 * Vowels and consonants are the tokens, while the remaining 
 * Final processing involves placing the consonant at the end of the string and
 * continuing. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include "piglatin.h"

int main(int argc, char *argv[]) {
	/* not enough arguments given */
	if (argc < 2) {
		printf("usage: %s [string]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* allocate memory for processing buffers */
	size_t maxbytecount = strlen(argv[1]);
	for (int i = 2; i < argc; i++) {
		if (maxbytecount < strlen(argv[i])) {
			maxbytecount = strlen(argv[i]);
		}
	}
	/* maxbytecount will be the length of the longest input argument +
	 * length of CONSONANT_APPEND + length of VOWEL_APPEND + 1 to account
	 * for a trailing null character. The length of the two APPENDS are
	 * simply added so we don't have to calculate which one is larger */
	maxbytecount += strlen(CONSONANT_APPEND) + strlen(VOWEL_APPEND) + 1;
	char *returnbuf = malloc(maxbytecount);
	char *buf =  malloc(maxbytecount);

	/* loop through command-line arguments and convert each one */
	for (int i = 1; i < argc; i++) {
		printf("%s ", convert(returnbuf, buf, argv[i]));
	}
	putchar('\n');

	/* free word-processing buffers */
	free(returnbuf);

	return 0;
}
