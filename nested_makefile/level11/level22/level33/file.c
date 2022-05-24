#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int hello_init(void)
{
printk(KERN_ALERT "hello\n");
return 0;
}

static void hello_exit(void){
printk(KERN_ALERT "exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("NAGALAKSHMI\n");
MODULE_DESCRIPTION("NESTED FILE\n");
MODULE_LICENSE("GPL");

