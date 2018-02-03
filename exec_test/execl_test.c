#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void perr_exit(const char *src)
{
	perror(src);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	pid_t pid;
	int ret, stat;
	if (argc != 2) {
		fprintf(stderr, "usage: %s [file]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if ( (pid = fork()) == -1)
		perr_exit("fork");
	else if (!pid) {	/* child process execute new image */
		if ( (ret = execl("/bin/ls", "ls", "-l", argv[1], NULL)) == -1)
			perr_exit("execl");
		exit(EXIT_SUCCESS);
	} else {	/* paretn process wait child and then exit */
		wait(&stat);
		printf("child process exit with %d\n", stat);
		exit(EXIT_SUCCESS);
	}
}
