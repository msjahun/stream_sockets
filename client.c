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
#define PORT  14782/* Port of the server */
#define SIZE sizeof(struct sockaddr_in)

int main(void){

	char buf[1024];
	int n, s, ns, len;

/* For client's address, OS will assign IP of this host  */
/* and arbitrary port number: */

	struct sockaddr_in cli = {AF_INET, INADDR_ANY, INADDR_ANY};

/* For server's address */

	struct sockaddr_in srv = {AF_INET, PORT, inet_addr("194.27.78.02")}; 

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
	n = send(s, "This is a request from client\n", 30, 0);

	if (n < 0) {
		perror("send problem");
		 exit(1);
	}

	printf ("TCP CLIENT: a request is sent ...\n");

/* Receiving and printing a reply from server */
	n = recv(s, buf, sizeof(buf), 0);
	write (1, buf, n);

/** Close the socket and terminate.*/
	close(s);
	printf ("TCP CLIENT terminated...\n");
	exit(0);
}