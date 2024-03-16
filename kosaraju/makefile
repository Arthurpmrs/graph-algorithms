CC=g++
CFLAGS=-Wall
VPATH=../modules
DEPS=graph.h utils.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kosaraju: kosaraju.o graph.o utils.o
	$(CC) -o kosaraju kosaraju.o graph.o utils.o $(CFLAGS)
