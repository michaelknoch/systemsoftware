// ...
#include <asm/uaccess.h>

// ...

static ssize_t driver_write(struct file *instanz, const char *user, size_t count, loff_t *offset) {
	char buffer[count];
	unsigned long notcopied;
	size_t to_copy;

	to_copy =  count;
	
	// unsigned long copy_from_user (void * to, const void __user * from, unsigned long n);
	notcopied = copy_from_user(buffer, user, to_copy);
	return to_copy - notcopied;
}

static ssize_t driver_read(struct file *instanz, char *user, size_t count, loff_t *offset) {
	char *helloworld = "hello world\n";
	unsigned long notcopied;
	size_t to_copy;

	to_copy =  min(strlen(minorone), count);
	
	// unsigned long copy_to_user(void __user * to, const void * from, unsigned long n);
	notcopied = copy_to_user(user, helloworld, to_copy);
	return to_copy - notcopied;
}

// ...
