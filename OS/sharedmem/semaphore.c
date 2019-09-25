#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,writeblock;
int rcount = 0;

void *reader(void *arg)
{
	char *f;
	f = (char *)arg;
	sem_wait(&mutex);
	rcount = rcount + 1;
	if(rcount==1)
		sem_wait(&writeblock);
	sem_post(&mutex);
	printf("Data read by the reader is %d\n",data);
	sleep(1);
	sem_wait(&mutex);
	//rcount = rcount - 1;
	//if(rcount==0)
	sem_post(&writeblock);
	sem_post(&mutex);
}

void *writer(void *arg)
{
	char *f;
	f = (char *)arg;
	sem_wait(&writeblock);
	printf("enter data");
	scanf("%s",data);
	//data++;
	//printf("Data writen by the writer is %d\n",data);
	sleep(1);
	sem_post(&writeblock);
}

int main()
{
	int b; 
	pthread_t rtid,wtid;
	sem_init(&mutex,0,1);
	sem_init(&writeblock,0,1);
	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 
	//	sem_wait(&mutex);
	// shmat to attach to shared memory 
	char *str = (char*) shmat(shmid,NULL,0); 
	//for(i=0;i<=2;i++)
	// {
	pthread_create(&wtid,NULL,writer,(void *)str);
	pthread_create(&rtid,NULL,reader,NULL);
	// }
	// for(i=0;i<=2;i++)
	//{
	pthread_join(wtid,NULL);
	pthread_join(rtid,NULL);
	// }
	return 0;
}
