#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<pthread.h>
#include<stdlib.h>
#define PORT 8000
#define MAX 1

int q;
char str[1024],str1[1024];

struct DATANODE {
	int a_id,c_count;
};
struct DATANODE *data;

struct DATANODE2 {
	int a_id[20];
	int c_count;
};
struct DATANODE data_write;


void clear_client(int val)
{
	
}


void *func_read(void* data)
{
	struct DATANODE	*info = (struct DATANODE*)data;	


	printf("\nreceived data:\naccept id: %d, count: %d",(*info).a_id,(*info).c_count);

	while(1)
	{
		q=read(info->a_id,&str,1024);
		if(q!=0)
		{
			printf("\nClient %d:",info->c_count);
			printf(" %s\n",str);
			if(strcmp("Bye",str)==0)
			{
				clear_client(info->c_count);
			}


		}else
		{

			break;
		}
		q=0;
		bzero(str,1024);
	}
	free(info);
}

void *func_write(void *data_write1)
{

	printf("write thread on\n");
	struct DATANODE2 *info1 ;
	info1 = (struct DATANODE2*)data_write1;	
	int  i=0,j=0;

	while(1)
	{
		if(info1->c_count+1)
		{

			while ((str1[i++] = getchar()) != '\n');
			for(j=0;j<info1->c_count;j++)
			{

				i=write(info1->a_id[j],&str1,strlen(str1));
				//printf("\ni:%d and LINE:%d",i,__LINE__);
			}
			i=0;

			bzero(str1,1024);

		}else
			printf("\nNo clients connected in last 10 sec");
		sleep(10);
	}
}



int main()
{

	int i,ret=0,socket_fd,val=1,count=0;
	struct sockaddr_in addr;
	int addrlen =sizeof(addr);
	pthread_t tid[30],tid_wr;
	int client_count =0;
	//struct DATANODE2 data_write;

	//create
	socket_fd = socket(AF_INET,SOCK_STREAM,0);
	if(socket_fd)
	{
		printf("socket created\n");
	}
	else
	{	perror("socket failed\n");
		return -1;
	}

	//setsockopt

	ret= setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

	if(ret!=0)
	{
		perror("setsockopt\n");
		return -1;
	}
	else
	{
		printf("setsockopt success.\n");
	}

	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.s_addr= INADDR_ANY;

	//bind

	if(bind(socket_fd,(struct sockaddr*)&addr,sizeof(addr))!=0)
	{
		perror("bind error:");
		return 0;
	}
	else
		printf("bind success\n");

	//listen

	if(listen(socket_fd,MAX)!=0)
	{

		perror("listen failed. ");
		return 0;
	}
	else
		printf("sever is listening..\n");


	//accept

	i=0;
	//data_write.c_count=client_count;
	pthread_create(&tid_wr,NULL,&func_write,&data_write);	

	while(1)
	{
		if(data_write.c_count < MAX+3)
		{
			data_write.a_id[data_write.c_count]=accept(socket_fd,(struct sockaddr *)&addr,(socklen_t *)&addrlen);

			if(data_write.a_id[data_write.c_count]<0)
			{
				perror("\nserver accept failed\n");
			}
			else
				printf("\nserver accepts the client %d.\n",data_write.c_count+1);

			data = malloc(sizeof(struct DATANODE));

			(*data).a_id=data_write.a_id[data_write.c_count];
			(*data).c_count=data_write.c_count+1;	
			printf("accept_id of {client %d}: %d\n",data_write.c_count+1,data_write.a_id[data_write.c_count]);

			bzero(str,1024);
			pthread_create(&tid[count++],NULL,&func_read,data);	
			data_write.c_count=data_write.c_count +1;
		}		

	}
	return 0;
}
