#include "../include/apue.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int total = 0;
int N = 5;
int count1 = 0;
int count2 = 0;
pthread_mutex_t mutex;

void *tfn(void *arg){
    int num = *((int *)arg);
    pthread_mutex_lock(&mutex);
    total = total + num;
    count2 ++;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[]){
    pthread_t tid;
    int num;
    pthread_mutex_init(&mutex, NULL);

    while(scanf("%d", &num) == 1){
        if(num == N){
            count1 ++;
            pthread_create(&tid, NULL, tfn, (void *)&N);
        }
    }
    while(1)
        if((count1 == count2) && (pthread_mutex_trylock(&mutex) == 0)){
            pthread_mutex_unlock(&mutex);
            break;
        }
    //printf("Total %d\n", total);
    pthread_mutex_destroy(&mutex);
    return 0;
}
