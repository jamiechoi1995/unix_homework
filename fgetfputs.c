#include "../include/apue.h"

#define BUF 2 // different size result in different result
int main(void)
{
	char buf[BUF];
	while(fgets(buf, BUF, stdin) != NULL)
		// if(fputs(buf, stdout) == EOF)
		if(puts(buf) == EOF)
			printf("output error\n");
	if(ferror(stdin))
		printf("input error\n");
	exit(0);
}
