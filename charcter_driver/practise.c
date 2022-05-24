#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

int major;
char ptr;
#define DEVICE_NAME "Example_chardevice"

int device_open(struct inode *pinode, struct file *pfile){
	printk("function called from %s\n",__func__);
	return 0;
}

ssize_t device_read(struct file *pfile, char __user *buff, size_t length , loff_t *offset){
	printk("function called from %s\n",__func__);
	if(put_user(ptr,buff) !=0){
		printk("copying failed\n");
		return -1;
	}
	else
	{
		printk("copying to user sucess with %s\n",buff);
	}
	return 0;
}

ssize_t device_write(struct file *pfile, const char __user *buff, size_t length, loff_t *offset){
	printk("function called from %s\n",__func__);
	/*  ptr=kzalloc(length,GFP_KERNEL);
	    if(ptr==NULL){
	    printk("memory not allocated\n");
	    }
	    else
	    {
	    printk("memory allocated\n");
	    */	if(get_user(ptr,buff) !=0){
		    printk("copied failure\n");
		    return -1;
	    }
	    else{
		    printk("copying from user is success with %s\n", ptr);
	    }
	    return length;
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
	major=register_chrdev(0,"Example_chardevice", &fops);
	printk("Major Number: %d\n",major);
	return 0;
}

static void helloexit(void){
	printk("good bye %s\n" ,__func__);
	unregister_chrdev(major,"Example_chardevice");
}

module_init(helloinit);
module_exit(helloexit);

MODULE_AUTHOR("Nagalakshmi\n");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Example program.");


