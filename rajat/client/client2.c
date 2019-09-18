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
char dest_client_name[20];

//char str[1024],str1[1024];
int flag=0;

void * func_read(void *accept_id)
{
	char str[1024],temp[20];
	int q;
	//printf("testing");
	while(1)
	{
		//printf("hello");
		bzero(str,1024);
		// starts the reading opertion
		//read((long)accept_id,&temp,20);
		q=read((long)accept_id,&str,1024); 
		if(q!=0)
		{
			printf("\n%s : %s\n",temp,str);
			// clients shut down if the server is down*/
			if(strncmp("bye",str,3)==0) 
			{	
				//printf("server down\n");
				//pthread_mutex_destroy(&lock);
				break;
			}
		}else
		{
			break;
		}
		q=0;
		// clearing the message buffer
		bzero(str,1024); 
		bzero(temp,20);
	}
}


void * func_write(void *accept_id)
{
	//char dest_client_name[20];
	char str1[1024];
	bzero(dest_client_name,1024);
	if(flag==0)
	{
		printf("Enter destination client name: ");
		scanf("%s",dest_client_name);
		write((long)accept_id,dest_client_name,strlen(dest_client_name));
	}
	// sends only the client name to the server 
	 

	// control variables
	int  i=0,j=1,temp=0; 

	while(j)
	{
		j=0;
		printf("Enter message: ");
		scanf("%s",str1);
		// sending the data
		temp=write((long)accept_id,str1,strlen(str1)); 
		/*pthread_mutex_lock(&lock);
		// opening file in append mode
		fp=fopen(name1,"a+"); 
		if(fp==NULL)
			printf("error opening file");
		else
		{
			// recording the chat history
			fprintf(fp,"Me: %s\n",str1); 
			fclose(fp);
		}
		pthread_mutex_unlock(&lock);*/
		// shutting the client
		if(strncmp("bye",str1,3)==0)
		{
			printf("client exiting\n");
			//pthread_mutex_destroy(&lock);
			break;
		}

		i=0;
		bzero(str1,1024);
		j=1;
	}
}

int main()
{
	int x;
	// setting the client name 
        printf("Set client name: "); 
        scanf("%s",name);
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

	// assiging the address to the address variable
	ret = inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr); 
	if(!ret)
	{
		perror("failed to assign address");
	}	
	//pthread_create(&pid2,NULL,&func_write,(void *)(unsigned long long)socket_fd);
	//sends the connect request to the server
	ret= connect(socket_fd,(struct sockaddr *)&addr,addrlen);
	if(!ret)
	{	
		strcpy(name1,name);
		strcat(name1,".txt"); // setting the file name in which the chat is to be recorded
		x=write(socket_fd,name,strlen(name));
		//printf("%d\n",x);
		printf("Connected to server.\n");
		//creating the read thread to perform read operation  
		pthread_create(&pid,NULL,&func_read,(void *)(unsigned long long)socket_fd); 

		//creating the write thread to perform the write operation
		pthread_create(&pid2,NULL,&func_write,(void *)(unsigned long long)socket_fd);

		// joining the threads so that they can be properly executed
		pthread_join(pid,NULL);
		pthread_join(pid2,NULL);
	}
	else
	{
		perror("Not connected."); // connection error
	}
	pthread_mutex_destroy(&lock);
	return 0;
}
