#include <pthread.h>
#include <stdio.h>

void *routine(void *arg)
{
	printf("Hello from thread\n");
	return (NULL);
}

int main(void)
{
	pthread_t thread_1;

	/*
	starts a new thread in the calling process
	the thread invoke start_routine() that calls the passed routine() fct
	*/
	pthread_create(&thread_1, NULL, routine, NULL);



	/*
	makes the main programm wait for the specified thread to terminate
	*/
	pthread_join(thread_1, NULL);
}