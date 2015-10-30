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


#feuer frei
./bin/sysinfo


setsid sh