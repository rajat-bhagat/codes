#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<pthread.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define PORT 8000 //port

char name[20],dest_client_name[20];

void * func_read(void *accept_id)
{
	char str[1024];
	int q;
	while(1)
	{
		bzero(str,1024);
		q=read((long)accept_id,&str,1024); // starts the reading opertion 
		if(q!=0)
		{
			printf("\nClient : %s\n",str);
			/*pthread_mutex_lock(&lock);
			fp=fopen(name1,"a+"); //file to save the chat history
 			if(fp==NULL)
				printf("error opening file");
			else
			{
				fprintf(fp,"server:  %s\n",str); // recording chat history in the file 
				fclose(fp);
			}
			pthread_mutex_unlock(&lock);*/
			if(strncmp("bye",str,3)==0) // clients shut down if the server is down
			{	
				printf("chat closed\n");
				pthread_exit(NULL);
				//pthread_mutex_destroy(&lock);
				//exit(0);
			}
		}else
		{
			break;
		}
		q=0;
		bzero(str,1024); // clearing the message buffer
	}
}


void * func_write(void *accept_id)
{
	char str1[1024];
	int  i=0,j=1,temp=0; // control variables

	while(j)
	{
		j=0;
		printf("Enter message: ");
		scanf("%s",str1);
		write((long)accept_id,str1,strlen(str1)); // sending the data
		/*pthread_mutex_lock(&lock);
		fp=fopen(name1,"a+"); // opening file in append mode
		if(fp==NULL)
			printf("error opening file");
		else
		{
			fprintf(fp,"Me: %s\n",str1); // recording the chat history
			fclose(fp);
		}
		pthread_mutex_unlock(&lock);*/
		if(strncmp("bye",str1,3)==0) // shutting the client
		{
			printf("chat closed\n");
			pthread_exit(NULL);
			//pthread_mutex_destroy(&lock);
			//exit(0);
		}

		i=0;
		bzero(str1,1024);
		j=1;
	}
}


int main()
{
	int val=1, socket_fd;
	struct sockaddr_in addr;
	char msg[100],choice;
	int addrlen =sizeof(addr);
	pthread_t th_wr,th_rd;
	
	printf("Set client name: "); 
        scanf("%s",name);
		
	//create a socket
	socket_fd = socket(AF_INET,SOCK_STREAM,0);
	if(socket_fd)
	{
		printf("socket created\n");
	}
	else
	{	perror("socket failed\n");
		return -1;
	}
	
	addr.sin_family=AF_INET; // IPv4 family
	addr.sin_port=htons(PORT); //setting the port
	
	if(inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr)!=1)
	{
		printf("failed to assign address\n");
	}
	
	if(connect(socket_fd,(struct sockaddr *)&addr,addrlen) < 0)
		printf("connect error\n");
	else
	{
		printf("connected\n");
		write(socket_fd,name,strlen(name));
	}
	while(1)
	{
		printf("1. send connection request\n2. wait for connection\n");
		printf("Enter choice: ");
		scanf(" %c",&choice);
		write(socket_fd,&choice,1);
		switch(choice)
		{
			case '1':
				//write(socket_fd,"1",1);
				printf("\nEnter the destination client: ");
				scanf("%s",dest_client_name);
				write(socket_fd,&dest_client_name,strlen(dest_client_name));
				break;
			case '2':
				//write(socket_fd,"2",1);
				//while(read(socket_fd,&msg,100) <= 0);
				read(socket_fd,&msg,100);
				printf("\n%s\n",msg);
				break;
			default:
				printf("wrong choice");
				break;
		}
		pthread_create(&th_wr,NULL,&func_write,socket_fd);
		pthread_create(&th_rd,NULL,&func_read,socket_fd);
		//pthread_create(&th_wr,NULL,&func_write,socket_fd);
	
		pthread_join(th_rd,NULL);
		pthread_join(th_wr,NULL);
		}
	return 0;
}

				










