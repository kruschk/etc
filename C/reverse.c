/* Take command-line arguments as input, reverse the input, and print the
 * resulting string to stdout. */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage: %s [string]\n", argv[0]);
    return 1;
  }

  for (int i = argc - 1; i >= 1; i--) {
    for (int j = strlen(argv[i]) - 1; j >= 0; j--) {
      putchar(argv[i][j]);
    }
    if (i > 0) {
      putchar(' ');
    }
  }

  putchar('\n');
  return 0;
}
