#!/bin/busybox sh
/bin/busybox --install -s /bin/


echo '!!!!!!!'
echo 'wuhoooo'
echo 'wuhoooo'
echo 'wuhoooo'
echo 'wuhoooo'
echo 'wuhoooo'
echo '!!!!!!!'


## mount (-t = target)
## type device dir
mount -t tmpfs none /tmp
mount -t sysfs none /sys
mount -t proc proc /proc

mdev -s


# Set loglevel to "Emergency messages, system is about to crash or is unstable"
echo 0 > /proc/sys/kernel/printk

#feuer frei
./bin/sysinfo

## shell feuern
setsid sh
