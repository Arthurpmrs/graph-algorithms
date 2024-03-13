CC=g++
CFLAGS=-Wall
VPATH=../modules
DEPS=graph.h utils.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prim: prim.o graph.o utils.o
	$(CC) -o prim prim.o graph.o utils.o $(CFLAGS)