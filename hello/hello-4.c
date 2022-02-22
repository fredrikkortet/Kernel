//hello-4.c demonstrates module documentation.

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fredrik kortetjärvi");
MODULE_DESCRIPTION("A simple driver");

static int __init init_hello_4(void)
{
    pr_info("hello World!\n");
    return 0;
}
static void __exit exit_hello_4(void)
{
    pr_info("goodbye!\n");
}
module_init(init_hello_4);
module_exit(exit_hello_4);
