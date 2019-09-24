#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include<semaphore.h>

//sem_t mutex;

int main() 
{ 
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex,NULL);
//	sem_init(&mutex,1,1);
	//char e[]="end";
	int c;
	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 
//	sem_wait(&mutex);
	// shmat to attach to shared memory 
	char *str = (char*) shmat(shmid,NULL,0); 
	//char *str1;
//	sem_post(&mutex);

	while(1)
	{
		//strcpy(str1,str);
		//str1=str;
		c=strncmp(str,"end",3);
		if(c!=0)
		{
			/*for(int i=0;str[i]!='\0';i++)
			{
				if(str[i]>=97 && str[i]<=122)
				{
					str[i]=str[i]-32;
				}
				else if(str[i]>=65 && str[i]<=90)
				{	
					str[i]=str[i]+32;
				}
			}*/
			//if(strcmp)
			pthread_mutex_lock(&mutex);
			printf("Data read from memory: %s\n",str);
			pthread_mutex_unlock(&mutex);
			sleep(5);
		}
		else
		{
			printf("Data read from memory: %s\n",str);	
			exit(0);
		}
	}	

	//detach from shared memory  
	shmdt(str); 

	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL); 
	pthread_mutex_destroy(&mutex);
//	sem_destroy(&mutex);
	return 0; 
} 
