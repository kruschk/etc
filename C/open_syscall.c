/* A file is opened and a file descriptor is obtained with the open() system call. */

#include <types.h>
#include <stat.h>
#include <fcntl.h>

int open(const char *name, int flags);
int open(const char *name, int flags, mode_t mode);

int fd;

fd = open("/home/jonah/binaries.txt", O_RDONLY);
if (fd == -1) {
	printf("something went wrong\n");
}
