CC=g++
CFLAGS=-Wall
VPATH=../modules
DEPS=graph.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kosaraju: kosaraju.o graph.o
	$(CC) -o kosaraju kosaraju.o graph.o $(CFLAGS)
