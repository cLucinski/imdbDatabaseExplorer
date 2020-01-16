CC = gcc
CFLAGS = -Wall -ansi -pedantic

all: a3

a3: binary.o common.o name.o principals.o title.o main.o
	$(CC) $(CFLAGS) binary.o common.o name.o principals.o title.o main.o -o a3

binary.o: binary.c common.h
	$(CC) $(CFLAGS) -c binary.c -o $@

common.o: common.c
	$(CC) $(CFLAGS) -c common.c -o $@

name.o: name.c binary.h common.h
	$(CC) $(CFLAGS) -c name.c -o $@

principals.o: principals.c binary.h common.h
	$(CC) $(CFLAGS) -c principals.c -o $@

title.o: title.c binary.h common.h
	$(CC) $(CFLAGS) -c title.c -o $@

main.o: binary.c common.c name.c principals.c title.c main.c binary.h common.h name.h principals.h title.h
	$(CC) $(CFLAGS) -c main.c -o $@

clean:
	rm *.o a3

cleanAll:
	rm *.o binary common name principals title main a3