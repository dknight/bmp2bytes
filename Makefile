CC      = gcc
CFLAGS  = -g
RM      = rm -f
PREFIX ?= /usr/local
EXEC    = bmp2bytes

default: all

all: build

build: main.c
	$(CC) $(CFLAGS) -o $(EXEC) main.c
	@echo Done

copybin:
	cp $(EXEC) $(PREFIX)/bin
	chmod 0755 $(PREFIX)/bin/$(EXEC)
	@echo Done
	
install: build copybin

clean:
	$(RM) bmp2bytes
