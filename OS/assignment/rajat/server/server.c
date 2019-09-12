//server side code for the chat application

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<pthread.h>
#include<stdlib.h>
#define PORT 8000 //port 
#define MAX 2

int q,count=0;
char str[1024],str1[1024];

struct DATANODE {
	int a_id,c_count;
	char client_name[20];
};
struct DATANODE *data;

struct DATANODE2 {
	int a_id[20];
	int c_count;
};


// the function to receive data called in the read thread
void *func_read(void* data)
{
	struct DATANODE	*info = (struct DATANODE*)data;	
 	read(info->a_id,&str,1024); //reading the client name 
        strcpy(info->client_name,str);
        bzero(str,1024);

	while(1)
	{
		q=read(info->a_id,&str,1024); // reading the nessage sent by client 
		if(q!=0) //if the read funtion reads NOT NULL value
  		{
			printf("\nClient %s:",info->client_name);

			printf(" %s\n",str);
			if(strcmp("bye",str)==0) //when the client exits
			{
				count--;
			}
		}else
		{
			break;
		}
		q=0;
		bzero(str,1024); //clearing the message buffer 
	}
	free(info); // deallocating the pointer
}

// the function to send the data to client called in the write thread
void *func_write(void *data_write1)
{

	printf("write thread on\n");
	struct DATANODE2 *info1 ;
	info1 = (struct DATANODE2*)data_write1;	
	int i=0,j=0; // control variables

	while(1)
	{
		if(info1->c_count+1) //checks that client is present or not
		{

			while ((str1[i++] = getchar()) != '\n'); //takes the message untill enter is pressed
			for(j=0;j<info1->c_count;j++)
			{
				i=write(info1->a_id[j],&str1,strlen(str1));
			}
			if(strncmp("bye",str1,3)==0) // to shut the server down
                        {
                                printf("server shutting down\n");
                                exit(0);
                        }
			i=0;
			bzero(str1,1024); // clearing the buffer
		}
		else
		{
			printf("\nNo clients connected in last 10 sec");
			sleep(10);
		}
	}
}


int main()
{
	int ret=0,socket_fd,val=1;
	struct sockaddr_in addr;
	int addrlen =sizeof(addr);
	pthread_t tid[30],tid_wr;
	int client_count =0;
	struct DATANODE2 data_write;

	//create socket
	socket_fd = socket(AF_INET,SOCK_STREAM,0);
	if(socket_fd)
	{
		printf("socket created\n");
	}
	else
	{	perror("socket failed\n");
		return -1;
	}

	//setsockopt sets the sttributes or properties of the socket

	ret= setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

	if(ret!=0)
	{
		perror("setsockopt error\n");
		return -1;
	}
	else
	{
		printf("setsockopt success.\n");
	}

	addr.sin_family=AF_INET; //IPv4 family
	addr.sin_port=htons(PORT);// setting port
	addr.sin_addr.s_addr= INADDR_ANY; // accepts any type of address

	//bind the socket

	if(bind(socket_fd,(struct sockaddr*)&addr,sizeof(addr))!=0)
	{
		perror("bind error:");
		return 0;
	}
	else
		printf("bind success\n");

	//listen makes the server to start accepting clients
	if(listen(socket_fd,MAX)!=0)
	{
		perror("listen failed. ");
		return 0;
	}
	else
		printf("sever is listening..\n");
	pthread_create(&tid_wr,NULL,&func_write,&data_write); //creating the write thread to perform the write operation

	while(1)
	{
		if(count < MAX+1) //resticting the number of clients
		{	
			// accept function accepts if a client requests to connect
			data_write.a_id[data_write.c_count]=accept(socket_fd,(struct sockaddr *)&addr,(socklen_t *)&addrlen);

			if(data_write.a_id[data_write.c_count]<0)
			{
				perror("\nserver accept failed\n");
			}
			else
			{
				printf("\nserver accepts the client %d.\n",data_write.c_count+1);
				count++;
			}

			data = malloc(sizeof(struct DATANODE));

			(*data).a_id=data_write.a_id[data_write.c_count];
			(*data).c_count=data_write.c_count+1;	
			printf("accept_id of {client %d}: %d\n",data_write.c_count+1,data_write.a_id[data_write.c_count]);// printing the client information

			bzero(str,1024);
			pthread_create(&tid[count++],NULL,&func_read,data); // creating the read thread to perform the read operation
			data_write.c_count=data_write.c_count +1; // incrementing the count for the next client
		}		

	}
	return 0;
}
