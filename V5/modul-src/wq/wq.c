#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/timer.h>
#include <linux/delay.h>


#include <linux/workqueue.h>

#define DRIVER_NAME "wq"
#define MINORS_COUNT 1

static struct timer_list mytimer;

static struct file_operations fops = {
    .owner=THIS_MODULE,
};

static struct cdev *driver_object;
static dev_t device_number;
struct class *template_class;

static unsigned int min, max, curr, prev = 0;

static struct workqueue_struct *wq;
static void inc_count(struct work_struct*);
static DECLARE_WORK( work_obj, inc_count);
static DECLARE_COMPLETION(on_exit);

static atomic_t stop_timer = ATOMIC_INIT(0);

static void inc_count(struct work_struct *work)
{
    curr = jiffies - prev;

    // if there was a prev iteration
    if(prev) {

        // use current as max if its creater than max
        max = curr > max ? curr : max;

        // use current as min if its smaller than min
        min = curr < min ? curr : min;

    }
    

    prev = jiffies;

     printk("inc_count called (%ld)... \ncurrent: %d\nmin: %d\nmax: %d\n",
			mytimer.expires, curr, min, max );

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
	int major;

	if( alloc_chrdev_region( &device_number, 0, MINORS_COUNT, DRIVER_NAME ) < 0) {
		printk("Devicenumber 0x%x not available ...\n", device_number );
		return -1;
	}

	/* get some memory */
	driver_object = cdev_alloc();
	if( driver_object==NULL ) {
		printk("cdev_alloc failed ...\n");
		goto free_device_number;
	}

	driver_object->ops = &fops;
	driver_object->owner = THIS_MODULE;


	if( cdev_add( driver_object, device_number, MINORS_COUNT )) {
		printk("cdev_add failed ...\n");
		goto free_cdev;
	} else {
		printk("cdev add success\n");
	}

	template_class = class_create(THIS_MODULE, DRIVER_NAME);
	device_create(template_class, NULL, device_number, NULL, "%s", DRIVER_NAME);

	major = MAJOR(device_number);
	printk("Major number: %d\n", major);

	wq = create_workqueue("DrvrSmpl");

	if(queue_work(wq, &work_obj)) {
        printk( "queue_work successful ...\n");
    } else {
        printk( "queue_work not successful ...\n");
    }


	return 0;

free_cdev:
	kobject_put(&driver_object->kobj);
	driver_object = NULL;

free_device_number:
	unregister_chrdev_region( device_number, 1 );
	return -1;
}

static void __exit ModExit(void)
{

	atomic_set(&stop_timer, 1);
	wait_for_completion(&on_exit);
	if( wq ) {
        destroy_workqueue( wq );
        pr_debug("workqueue destroyed\n");
    }

	device_destroy(template_class, device_number);
	class_destroy(template_class);

	printk("trying to unregister 0x%x\n", device_number);

	cdev_del( driver_object );
	unregister_chrdev_region( device_number, 1 );
	
	
	
	printk("exiting\n");

}

module_init(ModInit);
module_exit(ModExit);

// Metainformation
MODULE_AUTHOR("Timo Weiß und Michael Knoch");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Just a Modul-Template, without specific functionality.");
MODULE_SUPPORTED_DEVICE("none");
