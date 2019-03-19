int main(void) {
	while (1) {
		int ret;

		ret = fork();
		if (!ret) {
			perror("fork");
		}
	}
}
