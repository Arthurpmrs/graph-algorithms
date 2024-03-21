CC=g++
CFLAGS=
VPATH=../modules
DEPS=graph.h utils.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dijkstra: dijkstra.o graph.o utils.o
	$(CC) -o dijkstra.bin dijkstra.o graph.o utils.o $(CFLAGS)
