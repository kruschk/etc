#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *name, int flags);
int open(const char *name, int flags, mode_t mode);

int main(void) {
	int fd;

	fd = open("/home/jonah/code/open.c", O_RDONLY);

	if (fd == -1) {
		printf("Something went wrong.\n");
	}
	return EXIT_SUCCESS;
}
