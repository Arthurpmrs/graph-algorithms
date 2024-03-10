CC=g++
CFLAGS=-Wall
VPATH=../modules
DEPS=graph.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prim: prim.o graph.o
	$(CC) -o prim prim.o graph.o $(CFLAGS)