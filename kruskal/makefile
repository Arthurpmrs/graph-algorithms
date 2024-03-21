CC=g++
CFLAGS=
VPATH=../modules
DEPS=graph.h utils.h unionfind.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kruskal: kruskal.o graph.o unionfind.o utils.o
	$(CC) -o kruskal.bin kruskal.o graph.o unionfind.o utils.o $(CFLAGS)