#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <pthread.h>
#include <stdio.h> 
#include <string.h>
#include<semaphore.h>

//sem_t mutex;

int main() 
{ 
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex,NULL);
	//sem_init(&mutex,1,1);	
	// ftok to generate unique key 
	char e[]="end";
	int c;
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 

	// shmat to attach to shared memory 
	//sem_wait(&mutex);
	char *str = (char*) shmat(shmid,NULL,0); 
	//sem_post(&mutex);	
	while(1)
	{
		printf("Write Data : "); 
		pthread_mutex_lock(&mutex);
		fgets(str,20,stdin); 
		pthread_mutex_unlock(&mutex);
		printf("Data written in memory: %s\n",str);
		c=strncmp("end",str,3);
		if(c==0)
		{
			exit(0);
		}
	}

	//detach from shared memory  
	shmdt(str); 
	pthread_mutex_destroy(&mutex);
	//sem_destroy(&mutex);
	return 0; 
} 
