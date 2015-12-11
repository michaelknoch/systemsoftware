#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>

#define DRIVER_NAME "template"

static struct file_operations fops;
static struct cdev *driver_object = NULL;
static dev_t device_number;


static int register_driver( dev_t device_number, int count, char *name, struct file_operations *fops )
{
	if( alloc_chrdev_region( &device_number, 0, count, name ) ) {
		printk("Devicenumber 0x%x not available ...\n", device_number );
		return -1;
	}

	/* get some memory */
	driver_object = cdev_alloc();
	if( driver_object==NULL ) {
		printk("cdev_alloc failed ...\n");
		goto free_device_number;
	}

	kobject_set_name(&driver_object->kobj, name );
	driver_object->owner = THIS_MODULE;
	
	cdev_init( driver_object, fops );
	if( cdev_add( driver_object, device_number, count ) ) {
		printk("cdev_add failed ...\n");
		goto free_cdev;
	}
	return 0;
	
free_cdev:
	kobject_put(&driver_object->kobj);
	driver_object = NULL;
	
free_device_number:
	unregister_chrdev_region( device_number, count );
	return -1;
}

int unregister_driver(dev_t device_number, int count)
{
	if( driver_object )
		cdev_del( driver_object );
	unregister_chrdev_region( device_number, count );
	printk("bye\n");
	return 0;
}


static int __init ModInit(void)
{
	printk("trying to init\n"); 
	if(register_driver(device_number, 1, DRIVER_NAME, &fops) == 0) {
		printk("Oh this was so successful\n");
		return 0;
	}
	return -EIO;
}

static void __exit ModExit(void)
{
	printk("trying to exit\n");

	if( driver_object ) {
		unregister_driver( device_number, 1 );
	}
}

module_init(ModInit);
module_exit(ModExit);

// Metainformation
MODULE_AUTHOR("Timo Weiß und Michael Knoch");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Just a Modul-Template, without specific functionality.");
MODULE_SUPPORTED_DEVICE("none");
