CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first second

first.o: scenarios/first.cpp address.h echo_service.h echo_service_installer.h host.h manual_router.h message_service.h message_service_installer.h node.h packet.h router.h service.h service_installer.h link.h
	$(CC) $(CFLAGS) -c -o first.o scenarios/first.cpp

second.o: scenarios/second.cpp address.h echo_service.h echo_service_installer.h host.h manual_router.h message_service.h message_service_installer.h node.h packet.h router.h service.h service_installer.h link.h
	$(CC) $(CFLAGS) -c -o second.o scenarios/second.cpp

first: first.o link.o node.o 
	$(CC) $(CFLAGS) -o first first.o link.o node.o 

second: second.o link.o node.o 
	$(CC) $(CFLAGS) -o second second.o link.o node.o 

link.o: link.cpp link.h
	$(CC) $(CFLAGS) -c -o link.o link.cpp

node.o: node.cpp node.h 
	$(CC) $(CFLAGS) -c -o node.o node.cpp

clean:
	rm -f *.o first second
