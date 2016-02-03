// ..
#include <linux/delay.h>
#include <linux/workqueue.h>

static struct workqueue_struct *wq;
static void inc_count(struct work_struct*);
static DECLARE_WORK( work_obj, inc_count);
static DECLARE_COMPLETION(on_exit);

static atomic_t stop_timer = ATOMIC_INIT(0);

static void inc_count(struct work_struct *work)
{
	msleep(2000);

	if (atomic_read(&stop_timer)) {
		complete(&on_exit);
		return;
	} 
	
	if (queue_work(wq, &work_obj)) {
		printk("queue_work SUCCESS\n");
	} else {
		printk("queue_work ERROR\n");
	}
}

static int __init ModInit(void)
{
	// ..

	wq = create_workqueue("DrvrSmpl");
	if(queue_work(wq, &work_obj)) {
		printk( "queue_work successful ...\n");
	} else {
		printk( "queue_work not successful ...\n");
	}
	return 0;

	static void __exit ModExit(void)
	{
		atomic_set(&stop_timer, 1);
		wait_for_completion(&on_exit);
		if( wq ) {
			destroy_workqueue( wq );
			pr_debug("workqueue destroyed\n");
		}

	// ..
	}

// ..
