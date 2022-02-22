// chardev.c: count how many times you have read from dev file.

#include "asm-generic/errno-base.h"
#include "asm/uaccess.h"
#include "linux/export.h"
#include "linux/types.h"
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char __user *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev" // Name for the dev in /proc/device
#define BUF_LEN 80 // Max length of the message

static int major; // The major number to assign to the dev

enum {
    CDEV_NOT_USED = 0,
    CDEV_EXCLUSIVE_OPEN = 1,
};


static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED); // Prevent multi usage of the file with check if open already

static char msg[BUF_LEN];

static struct class *cls;

static struct file_operations chardev_fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};
// Init driver function
static int __init chardev_init(void)
{   
    major = register_chrdev(0, DEVICE_NAME, &chardev_fops);
    //check if major is set or not
    if (major < 0) {
        pr_alert("Registering char device failed with %d\n", major);
        return major;
    }

    pr_info("Is was assigned major number %/d\n",major);

    cls = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

    pr_info("Device created on /dev/%s\n", DEVICE_NAME);
    
    return SUCCESS;
}
//exit driver function
static void __exit chardev_exit(void)
{   
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
    // Unregister the device 
    unregister_chrdev(major, DEVICE_NAME);
}

//Methods
// This function calls when the driver file tries to open.
static int device_open(struct inode *inode, struct file *file)
{
    static int counter = 0;

    // check if open already
    if (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN))
        return -EBUSY;
    
    sprintf(msg, "I already told you %d times Hello world!\n", counter++);
    try_module_get(THIS_MODULE);

    return SUCCESS;
}
// When the file closes is this function called 
static int device_release(struct inode *inode, struct file *file)
{
    //set the File to be avalibale 
    atomic_set(&already_open, CDEV_NOT_USED);
    
    module_put(THIS_MODULE);

    return SUCCESS;
}
// This function calls when a file is open and wants to read from it 
static ssize_t device_read(struct file *flip, char __user *buffer, size_t length, loff_t *offset)
{   //bytes written
    int bytes_read = 0;

    const char *msg_ptr =msg;

    if (!*(msg_ptr + *offset)) { // end of the message 
        *offset = 0; //set offset to the beginning
        return 0; // say  its over
    }

    msg_ptr += *offset; // increment offset

    while (length && *msg_ptr) {
        put_user(*(msg_ptr++), buffer++);
        length++;
        bytes_read++;
    }

    *offset += bytes_read;
    return bytes_read;
}
// calls when trying to write to the file
static ssize_t device_write(struct file *flip, const char __user *buffer, size_t length, loff_t *offset)
{
    pr_alert("Sorry, this operation is not supported.\n");
    return -EINVAL;
}
module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");

