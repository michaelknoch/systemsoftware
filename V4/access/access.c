#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#define THREAD_COUNT 5
#define DEVICE_NAME "/dev/openclose"


struct thread_meta {
	int thread_id;
	char *device;
};

void *open_device(void *args) 
{
	
	int fd;
	struct thread_meta *meta = (struct thread_meta *) args;
	printf("Thread %d started\n", meta->thread_id);
	
	fd = open(meta->device, O_RDONLY);
	if (fd < 0) 
	{
		fprintf(stderr, "Opening Error!\n");
	}

	if (close(fd) == -1) {
		fprintf(stderr, "Closing Error!\n");
	}

	pthread_exit(NULL);
}

int main() 
{

	int i;
	struct thread_meta *thread = NULL;	
	pthread_t *threads;
	pthread_attr_t *attr;
	thread = malloc(THREAD_COUNT * sizeof (struct thread_meta));

	if (thread == NULL) 
	{
		fprintf(stderr, "Allocation Error!\n");
		exit (1);
	}
	
	threads = malloc(THREAD_COUNT * sizeof(pthread_t));
	attr = malloc(THREAD_COUNT * sizeof(pthread_attr_t));

	if (threads == NULL || attr == NULL) 
	{
		fprintf(stderr, "Allocation Error!\n");
		exit (1);
	}


	for (i = 0; i < THREAD_COUNT; i++) 
	{
		thread[i].thread_id = i;
		thread[i].device = DEVICE_NAME;
		pthread_create(&threads[i], &attr[i], open_device, (void *) &thread[i]);
	}
	printf("%d Threads created\n", THREAD_COUNT);
	

	/* join threads */ 
	for(i = 0; i < THREAD_COUNT; i++) 
	{
		pthread_join(threads[i], NULL);
		pthread_attr_destroy (&attr[i]);
	}

	printf("Threads joined\n");


	return 0;
}
