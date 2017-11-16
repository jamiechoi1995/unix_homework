#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#define MSGSZ 128
struct msgbuf {
	long mtype;
	char mtext[MSGSZ];
};

int main () {
	int msgid;
	key_t key;
	struct msgbuf sbuf,rbuf;
	key = 4587;
	if ((msgid = msgget(key, IPC_CREAT|0666)) < 0) {
		printf("msgget");
		exit(1);
	}
	printf("%d\n", msgid);
	// if  (msgctl(msgid, IPC_RMID, &sbuf) < 0)
	// 	printf("delete fail\n");

	sbuf.mtype=1;
	sprintf(sbuf.mtext,"Did you get the Message ?"); //sbuf.mtext = "Did you get the Message ?"
	if (msgsnd(msgid, &sbuf, strlen(sbuf.mtext)+1, 0) < 0) {
		printf("msgsnd");
		exit(1);
	}
	if (msgrcv(msgid, &rbuf, MSGSZ, 2, 0)<0) { //2 ?
		printf("msgrcv");
		exit(1);
	}
	printf("%s\n", rbuf.mtext);
	// while(1);
	exit(0);
}