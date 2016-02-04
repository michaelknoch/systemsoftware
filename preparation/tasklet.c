//...
#include <linux/interrupt.h>

static void tasklet_func(unsigned long data) {
	printk("Ich bin ein winzigkleines Taslet...\n");
}

// 0L = Unsigned Long Data
DECLARE_TASKLET(tasklet_struct, tasklet_func, 0L);

static int __init ModInit(void)
{
	//...
	
	/* 	übergibt tasklet_struct zur Abarbeitung an den Kernel
		Wird direkt nach ISR gefeuert (sofern keine anderen Tasklets warten) */
	tasklet_schedule(&tasklet_struct);

	/* 	Alternative für mehr prio
		auch nach ISR, aber vor niederprioren tasklets
		tasklet_hi_schedule(&tasklet_struct); */
	return 0;
}

static void __exit ModExit(void)
{
	tasklet_kill(&tasklet_struct);
	
	//...	
}
