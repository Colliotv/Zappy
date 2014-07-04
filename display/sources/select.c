// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>

// #define PORT 4242
 
// int main(int argc, char *argv[])
// {
// 	fd_set master; 	/* master file descriptor list */
// 	fd_set read_fds; /* temp file descriptor list for select() */
// 	struct sockaddr_in serveraddr; 	/* server address */
// 	struct sockaddr_in clientaddr;	/* client address */
// 	int fdmax;
// 	int listener;
// 	int newfd;
// 	char buf[1024];
// 	int nbytes;
// 	int yes = 1;
// 	int addrlen;
// 	int i, j;
// 	FD_ZERO(&master);
// 	FD_ZERO(&read_fds);
// 	if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
// 	{
// 		perror("Server-socket() error lol!");
// 		exit(1);
// 	}
// 	printf("Server-socket() is OK...\n");
// 	if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
// 	{
// 		perror("Server-setsockopt() error lol!");
// 		exit(1);
// 	}
// 	printf("Server-setsockopt() is OK...\n");

// 	serveraddr.sin_family = AF_INET; /* bind */
// 	serveraddr.sin_addr.s_addr = INADDR_ANY;
// 	serveraddr.sin_port = htons(PORT);
// 	memset(&(serveraddr.sin_zero), '\0', 8);

// 	if(bind(listener, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
// 	{
// 		perror("Server-bind() error lol!");
// 		exit(1);
// 	}
// 	printf("Server-bind() is OK...\n");

// 	if(listen(listener, 10) == -1) /* listen */
// 	{
// 		perror("Server-listen() error lol!");
// 		exit(1);
// 	}
// 	printf("Server-listen() is OK...\n");

// 	FD_SET(listener, &master); /* add the listener to the master set */
// /* keep track of the biggest file descriptor */
// 	fdmax = listener; /* so far, it's this one*/

// 	for(;;)
// 	{
// 		read_fds = master;
// 		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
// 		{
// 			perror("Server-select() error lol!");
// 			exit(1);
// 		}
// 		printf("Server-select() is OK...\n");

// 	/*run through the existing connections looking for data to be read*/
// 		for(i = 0; i <= fdmax; i++)
// 		{
// 			if(FD_ISSET(i, &read_fds))
//     { /* we got one... */
// 				if(i == listener)
// 				{
//          /* handle new connections */
// 					addrlen = sizeof(clientaddr);
// 					if((newfd = accept(listener, (struct sockaddr *)&clientaddr, &addrlen)) == -1)
// 					{
// 						perror("Server-accept() error lol!");
// 					}
// 					else
// 					{
// 						printf("Server-accept() is OK...\n");
//                       	FD_SET(newfd, &master); /* add to master set */
// 						if(newfd > fdmax)
// 	                    {
// 	                    	fdmax = newfd;
// 	                    }
// 	                    printf("%s: New connection from %s on socket %d\n", argv[0], inet_ntoa(clientaddr.sin_addr), newfd);
// 	                }
// 	            }
// 	            else
// 	            {
// 	            	if((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
// 	            	{
// 	            		if(nbytes == 0)
// 	            			printf("%s: socket %d hung up\n", argv[0], i);
// 	            		else
// 	            			perror("recv() error lol!");
// 	            		close(i);
// 	            		FD_CLR(i, &master);
// 	            	}
// 	            	else
// 	            	{
// 	            		for(j = 0; j <= fdmax; j++)
// 	            		{
// 	            			if(FD_ISSET(j, &master))
// 	            			{
// 	            				if(j != listener && j != i)
// 	            				{
// 	            					if(send(j, buf, nbytes, 0) == -1)
// 	            						perror("send() error lol!");
// 	            				}
// 	            			}
// 	            		}
// 	            	}
// 	            }
// 	        }
// 	    }
// 	}
// 	return 0;
// }
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
 #include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        perror("ERROR opening socket");
        exit(1);
    }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
           (char *)&serv_addr.sin_addr.s_addr,
                server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd,&serv_addr, sizeof(serv_addr)) < 0) 
    {
         perror("ERROR connecting");
         exit(1);
    }   
    /* Now ask for a message from the user, this message
    * will be read by server
    */
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    /* Send message to the server */
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
    {
         perror("ERROR writing to socket");
         exit(1);
    }
    /* Now read server response */
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
    {
         perror("ERROR reading from socket");
         exit(1);
    }
    printf("%s\n",buffer);
    return 0;
}