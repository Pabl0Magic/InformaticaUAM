CC = gcc
CFLAGS = -g -Wall
OBJECTS = symbols_table.o hash_table.o prueba_tabla.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o prueba_tabla $(OBJECTS)

hash_table.o: hash_table.c
	$(CC) $(CFLAGS) -c hash_table.c

symbols_table.o: symbols_table.c
	$(CC) $(CFLAGS) -c symbols_table.c

prueba_tabla.o: prueba_tabla.c
	$(CC) $(CFLAGS) -c prueba_tabla.c

clean:
	rm -rf prueba_tabla  *.o