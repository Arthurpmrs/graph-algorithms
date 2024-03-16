CC=g++
CFLAGS=-Wall
VPATH=../modules
DEPS=graph.h utils.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bellman: bellman.o graph.o utils.o
	$(CC) -o bellman bellman.o graph.o utils.o $(CFLAGS)
