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
#define MAX 3

FILE *fp;
pthread_mutex_t lock;

char name[30],name1[30];
int q;
char str[1024],str1[1024];

void *func_read(int accept_id)
{
	while(1)
	{
		bzero(str,1024);
		q=read(accept_id,&str,1024); // starts the reading opertion 
		if(q!=0)
		{
			printf("\nServer : %s\n",str);
			pthread_mutex_lock(&lock);
			fp=fopen(name1,"a+"); //file to save the chat history
 			if(fp==NULL)
				printf("error opening file");
			else
			{
				fprintf(fp,"server:  %s\n",str); // recording chat history in the file 
				fclose(fp);
			}
			pthread_mutex_unlock(&lock);
			if(strncmp("bye",str,3)==0) // clients shut down if the server is down
			{	
				printf("server down\n");
				pthread_mutex_destroy(&lock);
				exit(0);
			}
		}else
		{
			break;
		}
		q=0;
		bzero(str,1024); // clearing the message buffer
	}
}


void *func_write(int accept_id)
{
write(accept_id,name,strlen(name)); // sends only the client name to the server 
	
int  i=0,j=1,temp=0; // control variables

	while(j)
	{
		j=0;
		while ((str1[i++] = getchar()) != '\n');
		temp=write(accept_id,str1,strlen(str1)); // sending the data
		pthread_mutex_lock(&lock);
		fp=fopen(name1,"a+"); // opening file in append mode
		if(fp==NULL)
			printf("error opening file");
		else
		{
			fprintf(fp,"Me: %s\n",str1); // recording the chat history
			fclose(fp);
		}
		pthread_mutex_unlock(&lock);
		if(strncmp("bye",str1,3)==0) // shutting the client
		{
			printf("client exiting\n");
			pthread_mutex_destroy(&lock);
			exit(0);
		}

		i=0;
		bzero(str1,1024);
		j=1;
	}
}

int main()
{
	int x;
        printf("Set client name:\n"); // setting the client name 
        gets(name);
	int i,ret=0,socket_fd,val=1,count=0,a[MAX];
	struct sockaddr_in addr;
	int addrlen =sizeof(addr);
	pthread_t pid,pid2;
	int client_count =0;
	if(pthread_mutex_init(&lock, NULL)!=0)
	{
		printf("mutex failed");
	}

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


	ret = inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr); // assiging the address to the address variable
	if(!ret)
	{
		perror("failed to assign address");
	}	
	//sends the connect request to the server
	ret= connect(socket_fd,(struct sockaddr *)&addr,addrlen);
	if(!ret)
	{	
		strcpy(name1,name);
		strcat(name1,".txt"); // setting the file name in which the chat is to be recorded
		x=write(socket_fd,name,strlen(name));
		printf("Connected to server.\n");
		pthread_create(&pid,NULL,&func_read,socket_fd); //creating the read thread to perform read operation  
		pthread_create(&pid2,NULL,&func_write,socket_fd);//creating the write thread to perform the write operation

		pthread_join(pid,NULL);
		pthread_join(pid2,NULL);// joining the threads so that they can be properly executed
	}
	else
	{
		perror("Not connected."); // connection error
	}
	pthread_mutex_destroy(&lock);
	return 0;
}
