// ...
#include <linux/completion.h>
#include <linux/sched.h>
#include <linux/kthread.h>

// ...

static struct task_struct* thread_id;
static wait_queue_head_t wq;
static DECLARE_COMPLETION(on_exit);

static int thread_code( void *data ) {
    unsigned long timeout;

    allow_signal(SIGTERM); 
    while(!signal_pending(current)) {
        timeout= 2 * HZ;
        timeout=wait_event_interruptible_timeout(
            wq, (timeout==0), timeout);
        printk("thread_code: woke up after 2 secs ...\n");
        if(timeout==-ERESTARTSYS) {
            printk("got signal, break\n");
            break;
        }
    }
    thread_id = 0;
    complete_and_exit(&on_exit, 0);
}

static int __init ModInit(void) {
	// ...

	init_waitqueue_head(&wq);
    thread_id=kthread_create(thread_code, NULL, "MyKThread");
    if(thread_id==0) {
        return -EIO;
    }
    wake_up_process(thread_id);
	return 0;
}

static void __exit ModExit(void) {
	if(thread_id){
		kill_pid(task_pid(thread_id), SIGTERM, 1);
	}
	
	wait_for_completion(&on_exit);

	// ...	
}

// ...
