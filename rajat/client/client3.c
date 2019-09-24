//client side code

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


//function performs the read operation and reads message from the connected client
void * func_read(void *accept_id)
{
	char str[1024];
	int ret;
	while(1)
	{
		bzero(str,1024);
		ret=read((long)accept_id,&str,1024); // starts the reading opertion 
		if(ret!=0)
		{
			printf("\nclient : %s\n",str);

			if(strncmp("bye",str,3)==0)
			{	
				pthread_exit(NULL);//exit if "bye" is received
			}
		}else
		{
			break;
		}
		ret=0;
		bzero(str,1024); // clearing the message buffer
	}
}


//function performs the write operation and sends the message to the connected client
void * func_write(void *accept_id)
{
	char str1[1024];

	while(1)
	{
		printf("Enter message: ");
		scanf("%s",str1);
		write((long)accept_id,str1,strlen(str1)); // sending the data
		
		if(strncmp("bye",str1,3)==0) // closing the chat
		{
			printf("chat closed bye me\n");
			pthread_exit(NULL);// closing the write operation
		}
		bzero(str1,1024);
	}
}


int main()
{
	char name[20],dest_client_name[20],sender_name[20];
	int val=1, socket_fd,bytes;
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
	
	//connecting to the server
	if(connect(socket_fd,(struct sockaddr *)&addr,addrlen) < 0)
		printf("connect error\n");
	else
	{
		printf("connected\n");
		//sending the client name
		write(socket_fd,name,strlen(name));
	}
	while(1)
	{
		printf("1. send connection request\n2. wait for connection\n3. exit\n");
		printf("Enter choice: ");
		scanf(" %c",&choice);
		//select choice
		write(socket_fd,&choice,1);
		switch(choice)
		{
			case '1':
				//write(socket_fd,"1",1);
				printf("\nEnter the destination client: ");
				scanf("%s",dest_client_name);
				bytes=write(socket_fd,&dest_client_name,strlen(dest_client_name));
#ifdef DEBUG
				//printf("%d\n",bytes);
#endif
				break;
			case '2':
				read(socket_fd,&msg,100);
				read(socket_fd,&sender_name,20);
				printf("\n%s\n",msg);
#ifdef DEBUG
				//printf("%s\n",sender_name);
#endif
				break;
			case '3':
				exit(0);
		}
		//read thread 
		pthread_create(&th_rd,NULL,&func_read,(void *)(unsigned long long)socket_fd);
		//write thread
		pthread_create(&th_wr,NULL,&func_write,(void *)(unsigned long long)socket_fd);
	
		pthread_join(th_rd,NULL);
		pthread_join(th_wr,NULL);
		}
	return 0;
}

				










