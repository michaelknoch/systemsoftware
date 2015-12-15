CC = /group/SYSO_WS1516/armv6j-rpi-linux-gnueabihf/bin/armv6j-rpi-linux-gnueabihf-gcc
CFLAGS = -g -Wall -Werror -static
LDFLAGS = -lpthread

NAME = access
TARGET = $(NAME)
OBJECTS = $(TARGET).o
TARGET_DIR=/lib/modules/4.2.3/extra/

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	$(RM) $(TARGET) $(TARGET).o

install:
	scp $(TARGET) user@192.168.29.49:$(TARGET_DIR)$(NAME)