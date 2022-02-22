#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fredrik Kortetjärvi");
MODULE_DESCRIPTION("How it work to seperate files");

static int __init init_start(void)
{
    pr_info("Hello world");
    return 0;
}

module_init(init_start);