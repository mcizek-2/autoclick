OUT=aclick
FLAGS=-g -Wall -L .usr.lib32 -lX11 -lXext -lXtst
CC=gcc

compile: sharedmemory.o
	$(CC) main.c sharedmemory.o $(FLAGS) -o autoclick
	mkdir -p $${HOME}/.local/var
	touch $${HOME}/.local/var/aclick
ifndef VERBOSE
.SILENT:
endif
sharedmemory.o:
	$(CC) -g -Wall -c sharedmemory.c -o sharedmemory.o
clean:
	rm -f autoclick
	rm -f *.o
	rm -f ./local/var/aclick
install:
ifneq ("","$(wildcard ./autoclick)")
	cp ./autoclick /usr/local/bin/autoclick
else
	echo "You need to compile the file first"
endif
uninstall:
	rm -f /usr/local/bin/autoclick
