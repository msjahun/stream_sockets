
/* SERVERprogram for Internet TCP sockets */
/* Server starts, creates and binds a socket */
/* and then handles clients’requestsin the loop, without termination*/

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
#define PORT  4000 /* Port of this server */
#define SIZE sizeof(struct sockaddr_in)


int main(void){
	char buf[1024];
	int n, s, ns, len;
	struct sockaddr_in 
	srv = {AF_INET, PORT, INADDR_ANY};
	struct sockaddr_in cli; /* For client's address */
	int cli_len = SIZE;
	

	printf("TCP SERVER: starting ...\n");

/** Create the Internet socket, of SOCK_STREAMtype.*/

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket problem");
		exit(1);
	}

/*
* For simplicity, use the IP address as the OS selects.
* It is more preferable to set a specific IP address
* which must be known to all clients...
*/
	
/*
* Bind the socket to the IP address of this host.*/

	if (bind(s, (struct sockaddr *) &srv, SIZE) < 0) {
		perror("bind problem");
		exit(1);
	}

/* Set the size of  requests queue */
	
	if (listen(s, 5) < 0){
		perror("listen problem"); exit(1);
	}

/* Now establish a connection if there is a request */
/* for a connection from a client */
/* A new socket descriptor will be created for this connection */
/* The server may continue listening on the old socket descriptor */
/* for new request for a connection */
	

	while (1){
		ns = accept(s, (struct sockaddr *) &cli, &len);
		
		if (ns < 0) {
			perror ("accept problem");
			 exit(1);
		}

	
/** Now read from the new socket ns*/
	

	n = recv(ns, buf, sizeof(buf), 0);
		
		if (n < 0) {
			perror("recv problem");
			 exit(1);
		}

	write(1, buf, n);

	
/* Sending a reply to client */
	
	send (ns, "This is a reply from server\n",28,0);

	printf ("TCP SERVER: a reply is sent...\n");

	close (ns);

	}  
}
