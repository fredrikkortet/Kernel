// hello-3.c illustating the __init, __initdata and __exit macros
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int hello3_data __initdata = 3;
static int hello2_data __initdata = 2;

static int __init hello_3_init(void)
{
    pr_info("calculating module: %d\n",hello2_data+hello3_data);
    
    return 0;
}

static void __exit hello_3_exit(void)
{
    pr_info("good to see you!\n");

}
module_init(hello_3_init);
module_exit(hello_3_exit);

MODULE_LICENSE("GPL");