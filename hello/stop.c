//second file
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fredrik");
MODULE_DESCRIPTION("How it work to seperate files 2");

static void __exit exit_stop(void)
{
    pr_info("goodbye from second file");
}

module_exit(exit_stop);