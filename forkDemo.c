#include "/home/wcai/Desktop/实验1/附件/apue.3e/include/apue.h"

int globvar = 88;       /* external variable in initialized data */
char buf[] = "a write to stdout\n";

int
main(void)
{
    int var;        /* automatic variable on the stack */
    pid_t pid;
    var = 6;

    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
        fprintf(stderr, "write error\n");
    printf("before fork\n");    /* we don't flush stdout */

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
    } else if (pid == 0) {      /* child */
        globvar++;                  /* modify variables */
        var++;
    } else {
        sleep(2);                   /* parent */
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    _exit(0); //diff between exit(0)
}
/*
wcai@tdtd-desktop ~/Downloads/homework $ ./a.out 
a write to stdout
before fork
pid = 8857, glob = 89, var = 7
pid = 8856, glob = 88, var = 6
wcai@tdtd-desktop ~/Downloads/homework $ ./a.out > temp.out
wcai@tdtd-desktop ~/Downloads/homework $ cat temp.out 
a write to stdout
*/
