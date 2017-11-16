#include "../include/apue.h"
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#define MSGSZ 128
struct msgbuf {
	long mtype;
	int mnum;
};

int	main(int argc, char const *argv[])
{
	if(argc != 3)
		fprintf(stderr, "Usage: ./sendnum 0xXX NUM\n");
	key_t key = 4567 + atoi(argv[1]);
	// key = key + argv[1];
	struct msgbuf sbuf;
	int msgid;
	if ((msgid = msgget(key, 0666)) < 0) {
		printf("msgget");
		exit(1);
	}
	sbuf.mtype = 1;
	sbuf.mnum = atoi(argv[2]);
	if (msgsnd(msgid, &sbuf, sizeof(int), 0) < 0) {
		printf("msgsnd");
		exit(1);
	}
	return 0;
}