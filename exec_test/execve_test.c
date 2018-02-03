#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void perr_exit(const char *src)
{
	perror(src);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	pid_t pid;
	int ret, stat;
	char *const args[] = {"/bin/sh", "-c", "env", NULL};
	char *const enpv[]	= {"MYWD=/home/qiuyu/oslab", NULL};
	if (argc != 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ( (pid = fork()) == -1)
		perr_exit("fork");
	else if (!pid) {
		if ( (ret = execve(args[0], args, enpv)) == -2)
			perr_exit("execve");
		exit(EXIT_SUCCESS);
	} else {
		wait(&stat);
		printf("child process exit with %d\n", stat);
		exit(EXIT_SUCCESS);
	}
}
