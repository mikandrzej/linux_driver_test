#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>


/* Meta information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikołaj Andrzejewski");
MODULE_DESCRIPTION("Registers a device nr. and implement some callback functions");


/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("dev_nr - open was called!\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close
};

#define NR_MAJOR 90

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	int retval;
	printk("Hello, Kernel!\n");

	/* Register device nr */
	retval = register_chrdev(NR_MAJOR, "my_dev_nr", &fops);
	if(retval == 0) {
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", NR_MAJOR, 0);
	}
	else if(retval > 0) {
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xFFFFF);
	}
	else {
		printk("Could not register device number!\n");
		unregister_chrdev(NR_MAJOR, "my_dev_nr");
		return -1;
	}
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	unregister_chrdev(NR_MAJOR, "my_dev_nr");
	printk("Goodbye kernel!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
