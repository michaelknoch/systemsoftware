#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
MODULE_LICENSE("GPL");

static int __init driver_init(void){
	printk ("Wup...\n");
	return 0;
}
static void __exit driver_exit(void){
	printk ("Wup...\n");
}

module_init(driver_init);
module_exit(driver_exit);
