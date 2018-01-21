// #include "../include/apue.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define N 5

int total = 0;
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
        int *p = malloc(sizeof(int));
        *p = num;
        if (*p == N){
            count1 ++;
            pthread_create(&tid, NULL, tfn, (void *)p);
        }
    }
    while(1)
        if((count1 == count2) && (pthread_mutex_trylock(&mutex) == 0)){
            pthread_mutex_unlock(&mutex);
            break;
        }
    printf("Total %d\n", total);
    pthread_mutex_destroy(&mutex);
    return 0;
}
