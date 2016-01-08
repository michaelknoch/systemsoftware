#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/completion.h>
#include <linux/sched.h>
#include <linux/kthread.h>


#define DRIVER_NAME "kthread"
#define MINORS_COUNT 1

static struct file_operations fops = {
    .owner=THIS_MODULE,
};

static struct cdev *driver_object;
static dev_t device_number;
struct class *template_class;

static struct task_struct* thread_id;
static wait_queue_head_t wq;
static DECLARE_COMPLETION(on_exit);


static int thread_code( void *data )
{
    unsigned long timeout;
    int i;

    allow_signal( SIGTERM ); 
    for( i=0; i<10; i++ ) {
        timeout=HZ; // wait 1 second
        timeout=wait_event_interruptible_timeout(
            wq, (timeout==0), timeout);
        printk("thread_code: woke up ...\n");
        if( timeout==-ERESTARTSYS ) {
            printk("got signal, break\n");
            break;
        }
    }
    thread_id = 0;
    complete_and_exit( &on_exit, 0 );
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

	init_waitqueue_head(&wq);
    thread_id=kthread_create(thread_code, NULL, "MyKThread");
    if( thread_id==0 ) {
        return -EIO;
    }
    wake_up_process(thread_id);

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
	if(thread_id){
		kill_pid(task_pid(thread_id), SIGTERM, 1);
	}
	
	wait_for_completion(&on_exit);

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
