#include "../include/apue.h"
#include <fcntl.h>
#include <sys/stat.h>

int display_attribute(struct stat *p)
{
    if(S_ISREG(p->st_mode))
        printf("-");
    else if (S_SISDIR(p->st_mode))
        printf("d");
    else if (S_SISCHR(p->st_mode))
        printf("c");
    else if (S_SISBLK(p->st_mode))
        printf("b");
    else if (S_SISFIFO(p->st_mode))
        printf("p");
    else if (S_SISLNK(p->st_mode))
        printf("l");
    else if (S_SISSOCK(p->st_mode))
        printf("s");

        //文件权限
    if(p->st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");

    if(p->st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");

    if(p->st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");

    if(p->st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");

    if(p->st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");

    if(p->st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");


    if(p->st_mode & S_IROTH)
        printf("r");
    else
        printf("-");

    if(p->st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");

    if(p->st_mode & S_IXOTH)
        printf("x");
    else
        printf("-");
}

int main(int argc, char const *argv[])
{
	struct stat buf;

	if(argc < 2)
    {
        fprintf(stderr,"Usage: %s FILENAME\n",argv[0]);
        return -1;
    }

    if(stat(argv[1],&buf) < 0)
    {
        perror("Fail to stat.\n");
        return -1;
    }

	display_attribute(&buf);

    printf(" %s\n",argv[1]);

	return 0;
}
