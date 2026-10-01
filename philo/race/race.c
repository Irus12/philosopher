#include <pthread.h>
#include <stdio.h>

int counter = 0;  // ressource partagée
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void *increment(void *arg)
{
	int i = 0;
	while(i < 1000000)
	{
		//sandwich le bout de code qu'on veut proteger comme ca
		pthread_mutex_lock(&mutex);
		counter++; //ressource partagé par les thread
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

int main(void)
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1, NULL, increment, NULL);
	pthread_create(&t2, NULL, increment, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("counter = %d (attendu: 2000000)\n", counter);
	pthread_mutex_destroy(&mutex);
	return (0);
}