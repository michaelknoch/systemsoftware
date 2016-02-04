# Headers

### linux/init.h


* **module_init**(name);
	* Wenn Modul als built-in Treiber Compiler wird, wird die init fn beim booten aufgerufen.
* **module_exit**(name);

### linux/module.h

* **MODULE_LICENSE**(lizenz);
* **MODULE_PARM_DESC**(var, desc);
	* ordnet `var` eine Beschreibung `desc` für modinfo 

### asm/uaccess.h

* unsigned long **copy_from_user**(void *to, const void *from, unsigned long bytes_to_copy);
	* returns #Zeichen, die nicht kopiert wurden.  
* unsigned long **copy_to_user**(void *to, const void *from, unsigned long bytes_to_copy);
	* returns #Zeichen, die nicht kopiert wurden.
* int **get_user**(variable, source);
	* fn liest von Adresse `source` zu variable
	* 1, 2, 4 oder 8 Byte
	* source wird verifiziert
* int **put_user**(datum, destination);
	* fn schreibt datum zu destination
	* 1, 2, 4 oder 8 Byte
* int **__get_user**(variable, source);
	* fn liest von Adresse `source` zu variable
	* wie get_user nur ohne Verifikation
* int **__put_user**(datum, destination);
	* wie put_user nur ohne Verifikation
	

### <linux/timer.h>

```
struct timer_list {
    ...
    unsigned long expires;
    unsigned long data;
    void (*function)(unsigned long);
};
```

* void **init_timer**(struct timer_list *timer);
	* muss vor add_timer aufgerufen werden
* void **add_timer**(struct timer_list *timer); 
* int **del_timer**(struct timer_list *timer);
	* lieber del_timer_sync verwenden
* int **del_timer_sync**(struct timer_list *timer);
	* returns 1 wenn timer aktiv war, ansonsten 0
	* nicht im Interrupt-Kontext aufrufen!
* **mod_timer**(struct timer_list *timer, unsigned long expires);
	* um `expires` up-zu-daten

### asm/signal.h

* **SA_INTERRUPT**
	* Interrupt gesperrt 
* **SA_SHIRQ**
	* Interrupt kann von mehreren Treibern genutzt werden (geshared)
* **SA_SAMPLE_RANDOM**
	* Ist dieses Bit gesetzt, wird der Auftrittszeitpunkt des Interrupts zur Erzeugung von Zufallszahlen herangezogen.
	
### asm/semaphore.h

Mutexe und Semaphore stehen nur im Prozess- oder User-Kontext zur Verfügung.

* void **sema_init**(struct semaphore *sema, int val);
* void **up**(struct semaphore *sem);
	* Aufrufen beim Verlassen
* void **DECLARE_MUTEX**(name);
* void **DECLARE_MUTEX_LOCKED**(name);
	* locked den Mutex sofort

### linux/interrupt.h

* request_irq
* free_irq
* tasklet_disable
* tasklet_enable
* tasklet_hi_schedule
* tasklet_init
* tasklet_kill
* tasklet_schedule
* probe_irq_on
* probe_irq_off
* DECLARE_TASKLET
* DECLARE_TASKLET_DISABLED
