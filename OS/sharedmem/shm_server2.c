#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include<semaphore.h>
#include<fcntl.h>

sem_t *mutex;


int main() 
{ 
	//pthread_mutex_t mutex;
	//pthread_mutex_init(&mutex,NULL);
	mutex = sem_open("sem_write", O_CREAT, 0666, 1);

	sem_unlink("sem_write");

//	sem_init(&mutex,1,1);
	//char e[]="end";
	int c;
	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 
//	sem_wait(&mutex);
	// shmat to attach to shared memory 
	char *str1 = (char*) shmat(shmid,NULL,0); 
	//char *str1;
//	sem_post(&mutex);
	//printf("before while loop\n");
	while(1)
	{
		//printf("entered while loop\n");
		//printf("before sem_wait");
		sem_wait(mutex);
		//printf("after sem_wait");
		printf("Data read from memory: %s\n",str1);
		sem_post(mutex);
		c=strncmp(str1,"end",3);
		if(c==0)
		{
			exit(0);
		}
		sleep(2);
	}	

	//detach from shared memory  
	shmdt(str1); 

	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL); 
	//pthread_mutex_destroy(&mutex);
	sem_destroy(&mutex);
	return 0; 
} 
