LIBS = 
LIB_DIR =  
FLAGS = -O3 -Wall -D_GNU_SOURCE

.PHONY: clean all

all: clean matrixMultiplication

matrixMultiplication: matrixMultiplication.c arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

clean:
	rm -f *.o *~ fast slow matrixMultiplication
