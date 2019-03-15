#define VOWEL 0
#define CONSONANT 1
#define INVALID_CHAR -1

static const char CONSONANT_APPEND[] = "ay";
static const char VOWEL_APPEND[] = "way";

char *convert(char *returnbuf, char *buf, const char *word);
