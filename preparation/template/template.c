#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>

#define DRIVER_NAME "template"
#define MINORS_COUNT 1

static struct file_operations fops = {
    .owner=THIS_MODULE,
};

static struct cdev *driver_object;
static dev_t device_number;
static struct class *template_class;


// starting point (insmod)
static int __init ModInit(void)
{
	int major;

	/* 	alloc_chrdev_region
		Die Gerätenummer wird mit den ZUgriffsfunmtionen des Treibers verknüpft
		Arguments:	dev: 		output parameter for first assigned number
					baseminor: 	first of the requested range of minor numbers
					count: 		the number of minor numbers required
					name: 		the name of the associated device or driver
		Description: 	Allocates a range of char device numbers. 
						The major number will be chosen dynamically, 
						and returned (along with the first minor number) in dev. 
						returns zero or a negative error code.

	*/
	if( alloc_chrdev_region( &device_number, 0, MINORS_COUNT, DRIVER_NAME ) < 0) {
		printk("Devicenumber 0x%x not available ...\n", device_number );
		return -EIO;
	}

	/* get some memory for cdev driver structure */
	driver_object = cdev_alloc();
	if( driver_object==NULL ) {
		printk("cdev_alloc failed ...\n");
		goto free_device_number;
	}

	driver_object->ops = &fops;
	driver_object->owner = THIS_MODULE;

	/* Anmeldung beim Kernel */
	if( cdev_add( driver_object, device_number, MINORS_COUNT )) {
		printk("cdev_add failed ...\n");
		goto free_cdev;
	}

	/* Eintrag im Sysfs*/
	template_class = class_create(THIS_MODULE, DRIVER_NAME);
	/* Erzeugung der Gerätedatei mittels sysfs eintrag */
	device_create(template_class, NULL, device_number, NULL, "%s", DRIVER_NAME);

	major = MAJOR(device_number);
	printk("Major number: %d\n", major);

	return 0;
	
free_cdev:
	kobject_put(&driver_object->kobj);
	driver_object = NULL;
	
free_device_number:
	unregister_chrdev_region( device_number, MINORS_COUNT );
	return -EIO;
}

// ending point (rmmod)
static void __exit ModExit(void)
{

	device_destroy(template_class, device_number);
	class_destroy(template_class);

	printk("trying to unregister 0x%x\n", device_number);
	
	cdev_del( driver_object );
	unregister_chrdev_region( device_number, 1 );
	
	printk("exiting\n");
	
}

// starting and ending points for insmod and rmmod
module_init(ModInit);
module_exit(ModExit);

// meta
MODULE_AUTHOR("Timo Weiß und Michael Knoch");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Just a Modul-Template, without specific functionality.");
MODULE_SUPPORTED_DEVICE("none");
