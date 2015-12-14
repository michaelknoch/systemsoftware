
#!/bin/sh

DRIVER_NAME=myzero
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
./access -r -d 500

# get newest major
#http://stackoverflow.com/questions/4651437/how-to-set-a-bash-variable-equal-to-the-output-from-a-command
#http://stackoverflow.com/questions/4168371/how-can-i-remove-all-text-after-a-character-in-bash
major=`tail -1 /proc/devices | cut -f1 -d" "`

#create device with minor 1
echo mknod -m 622 /dev/myzerominor c $major 1
mknod -m 622 /dev/myzerominor c $major 1

# zeigt die entspr. Entlade Info des Kernel Logs
dmesg -c