#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *function(void * val)
{
	printf("ptid : %u  value : %d\n",pthread_self(),(int *)val);
	pthread_exit(1);
}

void main()
{
	pthread_t thread1, thread2;
	int status;
	int val1 = 35, val2 = 45;
	pthread_create(&thread1, NULL, function, (void *)val1);

	pthread_create(&thread2, NULL, function, (void *)val2);

	pthread_join(thread1, (void *)&status);
	printf("\n%s\n",(char *)status);
	pthread_join(thread2, NULL);

}
