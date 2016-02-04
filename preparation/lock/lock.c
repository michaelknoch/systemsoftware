// ...
#include <linux/semaphore.h>
#include <linux/delay.h>

// ...

static struct semaphore lock;

static int driver_open(struct inode *geraetedatei, struct file *instanz)
{
	//nonblocking accquire, returns 0 on success
	while (down_trylock(&lock) != 0) {
		//accquire failed
		printk("We are busy, try later\n");
		msleep(200);
	}

	// sleep 3 seconds
	printk("open success\n");
	msleep(3 * 1000);
	up(&lock);
	return 0;
}

static int __init ModInit(void)
{
	// ...

	//init semaphore(mutex weil binärer sempahor)
	sema_init(&lock, 1);

	return 0;
}

// ...
