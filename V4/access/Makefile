CC = /group/SYSO_WS1516/armv6j-rpi-linux-gnueabihf/bin/armv6j-rpi-linux-gnueabihf-gcc
CFLAGS = -g -W -Wall -ansi -static -pedantic
LDFLAGS = -lpthread

NAME = access
TARGET = $(NAME)
OBJECTS = $(TARGET).o
TARGET_DIR=/usr/bin/

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	$(RM) $(TARGET) $(TARGET).o

install:
	scp $(TARGET) user@192.168.29.48:$(TARGET_DIR)$(NAME)