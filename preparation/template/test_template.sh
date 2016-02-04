
#!/bin/sh

DRIVER_NAME=template
DRIVER_PATH=/usr/bin

# clear dmesg
dmesg -c > /dev/null

# zeigt die Informationen Ihres Moduls mit modinfo
modinfo $DRIVER_PATH/$DRIVER_NAME.ko

# lädt das Modul
insmod $DRIVER_PATH/$DRIVER_NAME.ko

# zeigt die entspr. Lade Info des Kernel Logs
dmesg -c

# zeigt die entspr. Infos aus /proc/devices an.
cat /proc/devices

# create device
mknod -m 622 /dev/myzerominor c 243 0
# (gerätepfad / characterdevice / major (steht in proc/devices) / minor)
# entfällt bei aktivierung von udev

# entlädt das Modul
rmmod $DRIVER_NAME

# zeigt die entspr. Entlade Info des Kernel Logs
dmesg -c