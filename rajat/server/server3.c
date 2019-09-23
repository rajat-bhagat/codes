//server side code

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



int client_increment=0,sender_exit_flag=0,dest_exit_flag=0,temp_sender_id,temp_dest_id;
struct datanode {
	int a_id,c_count;
	char client_name[20];
};

char dest_client_name[20],sender_name[20];

//function performs the read operation and reads message from the connected clients and send them to each other
void *func_read(void* data1)
{
	
	char choice;
	int sender_index,dest_index;
	char str[1024],str1[1024];
	char msg[]="connected to client";
	struct datanode	*info = (struct datanode*)data1;
	while(1)
	{	
		sender_exit_flag=0;dest_exit_flag=0;
#ifdef DEBUG
		//printf("\nstart in id %d\n",info->a_id);
#endif
		read(info->a_id,&choice,1);
		printf("choice: %c\n",choice);
		printf("\nbefore choices\n");
		if(choice=='1')
		{
			strcpy(sender_name,info->client_name);
			//reading the destination client name 
			read(info->a_id,&dest_client_name,20); 

			for(dest_index=0;dest_index<10;dest_index++)
			{
				if(strncmp(data[dest_index].client_name,dest_client_name,strlen(dest_client_name))==0)
				{
					break;
				}
			}
			//getting the destination client id
			temp_dest_id=dest_index;
#ifdef DEBUG
			//printf("\nin id %d\n",info->a_id);
#endif
		}
		if(choice == '2')
		{
			//connected to destination client
			write(data[temp_dest_id].c_id,&msg,strlen(msg));
			sleep(1);
			write(data[temp_dest_id].c_id,&sender_name,20);

			for(sender_index=0;sender_index<10;sender_index++)
			{
				if(strncmp(data[sender_index].client_name,sender_name,strlen(sender_name))==0)
				{
					break;
				}
			}
			//getting the sender client id
			temp_sender_id=sender_index;
#ifdef DEBUG
			//printf("\nin id %d\n",info->a_id);
#endif
		}
		
		printf("\ncheckpoint1\n");
		while(1)
		{	
			//if the sender client sends the data
			if(info->a_id==data[temp_sender_id].c_id)
			{
				if(read(data[temp_sender_id].c_id,&str,1024)!=0)
				{
					
					write(data[temp_dest_id].c_id,str,strlen(str));
					if(strncmp(str,"bye",3)==0)
					{
						printf("%s from %s\n",str,data[temp_sender_id].client_name);
						sender_exit_flag=1;//chat close
					}
#ifdef DEBUG
					//printf("\nstart in id %d\n",info->a_id);
#endif
				}
				bzero(str,1024);
			}
			//if the destination client sends data
			else if(info->a_id==data[temp_dest_id].c_id)
			{
				if(read(data[temp_dest_id].c_id,&str1,1024)!=0)
				{
					
					write(data[temp_sender_id].c_id,str1,strlen(str1));
					if(strncmp(str1,"bye",3)==0)
					{
						printf("%s from %s\n",str1,data[temp_dest_id].client_name);
						dest_exit_flag=1;//chat close
					}
#ifdef DEBUG
					//printf("\nstart in id %d\n",info->a_id);
#endif
				}
				bzero(str1,1024);
			}
			else
			{
			}

			if(sender_exit_flag==1 || dest_exit_flag==1)
			{
#ifdef DEBUG
				//printf("sender_exit_flag= %d   dest_exit_flag= %d\n",sender_exit_flag,dest_exit_flag);
#endif
				break;//ready for next iteration
			}
			bzero(str,1024); //clearing the message buffer 
			bzero(str1,1024);

		}	 
	}
	// deallocating the pointer
	free(info);
}


int main()
{
	int ret=0,socket_fd,val=1;
	int max_client=0;
	struct sockaddr_in addr;
	int addrlen =sizeof(addr);
	pthread_t tid_rd[30],tid_wr;
	int count_rd_thread=0;
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

	while(1)
	{
		if(max_client < MAX) //resticting the number of clients
		{	
			// accept function accepts if a client requests to connect
			data[client_increment].c_id=accept(socket_fd,(struct sockaddr *)&addr,(socklen_t *)&addrlen);

			if(data[client_increment].c_id<0)
			{
				perror("\nserver accept failed\n");
			}
			else
			{
				printf("\nserver accepts the client %d.\n",client_increment+1);
				//reading the name of the client
				read(data[client_increment].c_id,&data[client_increment].client_name,20);
				max_client++;
			}
			
			data1 = malloc(sizeof(struct datanode));

			// printing the client information
			printf("accept_id of {client %d}: %d\n",client_increment+1,data[client_increment].c_id);
			printf("%s\n",data[client_increment].client_name);

			//passing information to thread function
			(*data1).a_id=data[client_increment].c_id;
			strcpy((*data1).client_name,data[client_increment].client_name);
			(*data1).c_count=client_increment+1;

			// creating the read thread to perform the read operation
			pthread_create(&tid_rd[count_rd_thread++],NULL,&func_read,data1); 
			client_increment++;
		}
	}

	return 0;
}



