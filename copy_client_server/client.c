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

	struct sockaddr_in srv = {AF_INET, PORT, inet_addr(argv[1])}; 

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





/** Send a message to the server via socket s*/
	n = send(s, argv[3], sizeof(argv[3]), 0);

	if (n < 0) {
		perror("send problem");
		 exit(1);
	}

	printf ("TCP CLIENT: file request sent ...\n");
//printf ("");
		fdnew = creat(argv[2], 0666);
			if(fdnew == -1)
			{
				printf("cannot create file %s\n", argv[3]);
				exit(1);
			}

/* Receiving and printing a reply from server */
while( n = recv(s, buf, sizeof(buf), 0)>0){
		
	write(fdnew, buf, n);
	}

	

	//write (1, buf, n);

/** Close the socket and terminate.*/
	close(s);
	printf ("File transfer complete TCP CLIENT terminated...\n");
	exit(0);
}
