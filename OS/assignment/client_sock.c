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
#define PORT 8000
#define MAX 5
//#define FILE "client1.txt" 

int q;
char str[1024],str1[1024];

struct DATANODE {
	int a_id,c_count;
};
struct DATANODE data;

FILE *fp;

void *func_read(int accept_id)
{
	printf("\nRead_thread line no.%d\n",__LINE__);
	while(1)
	{
		q=read(accept_id,&str,1024);
		if(q!=0)
		{
			printf("\nServer : %s\n",str);
			fp=fopen("client1.txt","a+");
			if(fp==NULL)
				printf("error opening file");
			else
			{
				fprintf(fp,"\nserver:  %s\n",str);
				fclose(fp);
			}

			if(strcmp("bye",str)==0)
			{	
				printf("server down");
				exit(0);
			}

		}else
		{
			break;
		}
		q=0;
		bzero(str,1024);
	}

}

void *func_write(int accept_id)
{
	int  i=0,j=1,temp=0;
	while(j)
	{
		j=0;
		printf("\nClient:");
		while ((str1[i++] = getchar()) != '\n');
		temp=write(accept_id,str1,strlen(str1));
		fp=fopen("client1.txt","a+");
		if(fp==NULL)
			printf("error opening file");
		else
		{
			fprintf(fp,"\nMe: %s\n",str1);
			fclose(fp);
		}
		if(strcmp("bye",str1)==0)
		{
			printf("client exiting");
			exit(0);
		}

		i=0;
		printf("\nline no.%d, and write status=%d\n",__LINE__,temp);
		bzero(str1,1024);
		j=1;
	}

}



int main()
{

	int i,ret=0,socket_fd,val=1,count=0,a[MAX];
	struct sockaddr_in addr;
	int addrlen =sizeof(addr);
	pthread_t pid,pid2;
	int client_count =0;

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

	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);


	ret = inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
	if(!ret)
	{
		perror("failed to assign address");
	}	

	//connect

	i=0;

	ret= connect(socket_fd,(struct sockaddr *)&addr,addrlen);
	if(!ret)
	{	printf("Connected to server.\n");
		pthread_create(&pid,NULL,&func_read,socket_fd);
		pthread_create(&pid2,NULL,&func_write,socket_fd);

		pthread_join(pid,NULL);
		pthread_join(pid2,NULL);


	}
	else
	{
		perror("Not connected.");
	}

	//fclose(fp);
	return 0;
}
