
#!/bin/sh

DRIVER_NAME=mynull
DRIVER_PATH=/lib/modules/4.2.3/extra

dmesg -c

# zeigt die Informationen Ihres Moduls mit modinfo
modinfo $DRIVER_PATH/$DRIVER_NAME.ko

# lädt das Modul
insmod $DRIVER_PATH/$DRIVER_NAME.ko

# zeigt die entspr. Lade Info des Kernel Logs
dmesg -c

# zeigt die entspr. Infos aus /proc/devices an.
cat /proc/devices

# run access
./usr/bin/access -w -d 500

# entlädt das Modul
rmmod $DRIVER_NAME

# zeigt die entspr. Entlade Info des Kernel Logs
dmesg -c