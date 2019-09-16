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
#define MAX 4

struct database{
	int c_id;
	char client_name[20];
	int count;
};
struct database data[10];

int max_client=0;

/*void *func_write(void *data_write1)
  {

  printf("write thread on\n");
//struct DATANODE2 *info1 ;
//info1 = (struct DATANODE2*)data_write1;	
int i=0,j=0; // control variables

while(1)
{
if() //checks that client is present or not
{
//while ((str1[i++] = getchar()) != '\n'); //takes the message untill enter is pressed
gets(str1);
printf("reply to client:");// whom to reply
gets(cname);
for(j=0;j<info1->c_count;j++)
{
write(info1->a_id[j],&cname,strlen(cname));// sending the name of the client for whom the message is meant
sleep(5);
i=write(info1->a_id[j],&str1,strlen(str1));// sending the reply
}
if(strncmp("bye",str1,3)==0) // to shut the server down
{
printf("server shutting down\n");
exit(0);
}

bzero(str1,1024); // clearing the buffer
}
/*else
{
printf("\nNo clients connected in last 10 sec");
sleep(10);
}
}
}*/


int main()
{
	int ret=0,socket_fd,val=1,i=0;
	struct sockaddr_in addr;
	int addrlen =sizeof(addr);
	pthread_t tid_rd,tid_wr;
	int client_count =0;
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
	if(listen(socket_fd,MAX)!=0)
	{
		perror("listen failed. ");
		return 0;
	}
	else
		printf("sever is listening..\n");
	//pthread_create(&tid_wr,NULL,&func_write,&data_write); //creating the write thread to perform the write operation

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
				max_client++;
			}
			read(data[i].c_id,&data[i].client_name,strlen(data[i].client_name));

				//data = malloc(sizeof(struct DATANODE));

				//(*data).a_id=data_write.a_id[data_write.c_count];
				//database[i].a_id=data_write.a_id[data_write.c_count];
				//(*data).c_count=data_write.c_count+1;	
				printf("accept_id of {client %d}: %d\n",i+1,data[i].c_id);// printing the client information
				printf("%s  %d\n",data[i].client_name,sizeof(data[i].client_name));

			//bzero(str,1024);
			//pthread_create(&tid_rd,NULL,&func_read,&data[i]); // creating the read thread to perform the read operation
			i++;
			//data_write.c_count=data_write.c_count +1; // incrementing the count for the next client
		}
		/*else
		  {
		  if(listen(socket_fd,MAX)!=0)
		  {
		  perror("listen failed. ");
		  return 0;
		  }
		  else
		  printf("sever is listening..\n");
		  }*/		

	}
	return 0;
}

