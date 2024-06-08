CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
OBJECTS = simulator.o object.o

all: first second

first.o: scenarios/first.cpp address.h echo_service.h echo_service_installer.h host.h manual_router.h message_service.h message_service_installer.h node.h packet.h router.h service.h service_installer.h link.h
	$(CC) $(CFLAGS) -c -o first.o scenarios/first.cpp

second.o: scenarios/second.cpp address.h echo_service.h echo_service_installer.h host.h manual_router.h message_service.h message_service_installer.h node.h packet.h router.h service.h service_installer.h link.h
	$(CC) $(CFLAGS) -c -o second.o scenarios/second.cpp

first: first.o link.o node.o $(OBJECTS)
	$(CC) $(CFLAGS) -o first first.o link.o node.o $(OBJECTS)

second: second.o link.o node.o $(OBJECTS)
	$(CC) $(CFLAGS) -o second second.o link.o node.o $(OBJECTS)

link.o: link.cpp link.h
	$(CC) $(CFLAGS) -c -o link.o link.cpp

node.o: node.cpp node.h 
	$(CC) $(CFLAGS) -c -o node.o node.cpp

simulator.o: simulator.cpp
	$(CC) $(CFLAGS) -c simulator.cpp

object.o: object.cpp
	$(CC) $(CFLAGS) -c object.cpp

clean:
	rm -f *.o first second
