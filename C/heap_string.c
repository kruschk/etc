#include <stdio.h>
#include <stdlib.h>

/* heap-allocated string object */
typedef struct {
	size_t cap;
	char *s;
} HeapString;

/* create a new HeapString object */
HeapString *heap_string_new(size_t cap) {
	HeapString *hs = malloc(sizeof *hs);
	hs->cap = cap;
	hs->s = malloc(cap*sizeof *(hs->s));
	return hs;
}

/* destroy a HeapString object */
void heap_string_destroy(HeapString *hs) {
	free(hs->s);
	hs->s = NULL;
	hs->cap = 0;
	free(hs);
	hs = NULL;
}

int main(void) {
	HeapString *hs = heap_string_new(16);
	printf("%p, %p, %p\n", hs, &hs->cap, hs->s);
	heap_string_destroy(hs);
	return 0;
}
