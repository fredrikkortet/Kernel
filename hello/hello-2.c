// hello-2.c is the same as hello-1.c but instead used macros for init_module() and cleanup_module()
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_2_init(void)
{
    pr_info("hello, world 2\n");
    return 0;
}

static void __exit hello_2_exit(void)
{
    pr_info("Goodbye, world 2\n");

}

module_init(hello_2_init);
module_exit(hello_2_exit);

MODULE_LICENSE("GPL");