#include "../include/apue.h" //
#include <setjmp.h> //
//#include <signal.h>

static jmp_buf env_alrm;
static void sig_alrm(int signo); //

int
main(void)
{
	int	n;
	char line[MAXLINE];
	signal(SIGALRM, sig_alrm);
	alarm(10);
	if (setjmp(env_alrm) != 0) {
		printf("read timeout");
		exit(0);
	}
	n = read(STDIN_FILENO, line, MAXLINE);
	alarm(0);
	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void sig_alrm(int signo){
	longjmp(env_alrm, 1);
}