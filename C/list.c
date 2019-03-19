#include <stdio.h>

typedef struct list {
	int elem;
	struct list *next;
} List;

void print_list(List *ls) {
	if (NULL != ls) {
		printf("%d\n", ls->elem);
		print_list(ls->next);
	}
	return;
}

int main(void) {
	List a, b, c;
	a.elem = 1;
	a.next = &b;
	b.elem = 2;
	b.next = &c;
	c.elem = 3;
	c.next = NULL;
	print_list(&a);
	return 0;
}
