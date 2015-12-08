
export ARCH=arm
export CROSS_COMPILE=/group/SYSO_WS1516/armv6j-rpi-linux-gnueabihf/bin/armv6j-rpi-linux-gnueabihf-
export KDIR=../../../V3/buildroot/output/build/linux-4.2.3

NAME=template
SOURCES=$(NAME).c
OBJECTS=$(SOURCES:.c=.o)
TARGET_DIR=/usr/bin/

ifneq ($(KERNELRELEASE),)
obj-m	:= $(OBJECTS)

else
KDIR	:= $(KDIR)
PWD		:= $(shell pwd)

endif

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
clean:
	rm -rf *.o *.ko *.mod.c *.symvers *.order
install:
	scp $(NAME).ko user@192.168.29.48:$(TARGET_DIR)$(NAME).ko