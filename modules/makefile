build: main.o argReturn.o argNoreturn.o noargNoreturn.o noargReturn.o
	gcc -o solution main.o argReturn.c argNoreturn.o noargNoreturn.o noargReturn.o

main.o: main.c main.h
	gcc -c main.c

argReturn.o: argReturn.c main.h
	gcc -c argReturn.c

argNoreturn.o: argNoreturn.c main.h
	gcc -c argNoreturn.c

noargNoreturn.o: noargNoreturn.c main.h
	gcc -c noargNoreturn.c

noargReturn.o: noargReturn.c main.h
	gcc -c noargReturn.c

