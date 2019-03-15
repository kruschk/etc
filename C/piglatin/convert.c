#include <ctype.h> /* for isalpha() */
#include <string.h> /* for strlen() */
#include <error.h> /* for error() */
#include "piglatin.h"

/* returns VOWEL if the given character is a vowel, CONSONANT if it is a
 * consonant, and INVALID_CHAR if the character is invalid */
static int character_type(const char c) {
	/* list of vowels, 'y' has been ommitted */
	const char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };

	/* check if c is alphabetic, then check if it matches any of the vowels
	 * listed in vowels[] */
	if (isalpha(c)) {
		for (size_t i = 0; i < strlen(vowels); i++) {
			if (c == vowels[i]) {
				return VOWEL;
			}
		}
		return CONSONANT;
	}
	return INVALID_CHAR;
}

/* PURPOSE:	Converts a word to pig latin-ized form.
 *
 * INPUT:	returnbuf - pointer to a buffer that will store the result;
 * 			must be at least as long as the word + the string to be
 * 			appended to it, with room for a trailing '\0'.
 * 		buf - pointer to buffer for intermediate character storage;
 * 			must be at least as large as word, with room for a
 * 			trailing '\0'.
 *		word - pointer to the word to be converted.
 *
 * OUTPUT:	returnbuf - the result is stored in returnbuf
 *
 * NOTES:	It is up to the caller to ensure that returnbuf and buf are
 * 		large enough.
 * 		This function handles words starting with vowels by simply
 * 		appending VOWEL_APPEND to the end. Words starting with
 * 		consonants have all contiguous consonants stripped from the
 * 		beginning, appended to the end, and then CONSONANT_APPEND is
 * 		appended to the resulting string. */
char *convert(char *returnbuf, char *buf, const char *word) {
	int char_type = character_type(word[0]);

	/* handle words beginning with vowels */
	if (char_type == VOWEL) {
		for (size_t i = 0; i < strlen(word); i++) {
			returnbuf[i] = word[i];
		}
		returnbuf[strlen(word)] = '\0';
		return strcat(returnbuf, VOWEL_APPEND);
	}
	/* handle words beginning with consonants */
	else if (char_type == CONSONANT) {
		size_t i = 0;
		/* collect all the consonants into buf */
		while (character_type(word[i]) == CONSONANT) {
			buf[i] = word[i];
			i++;
		}
		/* don't forget to add the trailing null character! */
		buf[i] = '\0';

		/* need to "clear" returnbuf, we do so by setting the first
		 * character to a null character. */
		returnbuf[0] = '\0';
 		/* append the word to returnbuf, starting from the point in the
		 * string when we switch from a consonant (this is assumed to
		 * be a switch from a consonant to a vowel, but not this is not
		 * checked!) */
		strcat(returnbuf, &(word[i]));
		/* append the buffer to returnbuf */
		strcat(returnbuf, buf);
		/* append CONSONANT_APPEND to returnbuf and return the result */
		return strcat(returnbuf, CONSONANT_APPEND);
	}
	else if (char_type == INVALID_CHAR) {
		error(-1, -1, "invalid character");
	}
	error(-1, -1, "something went wrong");
	return NULL;
}
