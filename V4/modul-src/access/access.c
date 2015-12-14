#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

#define THREAD_COUNT 10
#define DEVICE_NAME "/dev/openclose"
#define DEVICE_NAME_MINOR "/dev/opencloseminor"
#define NANO_TO_MS 1000

/* ms to sleep */
unsigned int sleepTime = 10;

struct thread_meta {
	int thread_id;
	char *device;
};

int usleep(unsigned int);

void *open_device(void *args) 
{
	
	int fd;
	char buffer[256];

	struct thread_meta *meta = (struct thread_meta *) args;
	printf("Thread %d started\n", meta->thread_id);
	
	fd = open(meta->device, O_RDWR);
	if (fd < 0) 
	{
		fprintf(stderr, "T%d: opening Error!\n", meta->thread_id);
		pthread_exit(NULL);
	} else {
		printf("T%d: open success", meta->thread_id);
	}

	/* perform read */
	if (read(fd, buffer, 256) == -1) {
		fprintf(stderr, "T:%d read Error!\n", meta->thread_id);
	} else {
		printf("T%d: read success\n", meta->thread_id);
	}

	usleep(NANO_TO_MS * sleepTime);

	/* perform write */
	/*if (write(fd, buffer, 256) == -1) {
		fprintf(stderr, "write Error!\n");
	} else {
		printf("Write success. ThreadID: %d\n", meta->thread_id);
	}*/


	if (close(fd) == -1) {
		fprintf(stderr, "T%d: Closing Error!\n", meta->thread_id);
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

		if(i % 2 == 0) {
			/* gerade indizes bekommen minor 0 */
			thread[i].device = DEVICE_NAME;

		} else {
			/* ungerade indizes bekommen minor 1 */
			thread[i].device = DEVICE_NAME_MINOR;
		}


		pthread_create(&threads[i], &attr[i], open_device, (void *) &thread[i]);
	}
	printf("%d Threads created\n", THREAD_COUNT);
	

	/* join threads */ 
	for(i = 0; i < THREAD_COUNT; i++) 
	{
		pthread_join(threads[i], NULL);
		pthread_attr_destroy (&attr[i]);
	}

	printf("%d Threads joined\n", THREAD_COUNT);


	return 0;
}
