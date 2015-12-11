
#!/bin/sh

dmesg -c

# zeigt die Informationen Ihres Moduls mit modinfo
modinfo $PROG_NAME.ko

# lädt das Modul
insmod $PROG_NAME.ko

# zeigt die entspr. Lade Info des Kernel Logs
dmesg -c

# zeigt die entspr. Infos aus /proc/devices an.
cat /proc/devices

# entlädt das Modul
rmmod $PROG_NAME

# zeigt die entspr. Entlade Info des Kernel Logs
dmesg -c