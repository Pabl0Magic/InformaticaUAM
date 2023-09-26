
CC = gcc -pedantic -pthread
CFLAGS = -Wall -g
EXE = ejercicio_shell ejercicio_pipes ejercicio_hilos ejercicio_arbol

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

ejercicio_arbol.o : ejercicio_arbol.c
	$(CC) $(CFLAGS) -c $<

ejercicio_hilos.o : ejercicio_hilos.c
	$(CC) $(CFLAGS) -c $<

ejercicio_pipes.o : ejercicio_pipes.c
	$(CC) $(CFLAGS) -c $<

ejercicio_shell.o : ejercicio_shell.c
	$(CC) $(CFLAGS) -c $<