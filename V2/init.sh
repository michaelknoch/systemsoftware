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

mount -t devpts devpts /dev/pts
mdev -s


/bin/chown root.root /bin/busybox
/bin/chmod 4755 /bin/busybox

# Set loglevel to "Emergency messages, system is about to crash or is unstable"
echo 0 > /proc/sys/kernel/printk

ls /etc
ls /etc/udhcp
ls /bin
ls /usr/share/udhcpc

udhcpc -i eth0 -s /etc/udhcp/sample.script

#feuer frei
./bin/sysinfo

## shell feuern
echo 'asd'
ifconfig
echo 'asd2'
#setsid cttyhack sh

exec sh
