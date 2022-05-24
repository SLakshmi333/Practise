/*
#undef pr_fmt(fmt) 
#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/time.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <linux/dmaengine.h>
#include <linux/sched.h>
#include<linux/kdev_t.h>


#define MAX_DEV 3
struct mychar_device_data {
    struct cdev cdev;
};

dev_t dev;

static int dev_major = 0;
static struct class *mychardev_class = NULL;
static struct mychar_device_data mychardev_data[MAX_DEV];

static int mychardev_open(struct inode *inode, struct file *file)
{
    pr_info("MYCHARDEV: Device open\n");
    return 0;
}

static int mychardev_release(struct inode *inode, struct file *file)
{
    pr_info("MYCHARDEV: Device close\n");
    return 0;
}

/*static long mychardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    pr_info("MYCHARDEV: Device ioctl\n");
    return 0;
}*/


static ssize_t mychardev_read(struct file *file, char __user *buff, size_t count, loff_t *offset)
{

    pr_info("%s is read from Reading device: %d\n",buff,MINOR(dev));
    return 0;
}

static ssize_t mychardev_write(struct file *file, const char __user *buff, size_t count, loff_t *offset)
{
	printk("Writing to device, %ld num of bytes\n",count);

    return count;
}

static int mychardev_uevent(struct device *dev, struct kobj_uevent_env *env)
{
    add_uevent_var(env, "DEVMODE=%#o", 0666);
    return 0;
}


static const struct file_operations mychardev_fops = {
    .owner      = THIS_MODULE,
    .open       = mychardev_open,
    .release    = mychardev_release,
   // .unlocked_ioctl = mychardev_ioctl,
    .read       = mychardev_read,
    .write       = mychardev_write
};

static int __init mychardev_init(void)
{
    int err, i;
 

    err = alloc_chrdev_region(&dev, 0, MAX_DEV, "mychardev");

    dev_major = MAJOR(dev);

    mychardev_class = class_create(THIS_MODULE, "mychardev");
    mychardev_class->dev_uevent = mychardev_uevent;

    for (i = 0; i < MAX_DEV; i++) {
        cdev_init(&mychardev_data[i].cdev, &mychardev_fops);
        mychardev_data[i].cdev.owner = THIS_MODULE;

        cdev_add(&mychardev_data[i].cdev, MKDEV(dev_major, i), 1);

        device_create(mychardev_class, NULL, MKDEV(dev_major, i), NULL, "mychardev-%d", i);
    }

    pr_info("Successfully registered chardev module\n");
    return 0;
}

static void __exit mychardev_exit(void)
{
    int i;

    for (i = 0; i < MAX_DEV; i++) {
        device_destroy(mychardev_class, MKDEV(dev_major, i));
	cdev_del(&mychardev_data[i].cdev);
    }

    class_unregister(mychardev_class);
    class_destroy(mychardev_class);

    unregister_chrdev_region(MKDEV(dev_major, 0), MINORMASK);
    pr_info("Successfully removed chardev module\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nagalakshmi");

module_init(mychardev_init);
module_exit(mychardev_exit);
