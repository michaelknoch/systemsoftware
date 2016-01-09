
#!/bin/sh

DRIVER_NAME=kthread
DRIVER_PATH=/lib/modules/4.2.3/extra

dmesg -c > /dev/null

# zeigt die Informationen Ihres Moduls mit modinfo
modinfo $DRIVER_PATH/$DRIVER_NAME.ko

# lädt das Modul
insmod $DRIVER_PATH/$DRIVER_NAME.ko

# zeigt die entspr. Lade Info des Kernel Logs
echo "sleeping for 10 sec..."
sleep 10
dmesg -c

# zeigt die entspr. Infos aus /proc/devices an.
cat /proc/devices


# entlädt das Modul
rmmod $DRIVER_NAME

# zeigt die entspr. Entlade Info des Kernel Logs
dmesg -c