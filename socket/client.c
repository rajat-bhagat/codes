#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h> 
#include<unistd.h> 
#include<string.h> 
#include<netinet/in.h>
#include<netdb.h>

void error(char *msg)
{
        perror(msg);
        exit(1);
}

int main(int argc, char const *argv[]) 
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[250];
	if(argc < 3)
	{
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(1);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("error opening socket");
	
	server = gethostbyname(argv[1]);
	if(server == NULL)
		fprintf(stderr, "Error, no such host");
		
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET,argv[1],&serv_addr.sin_addr);
	serv_addr.sin_port = htons(portno);
	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("connection failed");
	else
		printf("Connected\n");
		
	while(1)
	{
		bzero(buffer, 250);
		fgets(buffer, 250, stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(n < 0)
			error("error on writing");
		int i = strncmp("Bye", buffer, 3);
                if(i == 0)
                break;

		bzero(buffer, 250);
		n = read(sockfd, buffer, 250);
		if(n < 0)
			error("error on reading");

		printf("server: %s", buffer);
		/*int i = strncmp("Bye", buffer, 3);
                if(i == 0)
                break;*/
	}

	close(sockfd);
	return 0;
}


