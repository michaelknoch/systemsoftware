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
	

### linux/timer.h

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
	
### linux/rwsem.h

Wenn man nur schreibenden Zugriff schützen will (lesen immer erlaubt), kann ein read/write semaphore verwendet werden:

* void **init_rwsem**(struct rw_semaphore *rwsema);
* void **down_read**(struct rw_semaphore *rwsema);
	* beim betreten zum lesen (kein lock)
* void **down_write**(struct rw_semaphore *rwsema);
	* beim betreten zum schreiben (lock) 
* void **up_read**(struct rw_semaphore *sem);
* void **up_write**(struct rw_semaphore *sem); 
* int **down_read_trylock**(struct rw_semaphore *rw_sema);
	* return 1 bei Erfolg, sonst 0
* int **down_write_trylock**(struct rw_semaphore *sem);  

### asm/atomic.h

* atomic_t index = ATOMIC_INIT(0);
* int **atomic_read**(atomic_t *v);
* void **atomic_set**(atomic_t *v, int i);
* void **atomic_add**(int i, atomic_t *v);
* void **atomic_sub**(int i, atomic_t *v);
* void **atomic_inc**(atomic_t *v);
* void **atomic_dec**(atomic_t *v);
* int **atomic_inc_and_test**(atomic_t *v);
* void **atomic_dec_and_test**(atomic_t *v);
	* return 1 wenn v nach inc/dec 0 ist, ansonsten 0
* int **atomic_add_negative**(int i, atomic_t *v);
	* return 1 wenn v nach add i >= 0 ist, ansonsten 0 (v noch negativ)
* int **atomic_add_and_test**(int i, atomic_t *v);
* int **atomic_sub_and_test**(int i, atomic_t *v);


### asm/spinlock.h 
Schutz eines „kurzen“ kritischen
Abschnitts, aktives warten, im Prozess & Interruptkontext einsetzbar, Theoretisch nur auf Mehrprozessor, praktisch auch auf Einprozessormaschinen  

* static **spinlock_t** lock = **SPIN_LOCK_UNLOCKED**;
* static **rwlock_t** rwlock = **RW_LOCK_UNLOCKED**;
* **spin_lock_init**(spinlock_t *lock);
* Rettet den Zustand des Interruptflags (in iflags), sperrt Interrupts auf dem lokalen Prozessor (auch Softirqs), bei restore wird das Flag-Register mit dem Wert »iflags« restauriert  
  	* void **spin_lock_irqsave**(spinlock_t *lock, unsigned long iflags);  
  	* void **spin_unlock_irqrestore**(spinlock_t *lock, unsigned long iflags);
* Einsatz wenn der Zustand des Interruptflags genau bekannt ist, sperrt die Abarbeitung von Interrupts, auch Softirqs. Die Interrupt-Flags werden nicht gesichert  
  	* void **spin_lock_irq**(spinlock_t *lock);  
  	* void **spin_unlock_irq**(spinlock_t *lock);
* Lässt Hardwareinterrupts zu, sperrt aber Softirqs
	* void **spin_lock_bh**(spinlock_t *lock);
	* void **spin_unlock_bh**(spinlock_t *lock);
* Nur im Prozess-Kontext (Treiberinstanzen, Kernel-Threads, Workqueues, Event-Workqueue)
	*  void **spin_lock**(spinlock_t *lock);  
	*  void **spin_unlock**(spinlock_t *lock);
* Für rw locks read/write prefix anstatt spin Bsp:  
	* void **read_lock_irq**(rwlock_t *lock);
	* void **write_lock_irq**(rwlock_t *lock);  
	
![Spinlock table](https://ezs.kr.hsnr.de//TreiberBuch/html/mutextable.png)



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
