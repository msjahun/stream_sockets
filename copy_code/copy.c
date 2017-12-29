#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
char buffer[2048];
int version =1;

void copy(int old, int new);
main(argc,argv)
	int argc;
	char *argv[];

{

	int fdold,fdnew;

	if(argc!=3){
		printf("need 2 arguments for copy program\n");
		exit(1);
	}

	fdold = open(argv[1], O_RDONLY);
	if(fdold == -1)
	{
		printf("cannot open file %s\n", argv[1]);
		exit(1);
	}

	fdnew = creat(argv[2], 0666);
	if(fdnew == -1)
	{
		printf("cannot open file %s\n", argv[1]);
		exit(1);
	}

	 copy(fdold, fdnew);
	exit(1);
}


	 void copy(int old, int new)
		
	{
		int count;
		
	while(( count = read(old, buffer, sizeof(buffer))) > 0)
		write(new, buffer, count);
	}
