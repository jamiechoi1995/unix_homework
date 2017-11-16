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
int sum = 0;
int count = 0;
int rcv_count = 0;
pthread_mutex_t mutex;
key_t key = 4567;
int queue[100];

struct msgbuf {
    long mtype;
    int mnum;
};

void *tfn(void)
{
    pthread_mutex_lock(&mutex);
    int msgid;
    if ((msgid=msgget(key+count, IPC_CREAT|0666))<0) {
        printf("msgget");
        exit(1);
    }
    queue[count] = msgid;
    printf("queue ID %d is %d, (0x%lx)\n", count, msgid, (long unsigned)msgid);
    count ++;
    pthread_mutex_unlock(&mutex);
}

int Usage(char *argv0)
{
    fprintf(stderr,"Usage: %s [-q num]\n",argv0);
    exit(-1);
}

int main(int argc, char *argv[])
{
    int opt;
    int q = 1;
    pthread_t tid;
    pthread_mutex_init(&mutex, NULL);

    if ((argc != 1) && (argc != 3))
    {
        Usage(argv[0]);
        exit(-1);
    }

    if (argc == 3) // ./accumulator -q num
    {
        while ((opt = getopt(argc, argv, "q:")) != -1) //":" need parameter
        {
            switch(opt)
            {
                case 'q':
                    q = atoi(optarg);
                    break;

                default:
                    Usage(argv[0]);
                    break;
            }
        }
    }

    for(int i = 0; i < q; i++){
        pthread_create(&tid, NULL, tfn, NULL);
    }

    struct msgbuf rbuf;
    while(1){
        for (int i = 0; i < q; i++){
            if (msgrcv(queue[i], &rbuf, MSGSZ, 1, 0) >= 0){
                rcv_count++;
                sum = rbuf.mnum + sum;
                printf("sum is %d\n", sum);
            }
        }
        if((rcv_count == q) && (count == q) && (pthread_mutex_trylock(&mutex) == 0)){
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
