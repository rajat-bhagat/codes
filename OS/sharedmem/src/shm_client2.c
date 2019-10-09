/**
 * @file stdio.h
 * @brief this header file contains the standard input output functions
 * @file stdlib.h
 * @brief this header file contains the standard funtions for process control, memory allocation etc
 * @file string.h 
 * @brief this header file contains the string manipulation functions
 * @file pthread.h
 * @brief this header file contains the thread related funtions
 * @file semaphore.h 
 * @brief this header file contains the semaphore fnunctions
 * @file fcntl.h
 * @brief this header file contains standard Macros needed for different functions
 * @file unistd.h
 * @brief this header file contains the sleep function that is used here
 * @file sys/shm.h
 * @brief this file contains the shared memory functions
 *
 * @author Rajat Bhagat
 *
 * @date 10/03/2019 
 */

#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include<semaphore.h>
#include<fcntl.h>

///these are the read and write semaphore pointers to maintain exclusivity between the server and client processes
//@{
sem_t *read_block,*write_block;
///@}

/// this the mutex to maintain lock between the threads
pthread_mutex_t lock;


/**
 * @struct shmseg
 * @brief this is the message structure containing the id of the message writer and the message
 *
 * @var id
 * it contains the id of the message writer
 *
 * @var message
 * it contains the message
 */
struct shmseg{
	int id;
	char message[256];
};


/**
 * this function is the write function used by the write thread
 * @param args it contains the address of the shared memory shared between the server and the client
 */
void *func_write(void * args)
{
	while(1)
	{
		struct shmseg *f = (struct shmseg *)args;
		printf("enter data: ");
		scanf("%s",(*f).message);
		sem_wait(write_block);
		pthread_mutex_lock(&lock);
		(*f).id=1;
		printf("\ndata entered is : %s\n",(*f).message);
		sleep(1);
		pthread_mutex_unlock(&lock);
		sleep(1);
		sem_post(write_block);
		if(strncmp((*f).message,"bye",3)==0)
			exit(0);
	}
}


/**
 * this function is the read function used by the read thread
 * @param args it contains the address of the shared memory shared between the server and the client
 */
void *func_read(void *args)
{	
	struct shmseg *f = (struct shmseg *)args;
	while(1)
	{
		sem_wait(read_block);
		pthread_mutex_lock(&lock);

		if((*f).id==0){
			printf("\ndata received is : %s\n",(*f).message);
		}

		pthread_mutex_unlock(&lock);
		sem_post(read_block);
		sleep(2);
	}
}
		

/**
 * this function is the main funtion which creates the semaphores, mutex, shared memory and the threads.
 *
 * @return returns 0 as return type is int
 */
int main() 
{ 
	pthread_t tid_r,tid_w;
	struct shmseg *buffer;

	pthread_mutex_init(&lock,NULL);

	// the semaphores are created 
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
