CC=g++
CFLAGS=-Wall
VPATH=../modules
DEPS=graph.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dfs: dfs.o graph.o
	$(CC) -o dfs dfs.o graph.o $(CFLAGS)