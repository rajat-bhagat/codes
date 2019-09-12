#for client side code

all: client

client: client.o
	gcc client.o -o client -lpthread

client.o: client.c
	gcc -c client.c
	
clean: 
	rm *.o client

