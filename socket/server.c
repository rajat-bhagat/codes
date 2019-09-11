#include<unistd.h> 
#include<stdio.h> 
#include<sys/socket.h> 
#include<stdlib.h> 
#include<netinet/in.h> 
#include<string.h>
#include<sys/types.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}


int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr,"port number not provided. program terminated");
		exit(1);
	}

	int sockfd, newsockfd, portno, n, flag=0;
	char buffer[250];

	struct sockaddr_in serv_addr, cli_addr;
	int serv_addrlen = sizeof(serv_addr);
	socklen_t clilen;

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		error("error in opening socket");
	}
	printf("socket decriptor %d\n", sockfd);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno=atoi(argv[1]);
	printf("portno %d\n", portno);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	//serv_addr.sin_addr.s_addr = "127.0.0.1";
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		error("binding failed");
	}
	printf("bind is complete\n");

	listen(sockfd, 0);
	clilen = sizeof(cli_addr);
	while(1)
	{

		//listen(sockfd, 2);
		//clilen = sizeof(cli_addr);

		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		printf("new socket descriptor %d\n", newsockfd);
		if(newsockfd < 0)
		{
			error("error on accept");
		}

		while(1)
		{
			bzero(buffer, 250);
			n = read(newsockfd, buffer, 250);
			if(n < 0)
				error("error on reading");
			printf("Client: %s\n", buffer);

			int i = strncmp("Bye", buffer, 3);
			if(i == 0)
			{
				flag = 0;
				break;
			}

			bzero(buffer, 250);
			fgets(buffer, 250, stdin);
			n = write(newsockfd, buffer, strlen(buffer));
			if(n < 0)
				error("error on writing");

			i=0;
			i = strncmp("Bye", buffer, 3);
			if(i == 0)
			{
				flag = 1;
				break;
			}

		}

		if(flag == 1)
		{
			break;
		}

		close(newsockfd);

	}

	close(newsockfd);
	close(sockfd);
	return 0;
}


