


#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DRIVER_NAME "openclose"
#define MINORS_COUNT 2
#define PROCESS_COUNT 1


static int driver_open(struct inode *geraetedatei, struct file *instanz); 
static int driver_release(struct inode *geraetedatei, struct file *instanz); 

static ssize_t driver_read(struct file *instanz, char *user, size_t count, loff_t *offset);
static ssize_t driver_write(struct file *instanz, const char *user, size_t count, loff_t *offset);

static struct file_operations fops = {
	.read = driver_read,
	.write = driver_write,
    .owner=THIS_MODULE,
    .open = driver_open,
    .release = driver_release,
};

/* makelinux.net/ldd3/chp-5-sect-7 */
static atomic_t lock = ATOMIC_INIT(PROCESS_COUNT);

static struct cdev *driver_object;
static dev_t device_number;
struct class *template_class;


static ssize_t driver_read(struct file *instanz, char *user, size_t count, loff_t *offset) 
{
	printk("read\n");
	return 0;
}

static ssize_t driver_write(struct file *instanz, const char *user, size_t count, loff_t *offset) 
{
	printk("write\n");
	return 0;
}


static int driver_open(struct inode *geraetedatei, struct file *instanz) 
{
	printk("Open Driver..\n");

	if (iminor(geraetedatei) == 0) {
		printk("open from Minor: 0\n");
	} else {

		if (!atomic_dec_and_test(&lock)) {
			atomic_inc(&lock);
			printk("Driver busy!\n");
			return -EBUSY;
		}

		printk("open from Minor: 1\n");
	}

	return 0;
}

static int driver_release(struct inode *geraetedatei, struct file *instanz) 
{
	printk("Release Driver..\n");
	if (iminor(geraetedatei) == 0) {
		printk("release from Minor: 0\n");
	} else {
		atomic_inc(&lock);
		printk("release from Minor: 1\n");
	}

	return 0;
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
