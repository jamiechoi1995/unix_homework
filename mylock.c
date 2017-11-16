#include "../include/apue.h"
#include <signal.h>
#include <string.h>

static void sig_int(int);

int main(void){
	char pw[] = "pw1234\n";
	char buf[MAXLINE];

	sigset_t newmask, oldmask, pendmask;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	while (fgets(buf, MAXLINE, stdin) != NULL){
		if(strcmp(pw, buf) == 0){
			printf("pass!\n");
			exit(0);
		}
		else{
			if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) <0 )
				printf("error\n");
			if (signal(SIGINT, sig_int) == SIG_ERR)
				printf("can't set sig_int\n");
			printf("Wrong password.\n");
			sleep(5);
			if(sigprocmask(SIG_SETMASK, &oldmask, NULL) <0 )
				printf("error\n");
		}
	}

	return 0;
}

static void sig_int(int signo){
	printf("\n");
}