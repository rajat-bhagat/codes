/*
 * code to implement the thread creation and conditional exiting
 */

#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

char * theStatus = "ok";
int a=0,b=0;
void *threadfunc(void *parm)
{
	printf("Inside secondary thread\n");
	printf("enter 2 numbers\n");
	scanf("%d %d",&a,&b);
	if((a+b)<10)
		pthread_exit((void *)theStatus);
	else 
		pthread_exit((void *)"problem");
}

int main(int argc, char **argv)
{
	pthread_t             thread;
	int                   rc=0;
	void                 *status;

	printf("Enter Testcase - %s\n", argv[0]);

	printf("Create thread using attributes that allow join\n");
	pthread_create(&thread, NULL, threadfunc, NULL);

	printf("Wait for the thread to exit\n");
	pthread_join(thread, &status);
	if((strcmp((char *)status, theStatus))!=0) {
		printf("Secondary thread failed\n");
		printf("%p\n%s\n", status,(void *)status);	
		exit(1);
	}

	printf("\n%p\n%s\n", status,(void *)status);	
	printf("Got secondary thread status as expected\n");
	printf("Main completed\n");
	return 0;
}
