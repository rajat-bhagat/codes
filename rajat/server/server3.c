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
#define MAX 3


struct database{
	int c_id;
	char client_name[20];
	int count;
};
struct database data[10];

int i=0,q,flag=0;
struct datanode {
	int a_id,c_count;
	char client_name[20];
};

char dest_client_name[20];


void *func_read(void* data1)
{
	int j,temp;
	char str[1024],str1[1024];
	char msg[]="connected to ";
	struct datanode	*info = (struct datanode*)data1;
	read(info->a_id,&dest_client_name,20); //reading the client name 
	for(j=0;j<10;j++)
	{
		if(strncmp(data[j].client_name,dest_client_name,strlen(dest_client_name))==0)
		{
			break;
		}
	}
	temp=j;
	strcat(msg,dest_client_name);
	write(data[temp].c_id,&msg,strlen(msg));
	bzero(msg,100);

	while(1)
	{
		//q=read(info->a_id,&str,1024); // reading the message sent by client 
		//if(q!=0) //if the read funtion reads NOT NULL value
		if(q=read(info->a_id,&str,1024)!=0)
		{
			//printf("\nClient %s:",info->client_name);
			//printf(" %s\n",str);
			//printf("%d",strlen(str));
			//printf("%s\n",str);
			//printf("Enter message: ");
			//scanf("%s",str1);
			write(data[temp].c_id,str,strlen(str));

			/*if(strcmp("bye",str)==0) //when the client exits
			{
				max_client--;
			}*/
		}
		else if(q=read(data[temp].c_id,&str1,1024)!=0)
		{
			//printf("%s\n",str);
			//printf("Enter message: ");
			//scanf("%s",str1);
			write(info->a_id,str1,strlen(str1));
		}
		else
		{
			break;
		}
		q=0;
		bzero(str,1024); //clearing the message buffer 
		bzero(str1,1024);

	}
	free(info); // deallocating the pointer
}




int main()
{
	int ret=0,socket_fd,val=1;
	int max_client=0;
	struct sockaddr_in addr;
	int addrlen =sizeof(addr);
	pthread_t tid_rd,tid_wr;
	int count=0;
	struct datanode *data1;
	//struct DATANODE2 data_write;

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
	if(listen(socket_fd,0)!=0)
	{
		perror("listen failed. ");
		return 0;
	}
	else
		printf("sever is listening..\n");

	//pthread_create(&tid_rd,NULL,);
	while(1)
	{
		//printf("count = %d\n",count);
		if(max_client < MAX) //resticting the number of clients
		{	
			// accept function accepts if a client requests to connect
			data[i].c_id=accept(socket_fd,(struct sockaddr *)&addr,(socklen_t *)&addrlen);

			if(data[i].c_id<0)
			{
				perror("\nserver accept failed\n");
			}
			else
			{
				printf("\nserver accepts the client %d.\n",i+1);
				read(data[i].c_id,&data[i].client_name,20);//reading the name of the client
				printf("%s\n",data[i].client_name);
				max_client++;
			}

			data1 = malloc(sizeof(struct datanode));

			printf("accept_id of {client %d}: %d\n",i+1,data[i].c_id);// printing the client information
			printf("%s\n",data[i].client_name);
			(*data1).a_id=data[i].c_id;
			strcpy((*data1).client_name,data[i].client_name);
			(*data1).c_count=i+1;

			pthread_create(&tid_rd,NULL,&func_read,data1); // creating the read thread to perform the read operation
			i++;
		}
	}

	return 0;
}



