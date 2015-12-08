#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#define DRIVER_NAME "template"

static struct file_operations fops;


static int __init ModInit(void)
{

	if(register_chrdev(240,DRIVER_NAME,&fops)== 0 ) {
        printk("Heyhey :)");
        return 0; // Treiber erfolgreich angemeldet
    }
    printk("Oh oh :(");
    return -EIO; // Anmeldung beim Kernel fehlgeschlagen
}

static void __exit ModExit(void)
{
    unregister_chrdev(240,DRIVER_NAME);

}

module_init(ModInit);
module_exit(ModExit);

// Metainformation
MODULE_AUTHOR("Timo Weiß und Michael Knoch");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Just a Modul-Template, without specific functionality.");
MODULE_SUPPORTED_DEVICE("none");
