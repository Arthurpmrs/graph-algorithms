CC=g++
CFLAGS=
VPATH=../modules
DEPS=graph.h utils.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prim: prim.o graph.o utils.o
	$(CC) -o prim.bin prim.o graph.o utils.o $(CFLAGS)