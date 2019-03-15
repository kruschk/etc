#include <stdio.h>

char a[4][7] = {"Common", "Point", "Boost", "Better"};
char (*b[4])[7] = {a+3, a+1, a, a+2}; /* b is an array of 4 pointers to arrays of 7 chars */

char (*(*c(void))[4])[7] { // c(void) => * [4] * [7] char
	return &b;
}

char (**d(void))[7] { // d(void) => * * [7] char
	return c()[1] - 3;
}

char buf[256];

char *pointer_monster(char (**(*f)(void))[7]) { /* same as d */
	int len;

	len  = sprintf(buf, "%s", *f()[0]);
	len += sprintf(buf + len, "%s ", *((**f)()-1)[0]+4);
	len += sprintf(buf + len, "%s", (*f())[0]-4);
	len += sprintf(buf + len, "%s", f()[1][2]+3);
	len += sprintf(buf + len, "%s", *((**f)()-1)[0]+4);
	return buf;
}

int main(void) {
	printf("%s", pointer_monster(d));
}
