
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

# get newest major
#http://stackoverflow.com/questions/4651437/how-to-set-a-bash-variable-equal-to-the-output-from-a-command
#http://stackoverflow.com/questions/4168371/how-can-i-remove-all-text-after-a-character-in-bash
major=`tail -1 /proc/devices | cut -f1 -d" "`

#create device with minor 1
mknod -m 622 /dev/openclose1 c $major 1

/usr/bin/access

# entlädt das Modul
rmmod $DRIVER_NAME

# zeigt die entspr. Entlade Info des Kernel Logs
dmesg -c