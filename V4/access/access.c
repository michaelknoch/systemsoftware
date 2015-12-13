#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#define THREAD_COUNT 5


struct thread_meta {
	int thread_id;
	char *device_name;
};

void *open_device(void *args) {
	struct thread_meta *meta = (struct thread_meta *) args;
	if (fd = open(meta->device_name, O_RDONLY) < 0) {
		fprintf(stderr, "Opening Error!\n");
	}
}

int main() {

	int i;
	struct thread_meta *thread = NULL;	
	pthread_t *threads;
	pthread_attr_t *attr;
	thread = malloc(THREAD_COUNT * sizeof (struct thread_meta));

	if (thread == NULL) {
		fprintf(stderr, "Allocation Error!\n");
		exit (1);
	}
	
	threads = malloc(THREAD_COUNT * sizeof(pthread_t));
	attr = malloc(THREAD_COUNT * sizeof(pthread_attr_t));

	if (threads == NULL || attr == NULL) {
		fprintf(stderr, "Allocation Error!\n");
        exit (1);
	}


	for (i = 0; i < THREAD_COUNT; i++) {
		thread[i].thread_id = i;

		pthread_create(&threads[i], &attr[i], open_device, (void *) &thread[i]);
	}
	

	/* join threads */ {
	for(i = 0; i < THREAD_COUNT; i++) {
			
			pthread_join(threads[i], NULL);
			
			if (pthread_attr_destroy (&attr[i]) == -1)
			{
				perror ("error in pthread_attr_init");
				exit (1);
			}
		}
	}

	return 0;
}