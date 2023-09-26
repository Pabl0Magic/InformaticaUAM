
CC = gcc -pedantic -pthread -g
CFLAGS = -Wall -g
EXE = ejercicio_alarm ejercicio_alternar ejercicio_captura_mejorado ejercicio_captura ejercicio_kill ejercicio_sem_signal ejercicio_sem ejercicio_sigset ejercicio_captura_4 ejercicio_prottemp ejercicio_prottemp_mejorado ejercicio_lect_escr ejercicio_prottemp_mejorado_op

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)
bins: EXE.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<