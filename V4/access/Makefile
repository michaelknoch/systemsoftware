CC = /group/SYSO_WS1516/armv6j-rpi-linux-gnueabihf/bin/armv6j-rpi-linux-gnueabihf-gcc
CFLAGS = -g -W -Wall -ansi -static -pedantic
LDFLAGS = -lpthread

TARGET = access
OBJECTS = $(TARGET).o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	$(RM) $(TARGET) $(TARGET).o

install:
	scp $(NAME) user@192.168.29.48:$(TARGET_DIR)$(NAME)