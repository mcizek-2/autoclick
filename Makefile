OUT=aclick
FLAGS=-Wall -pthread -L .usr.lib32 -lX11 -lXext -lXtst
CC=gcc

compile: sharedmemory.o
	$(CC) main.c sharedmemory.o $(FLAGS) -o $(OUT)
	mkdir -p $${HOME}/.local/tmp
ifndef VERBOSE
.SILENT:
endif
pipe.o:
	$(CC) -Wall -c pipe.c -o pipe.o
clean:
	rm -f autoclick
	rm -f *.o
	rm -f ./local/tmp/aclick
install:
ifneq ("","$(wildcard ./autoclick)")
	cp ./autoclick /usr/local/bin/autoclick
else
	echo "You need to compile the file first"
endif
uninstall:
	rm -f /usr/local/bin/autoclick
