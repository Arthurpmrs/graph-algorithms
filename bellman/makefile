CC=g++
CFLAGS=
VPATH=../modules
DEPS=graph.h utils.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bellman: bellman.o graph.o utils.o
	$(CC) -o bellman.bin bellman.o graph.o utils.o $(CFLAGS)
