
#!/bin/sh
# producer

DRIVER_NAME=buf
TEXT = "hallo michael du supertutor"

sleep 3
echo $TEXT > /dev/buf
sleep 3
echo $TEXT > /dev/buf
sleep 3
echo $TEXT > /dev/buf
sleep 3
echo $TEXT > /dev/buf