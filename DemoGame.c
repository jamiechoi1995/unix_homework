#include "../include/apue.h"
#include <unistd.h>
#include <time.h>
#define TIMEBUF 32

uid_t r_uid, e_uid, s_uid;
int flag = 1;
int score = 0;

void dolog(void)
{
	time_t t;
	struct tm *tmp;
	char buf[TIMEBUF];
	if(setuid(0) < 0){
		printf("set1 error\n");
		exit(1);
	}
	time(&t);
	tmp = localtime(&t);
	if(strftime(buf, TIMEBUF, "[%Y-%m-%d %r]:", tmp) == 0)
		printf("buf too small\n");
	else{
		FILE *fp;
		fp = fopen("scores.log", "a+");
		// fputs(buf, fp); // don't have /n
		fprintf(fp ,"%s%d\n", buf, score);
		fclose(fp);
		flag = 1;
		score++;
	}
}

void sig_alarm(int signo){
	dolog();
}

int main(void){
	uid_t ruid;
	ruid = getuid();

	if(seteuid(ruid) < 0)
		printf("setr error\n");
	dolog();

	for(;;){
		if(flag == 1){
			signal(SIGALRM, sig_alarm);
			alarm(3);
			if(seteuid(ruid) < 0)
				printf("setr error\n");
			flag = 0;
		}
	}
	return 0;
}

