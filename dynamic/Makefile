# this is the variable zone
cc= gcc
cflag= -c -Wall -FPIC

all: a.out

add.o: add.c
	$(cc) $(cflag) add.c

sub.o: sub.c
	$(cc) $(cflag) sub.c

libbasic.so: add.o sub.o
	$(cc) -shared -o libbasic.so add.o sub.o
	#cp libbasic.so /usr/lib/
	ldconfig -n ~/lib/dynamic

demo.o: basic.h demo.c
	$(cc) -c demo.c

a.out: libbasic.so demo.o
	$(cc)  -L. demo.o -l:libbasic.so

clean: 
	rm *.o a.out
