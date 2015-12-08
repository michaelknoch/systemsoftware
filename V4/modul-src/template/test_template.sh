
#!/bin/sh

dmesg -c > /dev/null

modinfo $PROG_NAME.ko
insmod $PROG_NAME.ko

dmesg -c
cat /proc/devices

rmmod $PROG_NAME

dmesg -c