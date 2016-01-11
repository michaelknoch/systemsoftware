#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/kfifo.h>

#define DRIVER_NAME "buf"
#define MINORS_COUNT 1


#define VIERUNDSECHZIG 32

/*
	Lots of the following code is borrowed from:
	http://lxr.free-electrons.com/source/samples/kfifo/bytestream-example.c
*/

static int driver_open(struct inode *geraetedatei, struct file *instanz); 
static int driver_release(struct inode *geraetedatei, struct file *instanz); 
static ssize_t driver_read(struct file *instanz, char *user, size_t count, loff_t *offset);
static ssize_t driver_write(struct file *instanz, const char *user, size_t count, loff_t *offset);


static wait_queue_head_t waitQueueRead;
static wait_queue_head_t waitQueueWrite;

static struct file_operations fops = {
	
    .owner= THIS_MODULE,
    .open = driver_open,
    .release = driver_release,
    .read = driver_read,
    .write = driver_write,
};

static struct cdev *driver_object;
static dev_t device_number;
struct class *template_class;


static DEFINE_MUTEX(read_lock);
static DEFINE_MUTEX(write_lock);

static DEFINE_KFIFO(fifo, unsigned char, VIERUNDSECHZIG);



static int driver_open(struct inode *geraetedatei, struct file *instanz) {
	return 0;
}

static int driver_release(struct inode *geraetedatei, struct file *instanz) {
	return 0;
}

static ssize_t driver_read(struct file *instanz, char *user, size_t count, loff_t *offset) 
{	
	int ret;
	unsigned int copied;
	printk("driver read start\n");

	if(wait_event_interruptible(waitQueueRead, !kfifo_is_empty(&fifo))) {
		printk("ERESTARTSYS");	
		return -ERESTARTSYS;
	}

	ret = kfifo_to_user(&fifo, user, count, &copied);
	printk("kfifotouser\n");	

	wake_up_interruptible(&waitQueueWrite);

	printk("driver read end\n");	
	return ret ? ret : copied;

}
static ssize_t driver_write(struct file *instanz, const char *user, size_t count, loff_t *offset)
{


	int ret;
	unsigned int copied;
 	
 	if(wait_event_interruptible(waitQueueWrite, kfifo_is_empty(&fifo))) {
		return -ERESTARTSYS;
	}

	ret = kfifo_from_user(&fifo, user, count, &copied);
	wake_up_interruptible(&waitQueueRead);

	return ret ? ret : copied;
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

	init_waitqueue_head(&waitQueueRead);
	init_waitqueue_head(&waitQueueWrite);


	
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
