CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: build

build: main.c
	$(CC) $(CFLAGS) -o bmp2bytes main.c
	@echo Done

clean:
	$(RM) bmp2bytes
