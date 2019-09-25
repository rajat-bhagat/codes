#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <pthread.h>
#include <stdio.h> 
#include <string.h>
#include<semaphore.h>
#include<fcntl.h>


sem_t *readblock,*writeblock;
pthread_mutex_t mutex;

int rcount = 0;

struct shmmsg
{
	char writer_name[20];
	char msg[1024];
	char receiver_name[20];
	int complete_flag;
};


void *reader(void *arg)
{
	struct shmmsg *f= (struct shmmsg *)arg;
	while(1)
	{
		//sem_wait(writeblock);
		if(f->complete_flag==1)
		{
			printf("Data read by the reader is %s\n",f->msg);
			sleep(2);
		}
		//sem_post(writeblock);
	}
}

/*void *writer(void *arg)
{
	char *f;
	f = (char *)arg;
	while(1)
	{
		sem_wait(writeblock);
		printf("enter data");
		scanf("%s",f);
		sleep(1);
		sem_post(writeblock);
	}
}*/

int main()
{
	int b; 
	pthread_t rtid,wtid;
	//sem_init(&readblock,0,1);
	//sem_init(&writeblock,1,1);
	struct shmmsg *data; 

	pthread_mutex_init(&mutex,NULL);
	writeblock = sem_open("sem_write", 0);
	//readblock = sem_open("sem_read", 0);

	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 
	
	// shmget returns an identifier in shmid 
	int shmid = shmget(key,sizeof(struct shmmsg),0666|IPC_CREAT); 
	//	sem_wait(&mutex);
	// shmat to attach to shared memory 
	printf("shared memory created\n");

	data = (struct shmmsg*) shmat(shmid,NULL,0); 
	printf("shared memory attached\n");


	//pthread_create(&wtid,NULL,writer,(void *)str);
	pthread_create(&rtid,NULL,reader,(void *)data);
	

	//pthread_join(wtid,NULL);
	pthread_join(rtid,NULL);

	return 0;
}
