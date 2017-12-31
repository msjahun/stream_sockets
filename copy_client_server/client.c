/* CLIENTprogram for Internet TCP sockets */
/* Client assumes that the server has  */
/* IP addr = 194.27.78.02   and port = 7000*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#define PORT  7000 /* Port of the server */
#define SIZE sizeof(struct sockaddr_in)

int howManyChars(char buff[]);
void clearbuff(char buff[]);

int main(int argc, char *argv[]){

	char buf[1024];
	int n, s, ns, len;
int count;
int fdnew;

	if(argc!=3){
		printf("need 2 arguments for ipaddress and name of file to copy\n");
		exit(1);
	}

/* For client's address, OS will assign IP of this host  */
/* and arbitrary port number: */

	struct sockaddr_in cli = {AF_INET, INADDR_ANY, INADDR_ANY};

/* For server's address */

	struct sockaddr_in srv = {AF_INET, PORT, inet_addr("127.0.0.1")}; 

/* Or in the following way (IP addr could be assigned later): */
/* struct sockaddr_in srv = {AF_INET, PORT}; */

	printf("TCP CLIENT: starting ...\n");

/*Convert and store IP address of the server: 194.27.78.02 (helium) */
/* if this is not done in initialisation of srv structure above */ 
/* srv.sin_addr.s_addr = inet_addr("194.27.78.02"); */
/** Create the Internet socket, of SOCK_STREAM  type.*/

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		{
			perror("socket problem");
			exit(1);
		}

/** Bind the socket to the IP address of this host.*/

	if (bind(s, (struct sockaddr *) &cli, SIZE) < 0) 
		{
			perror("bind problem");
			exit(1);
		}

/* Try to establish a connection with the server */

	len = SIZE;

	if (connect(s, (struct sockaddr *)&srv, len) < 0)
		{
			perror("connect problem"); 
			exit(1);
		}

//printf("\nThis is argv[1]:%s ,with length %d.And argv[2]:%s, with length %d\n",argv[1],howManyChars(argv[1]),argv[2],howManyChars(argv[2]));



/** Send a message to the server via socket s*/
	n = send(s, argv[1], howManyChars(argv[1])+1, 0);

	if (n < 0) {
		perror("send problem");
		 exit(1);
	}
printf ("TCP CLIENT: file request sent ...\n");
sleep(2);
clearbuff(buf);
	n=recv(s,buf,sizeof(buf),0);
	if(strcmp(buf,"error")==0){
		printf("File Not found, please check the name of the requested file and try again\n");

		}
	else if(strcmp(buf,"success")==0){

		printf("File found Successfully, getting ready to initiate download..\n");
		sleep(1);
		fdnew = creat(argv[2], 0666);
			if(fdnew == -1)
			{
				printf("cannot create file %s\n", argv[2]);
				exit(1);
			}
			clearbuff(buf);
			/* Receiving and printing a reply from server */
			while( n = recv(s, buf, sizeof(buf), 0)>0){
			//		printf("%s",buf);
				write(fdnew, buf, howManyChars(buf));
			clearbuff(buf);

			}

			//	n=recv(s,buf,sizeof(buf),0);


				//write (1, buf, n);
			printf ("File transfer complete TCP CLIENT terminated...\n");



	}
	else{
	printf("This is our buffer %s\n",buf);
	printf("Strcmp %s and success is %d\n",buf,strcmp(buf,"success"));
	printf("strcmp %s and error is %d\n\n",buf,strcmp(buf,"error"));
	}

	

/** Close the socket and terminate.*/
	close(s);
	
	exit(0);
}

int howManyChars(char buff[]){
int counter=0;
char *b;
b=buff;

while(*b != '\0'){
b++;
counter++;
}

return counter;
}


void clearbuff(char buff[]){
int i=0;
char *b;
b=buff;
for(;i<1024;i++){
*b='\0';
b++;

}
}
