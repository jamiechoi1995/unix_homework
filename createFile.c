#include "include/apue.h"
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>

int Usage(char *argv0)
{
	fprintf(stderr,"Usage: %s [-s filesize] filename\n",argv0);
    exit(-1);
}

int main(int argc, char *argv[])
{
	int fd, opt;
	int FILESIZE = 4000;
	char *FILENAME;

	if ((argc != 2) && (argc != 4))
	{
		Usage(argv[0]);
		exit(-1);
	}

	if (argc == 4) // ./createFile -s size FILENAME
	{
		while ((opt = getopt(argc, argv, "s:")) != -1)
		{
			switch(opt)
			{
				case 's':
					FILESIZE = atoi(optarg);
					FILENAME = argv[3];
					break;

				default:
					Usage(argv[0]);
					break;
			}
		}
	}

	if (argc == 2) // ./createFile FILENAME
		FILENAME = argv[1];

	char buf[FILESIZE+1];
	for(int i = 0;i < FILESIZE ; i++)
		{
			buf[i] = 'c';
		}
	buf[FILESIZE] = '\0';

	if ((fd = creat(FILENAME, S_IWUSR | S_IRUSR )) < 0)
		fprintf(stderr, "create error\n");
	if (write(fd, buf, FILESIZE) != FILESIZE)
		fprintf(stderr, "write error\n");
	return 0;
}
