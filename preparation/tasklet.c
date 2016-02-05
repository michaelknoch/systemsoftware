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
    
    /*  übergibt tasklet_struct zur Abarbeitung an den Kernel
        Wird NICHT direkt nach ISR gefeuert, erst kommen dran:
        1. HI_SOFTIRQ
        2. TIMER_SOFTIRQ
        3. NET_TX_SOFTIRQ
        4. NET_RX_SOFTIRQ
        5. SCSI_SOFTIRQ
        6. >> TASKLET_SOFTIRQ <<
        Um direkt nach ISR ausgeführt zu werden muss tasklet_hi_schedule(&tasklet_struct) verwendet werden
    */
    tasklet_schedule(&tasklet_struct);

    /*  Alternative für mehr prio
        auch nach ISR, aber vor niederprioren tasklets
        tasklet_hi_schedule(&tasklet_struct); */
    return 0;
}

static void __exit ModExit(void)
{
    tasklet_kill(&tasklet_struct);
    
    //...   
}
