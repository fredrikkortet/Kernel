#obj-m += hello-1.o
#obj-m += hello-2.o
#obj-m += hello-3.o
#obj-m += hello-4.o
#obj-m += hello-5.o
#obj-m += startstop.o
#startstop-m := start.o stop.o
obj-m += chardev.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
check:
	sudo insmod chardev.ko
distcheck:
	sudo rmmod chardev
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
