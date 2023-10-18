hello: main.o somePrint.o
	gcc -o hello main.o somePrint.o

main.o: main.c main.h
	gcc -c main.c

somePrint.o: somePrint.c main.h
	gcc -c somePrint.c
