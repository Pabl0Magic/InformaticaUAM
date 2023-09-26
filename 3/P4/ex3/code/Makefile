LIBS = 
LIB_DIR =  
FLAGS = -O3 -lgomp -lm -Wall -D_GNU_SOURCE -fopenmp

.PHONY: clean all

all: clean matrixMultiplicationSerie matrixMultiplicationLoop1 matrixMultiplicationLoop2 matrixMultiplicationLoop3

matrixMultiplicationSerie: matrixMultiplicationSerie.c arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

matrixMultiplicationLoop1: matrixMultiplicationLoop1.c arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

matrixMultiplicationLoop2: matrixMultiplicationLoop2.c arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

matrixMultiplicationLoop3: matrixMultiplicationLoop3.c arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

clean:
	rm -f *.o *~ fast slow matrixMultiplicationSerie matrixMultiplicationLoop1 matrixMultiplicationLoop2 matrixMultiplicationLoop3
