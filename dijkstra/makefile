CC=g++
CFLAGS=-Wall
VPATH=../modules
DEPS=graph.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dijkstra: dijkstra.o graph.o
	$(CC) -o dijkstra dijkstra.o graph.o $(CFLAGS)
