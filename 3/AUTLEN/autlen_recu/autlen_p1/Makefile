all: caso exe clean
	
caso:	
	gcc -Wall -ansi -pedantic -g -o ej1 caso.c transforma.c lib_afnd_64.a
exe:
	valgrind --track-origins=yes ./ej1
clean:
	rm -rf *.o ej1