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



int i=0,q,flag1=0,flag2=0,temp,temp1;
struct datanode {
	int a_id,c_count;
	char client_name[20];
};

char dest_client_name[20],sender_name[20];


void *func_read(void* data1)
{
	while(1)
	{
		char choice;
		int j,k;
		char str[1024],str1[1024];
		char msg[]="connected to client";
	
		
		struct datanode	*info = (struct datanode*)data1;
		printf("start in id %d\n",info->a_id);
		read(info->a_id,&choice,1);
		printf("choice: %c\n",choice);
		printf("before choices\n");
		if(choice=='1')
		{
			//printf("hello\n");
			//printf("%s\n",info->client_name);
			strcpy(sender_name,info->client_name);
			//printf("%s\n",temp_name);
			read(info->a_id,&dest_client_name,20); //reading the client name 
			//printf("%s\n",dest_client_name);
			for(j=0;j<10;j++)
			{
				if(strncmp(data[j].client_name,dest_client_name,strlen(dest_client_name))==0)
				{
					break;
				}
			}
			temp=j;
		}
		if(choice == '2')
		{
			//printf("hey\n");
			//strcat(msg,dest_client_name);
			write(data[temp].c_id,&msg,strlen(msg));
			write(data[temp].c_id,&sender_name,20);
			for(k=0;k<10;k++)
			{
				if(strncmp(data[k].client_name,sender_name,strlen(sender_name))==0)
				{
					break;
				}
			}
			temp1=k;
			printf("%s\n",sender_name);
			//write(info->a_id,&msg,strlen(msg));
			bzero(msg,100);
		}
		
		printf("checkpoint1\n");
		while(1)
		{
			//printf("checkpoint2");
			
			if(info->a_id==data[temp1].c_id)
			{
				if(read(data[temp1].c_id,&str,1024)!=0)
				{
					
					write(data[temp].c_id,str,strlen(str));
					//printf("%s\n",str);
					if(strncmp(str,"bye",3)==0)
					{
						printf("%s from %s\n",str,data[temp1].client_name);
						flag1=1;
						//pthread_exit(NULL);
						//break;
					}
				}
			}
			else if(info->a_id==data[temp].c_id)
			{
				if(read(data[temp].c_id,&str1,1024)!=0)
				{
					
					write(data[temp1].c_id,str1,strlen(str1));
					if(strncmp(str1,"bye",3)==0)
					{
						printf("%s from %s\n",str1,data[temp].client_name);
						flag2=1;
						//pthread_exit(NULL);
						//break;
					}
					//printf("%s\n",str1);
				}
			}
			else
			{
			}

			if(flag1==1 || flag2==1)
			{
				printf("flag1= %d   flag2= %d\n",flag1,flag2);
				//pthread_exit(NULL);
				break;
			}
			q=0;
			bzero(str,1024); //clearing the message buffer 
			bzero(str1,1024);

		}
		//break;
		free(info); // deallocating the pointer
	}
}


int main()
{
	int ret=0,socket_fd,val=1;
	int max_client=0;
	struct sockaddr_in addr;
	int addrlen =sizeof(addr);
	pthread_t tid_rd[30],tid_wr;
	int count=0;
	struct datanode *data1;
	void *status;
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
				//printf("%s\n",data[i].client_name);
				max_client++;
			}
			
			data1 = malloc(sizeof(struct datanode));

			printf("accept_id of {client %d}: %d\n",i+1,data[i].c_id);// printing the client information
			printf("%s\n",data[i].client_name);
			(*data1).a_id=data[i].c_id;
			strcpy((*data1).client_name,data[i].client_name);
			(*data1).c_count=i+1;
			//while(1)
			//{
				// creating the read thread to perform the read operation
				pthread_create(&tid_rd[count++],NULL,&func_read,data1); 
				//count++;
				//pthread_join(tid_rd[count],NULL);	
				//if(__INT(status)==NULL)
					//break;
			//}
			//count++;
			i++;
		}
	}

	return 0;
}



