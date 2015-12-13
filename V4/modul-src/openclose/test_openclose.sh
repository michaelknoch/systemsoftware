
#!/bin/sh

DRIVER_NAME = openclose

dmesg -c

# zeigt die Informationen Ihres Moduls mit modinfo
modinfo $DRIVER_NAME.ko

# lädt das Modul
insmod $DRIVER_NAME.ko

# zeigt die entspr. Lade Info des Kernel Logs
dmesg -c

# zeigt die entspr. Infos aus /proc/devices an.
cat /proc/devices

MINOR = `tail -1 /proc/devices`

# entlädt das Modul
rmmod $DRIVER_NAME

# zeigt die entspr. Entlade Info des Kernel Logs
dmesg -c