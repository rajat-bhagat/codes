#for server side code

all: server

server: server.o
	gcc server.o -o server -lpthread

server.o: server.c
	gcc -c server.c 

clean: 
	rm *.o server
