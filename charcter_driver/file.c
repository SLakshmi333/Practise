#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include <asm/uaccess.h> 

int major;
int device_open(struct inode *inode, struct file *file){
	printk(KERN_ALERT "opened from %s\n",__func__);
	return 0;
}
ssize_t device_read(struct file *file, char *buffer, size_t length, loff_t *offset){
printk(KERN_ALERT "read from %s\n",__func__);
	return length;
}
ssize_t device_write(struct file *file, const char *buffer, size_t length, loff_t *offset){
printk(KERN_ALERT "write from %s\n",__func__);
	return length;
}
int device_release(struct inode *inode, struct file *file){
printk(KERN_ALERT "released from %s\n",__func__);
	return 0;
}
struct file_operations fops= {
 .read = device_read,
 .write = device_write,
 .open = device_open,
 .release = device_release
};

static int hello_init(void)
{
printk(KERN_ALERT "hello\n");
major=register_chrdev(0,"simple_chrdev",&fops);
printk("%d",major);
return 0;
}

static void hello_exit(void){
printk(KERN_ALERT "exit\n");
unregister_chrdev(major,"simple_chrdev");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Nagalakshmi\n");
MODULE_DESCRIPTION("character driver practise\n");
MODULE_LICENSE("GPL\n");



