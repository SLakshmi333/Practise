#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define buf_len 50
static char *message_ptr;
static char message[buf_len];
int major;

#define DEVICE_NAME "Example_chardevice1"

int device_open(struct inode *pinode, struct file *pfile){
	printk("function called from %s\n",__func__);
	message_ptr="message";	
	return 0;
}

ssize_t device_read(struct file *pfile, char __user *buff, size_t length , loff_t *offset){
	printk("function called from %s\n",__func__);
	int bytes_read=0;
	if(*message_ptr==0)
		return 0;
	while(length && *message_ptr){
		put_user(*(message_ptr++),buff++);
		length--;
		bytes_read++;
	}
	return bytes_read;
}

ssize_t device_write(struct file *pfile, const char __user *buff, size_t length, loff_t *offset){
	printk("function called from %s\n",__func__);
	int i;
	for(i=0;i<length&&i<buf_len;i++)
		get_user(message[i],buff++);
	message_ptr="message"; 
	return i;
}
int device_release(struct inode *pnode , struct file *pfile){	
	printk("function called from %s\n ",__func__);
	return 0;
}

struct file_operations fops={
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int helloinit(void){
	printk("hello world %s\n" ,__func__);
	major=register_chrdev(0,"Example_chardevice1", &fops);
	printk("Major Number: %d\n",major);
	return 0;
}

static void helloexit(void){
	printk("good bye %s\n" ,__func__);
	unregister_chrdev(major,"Example_chardevice1");
}

module_init(helloinit);
module_exit(helloexit);

MODULE_AUTHOR("Nagalakshmi\n");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Example program.");


