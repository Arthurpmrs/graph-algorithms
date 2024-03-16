CC=g++
CFLAGS=-Wall
VPATH=../modules
DEPS=graph.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bellman: bellman.o graph.o
	$(CC) -o bellman bellman.o graph.o $(CFLAGS)
