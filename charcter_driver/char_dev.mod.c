#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x7aea56e7, "module_layout" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x71edadd6, "class_destroy" },
	{ 0x5869fe34, "class_unregister" },
	{ 0x7ba0a4b9, "cdev_del" },
	{ 0x6ca8103b, "device_destroy" },
	{ 0x80b5e90f, "device_create" },
	{ 0xcfc1fb2, "cdev_add" },
	{ 0x4aa1a2ff, "cdev_init" },
	{ 0x7f3d98e4, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x9c6febfc, "add_uevent_var" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "F5226C7ED1CC54025A2A8D6");
