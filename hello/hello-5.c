#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fredrik Kortetjärvi");
MODULE_DESCRIPTION("A demonstration of passing command line argumnet.");

static short int myshort =1;
static int myint =420;
static long int mylong =9999;
static char *mystring = "World";
static int myintarray[2]= {420,420};
static int arr_argc =0;

/* module_param(name,type,perm)
* the first argument is parameter name 
* the second  argumnet is its data type
* the last argument is the permisssons bits,
* for exposing paramters in sysfs(if non-zero) at a later stage.
*/
module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "This is a short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "This is a integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "This is a long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "This is a charpointer");

/* module_param_array(name,type,num,perm)
* the first parameter is the name of the parameter
* the second parameter i the type  of the parameter 
* the third parameter is a pointer to the variable that will score the number
* the last argument is permission bits
*/
module_param_array(myintarray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int __init init_hello_5(void)
{
    int i;

    pr_info("Hello world 5 \n============\n");
    pr_info("Myshort is a short integer: %hd\n",myshort);
    pr_info("Myint is a integer: %d\n",myint);
    pr_info("Mylong is a long integer: %ld\n",mylong);
    pr_info("Mystring is a charpointer: %s\n",mystring);

    for (i=0; i < ARRAY_SIZE(myintarray); i++)
    { 
        pr_info("Myintarray[%d] = %d\n", i, myintarray[i]);
    }
    pr_info("got %d argumnet for myintarray.\n",arr_argc);
    return 0;
}
static void __exit exit_hello_5(void)
{
    pr_info("goodbye!\n");
}
module_init(init_hello_5);
module_exit(exit_hello_5);