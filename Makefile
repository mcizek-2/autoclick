OUT=autoclick
FLAGS=-Wall -pthread -lX11 -lXext -lXtst 
CC=gcc

compile: pipe.o
	$(CC) main.c pipe.o $(FLAGS) -o $(OUT)
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
