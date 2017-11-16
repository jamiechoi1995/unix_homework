#include "../include/apue.h"
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
	char buf[128];
    int src_fd, new_fd, reader;

    struct stat src;
    struct timespec times[2];

    if ( (src_fd = open(argv[1], O_RDONLY)) < 0)
    	printf("opensrc\n");
    if ( (new_fd = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | S_IRUSR)) < 0)
    	printf("opennew\n");
    if ( (reader = read(src_fd, buf, sizeof(buf))) < 0 )
    	printf("readsrc\n");
    if ( write(new_fd, buf, reader) != reader )
    	printf("writenew\n");

    if (stat(argv[1], &src) < 0)
        printf("statsrc\n");
    times[0] = src.st_atim;
    times[1] = src.st_mtim;
    if (futimens(new_fd, times) < 0)
    	printf("time\n");;
    return 0;
}
