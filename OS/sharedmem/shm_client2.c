#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include<semaphore.h>
#include<fcntl.h>

sem_t *read_block,*write_block;
pthread_mutex_t lock;

struct shmseg{
	int id;
	char message[256];
};


void *func_write(void * args)
{
	int *t;
	while(1)
	{
		struct shmseg *f = (struct shmseg *)args;
		//pthread_mutex_lock(&lock);
		//sem_wait(write_block);
		printf("enter data: ");
		scanf("%s",(*f).message);
		sem_wait(write_block);
		pthread_mutex_lock(&lock);
		//scanf("%s",(*f).message);
		(*f).id=1;
		//printf("\nin write thread\n");
		printf("\ndata entered is : %s\n",(*f).message);
		pthread_mutex_unlock(&lock);
		sleep(1);
		sem_post(write_block);
		if(strncmp((*f).message,"bye",3)==0)
			exit(0);
		//sleep(2);
		//pthread_mutex_unlock(&lock);
		sleep(1);
	}
}

void *func_read(void *args)
{	
	struct shmseg *f = (struct shmseg *)args;
	int *t;
	//printf("\nin read thread\n");
	while(1)
	{
		//pthread_mutex_lock(&lock);
		sem_wait(read_block);
		//printf("\n read thread\n");
		pthread_mutex_lock(&lock);

		if((*f).id==0){
			printf("\ndata received is : %s\n",(*f).message);
			//printf("\nin read thread\n");
		}

		pthread_mutex_unlock(&lock);
		sem_post(read_block);
		//if(strncmp((*f).message,"bye",3)==0)
			//exit(0);
		sleep(2);
		//pthread_mutex_unlock(&lock);
	}
}
		

int main() 
{ 
	pthread_t tid_r,tid_w;
	struct shmseg *buffer;

	pthread_mutex_init(&lock,NULL);

	write_block = sem_open("sem1", 0);
	read_block = sem_open("sem2",0);

	if(write_block==NULL)
		printf("\nsemaphore not opened\n");

	if(write_block==NULL)
		printf("\nsemaphore not opened\n");

	sem_unlink("sem1");
	sem_unlink("sem2");

	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,sizeof(struct shmseg),0666|IPC_CREAT); 

	// shmat to attach to shared memory 
	buffer = (struct shmseg *) shmat(shmid,NULL,0); 

	pthread_create(&tid_w,NULL,func_write,(void *)buffer);
	pthread_create(&tid_r,NULL,func_read,(void *)buffer);

	
	pthread_join(tid_w,NULL);
	pthread_join(tid_r,NULL);
	

	//detach from shared memory  
	shmdt(buffer); 

	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL); 
	pthread_mutex_destroy(&lock);
	sem_destroy(write_block);
	sem_destroy(read_block);
	return 0; 
} 
