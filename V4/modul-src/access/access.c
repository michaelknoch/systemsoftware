#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#define THREAD_COUNT 100
#define DEVICE_NAME "/dev/openclose"
#define DEVICE_NAME_MINOR "/dev/opencloseminor"
#define NANO_TO_MS 1000

#define TRUE 1
#define FALSE 0

/* ms to sleep */
unsigned int sleepTime = 10;

struct thread_meta {
	int thread_id;
	char *device;
};


struct opts {
	int read;
	int open;
	int write;
	int time_to_wait_open_was_set;
	int time_to_wait_open;
	int time_to_wait_read_or_write_was_set;
	int time_to_wait_read_or_write;
};

struct opts *options;

int usleep(unsigned int);

void *open_device(void *args) 
{
	
	int fd;
	char buffer[256];

	struct thread_meta *meta = (struct thread_meta *) args;
	printf("T:%d started\n", meta->thread_id);
	
	fd = open(meta->device, O_RDWR);
	if (fd < 0) 
	{
		fprintf(stderr, "T%d: opening Error!\n", meta->thread_id);
		pthread_exit(NULL);
	} else {
		printf("T%d: open success\n", meta->thread_id);
	}

	/* perform read */
	if (read(fd, buffer, 256) == -1) {
		fprintf(stderr, "T:%d read Error!\n", meta->thread_id);
	} else {
		printf("T%d: read success\n", meta->thread_id);
	}

	if (options->time_to_wait_open_was_set)
	{
		usleep(NANO_TO_MS * options->time_to_wait_open);
	}
	
	/* perform write */
	/*if (write(fd, buffer, 256) == -1) {
		fprintf(stderr, "write Error!\n");
	} else {
		printf("Write success. ThreadID: %d\n", meta->thread_id);
	}*/


	if (close(fd) == -1) {
		fprintf(stderr, "T%d: Closing Error!\n", meta->thread_id);
	} else {
		printf("T%d: close success\n", meta->thread_id);
	}

	pthread_exit(NULL);
}

void read_test() {
	int fd;
	char buffer[256];

	fd = open("/dev/myzero", O_RDONLY);

	if (fd < 0) 
	{
		fprintf(stderr, "opening Error!\n");
		
	} else {
		printf("open success");
	}


	/* perform read */
	if (read(fd, buffer, 256) == -1) {
		fprintf(stderr, "read Error!\n");
	} else {
		printf("read success\n");
		printf(buffer);
	}

	if (options->time_to_wait_read_or_write_was_set)
	{
		usleep(NANO_TO_MS * options->time_to_wait_read_or_write);
	}


}

int main(int argc, char *argv[]) 
{

	int i;
	int opt;
	struct thread_meta *thread = NULL;	
	pthread_t *threads;
	pthread_attr_t *attr;
	
	options = malloc (sizeof (struct opts));

	while(-1 != (opt = getopt (argc, argv, "d:oct:e:n:m:hvrw:"))) {
		switch(opt){
			case 'r':
				options->read = TRUE;
				break;
			case 'o':
				printf("%s\n", "case o");
				options->open = TRUE;
				break;
			case 'w':
				options->write = TRUE;
			case 't':
				options->time_to_wait_open_was_set = TRUE;
				options->time_to_wait_open = atoi(optarg);
				break;
			case 'd':
				options->time_to_wait_read_or_write_was_set = TRUE;
				options->time_to_wait_read_or_write = atoi(optarg);
				break;
			
		}
	}
	printf("%s\n", "nach der while");
	if (options->open) 
	{

		printf("%s\n", "options->open TRUE");

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
	}



	if (options->read) 
	{
		read_test();
	}



	return 0;
}
