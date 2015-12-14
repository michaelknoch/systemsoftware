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

#mount -t devpts devpts /dev/pts


/bin/chown 0.0 /bin/busybox
/bin/chmod 4755 /bin/busybox


#Registrieren Sie z.B. mdev als Hotplug-Manager
echo "/sbin/mdev" > /proc/sys/kernel/hotplug

mdev -s

# Set loglevel to "Emergency messages, system is about to crash or is unstable"
#echo 0 > /proc/sys/kernel/printk

#chmod 777 /etc/udhcp/simple.script
#ls -la /etc/udhcp/simple.script
#whoami
sleep 2
udhcpc -i eth0 -s /etc/udhcp/simple.script

#/etc/init.d/S50dropbear start

#feuer frei
./bin/sysinfo

## shell feuern
#echo 'asd'
#ifconfig
#echo 'asd2'

#telnetd 192.168.26.48 -l /bin/sh

#setsid cttyhack /bin/busybox sh


