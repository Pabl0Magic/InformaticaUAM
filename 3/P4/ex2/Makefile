LIBS = 
LIB_DIR =  
FLAGS = -g -lgomp -lm -Wall -D_GNU_SOURCE -fopenmp

.PHONY: clean all

all: pescalar_serie pescalar_par1 pescalar_par2 pescalar_par3 pescalar_par_input clear

pescalar_%: pescalar_%.c arqo4.c
	gcc $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

clean:
	rm -f *.o *~ pescalar_serie pescalar_par1 pescalar_par2 pescalar_par3 pescalar_par_input pescalar_serie_input
	
clear:
	rm -f *.o *~
