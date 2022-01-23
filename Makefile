CC= cc
CFLAGS= -std=c89 -pedantic -Wall
OBJECTS= cl.o
all: cl
cl.o: cl.c
	$(CC) $(CFLAGS) -c cl.c
cl: $(OBJECTS)
	$(CC) $(OBJECTS) -o cl
clean:
	rm -f *.o cl
