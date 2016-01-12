
#!/bin/sh

DRIVER_NAME=open_once
DRIVER_PATH=/lib/modules/4.2.3/extra

dmesg -c > /dev/null

# zeigt die Informationen Ihres Moduls mit modinfo
modinfo $DRIVER_PATH/$DRIVER_NAME.ko

# lädt das Modul
insmod $DRIVER_PATH/$DRIVER_NAME.ko

# zeigt die entspr. Lade Info des Kernel Logs
dmesg -c

# zeigt die entspr. Infos aus /proc/devices an.
cat /proc/devices

cat /dev/open_once & cat/dev/open_once & cat/dev/open_once


# entlädt das Modul
rmmod $DRIVER_NAME

# zeigt die entspr. Entlade Info des Kernel Logs
dmesg -c