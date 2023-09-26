/**
 * @file ejercicio_arbol.c
 * @author Pablo Almarza (pablo.almarza@estudiante.uam.es)
 * @author Jorge Gonzalez (jorge.gonzalezgomez01@estudiante.uam.es)
 * @brief A partir de un proceso padre se iran generando procesos
 * hijos de cada hijo, es decir el padre tendra solo un hijo, ese
 * hijo tendra otro hijo y asi sucesivamente hasta el numero de procesos
 * definidos, formando asi una escalera.
 * @version 1.4
 * @date 2020-02-24
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define NUM_PROC 5

int main(void) {
    pid_t pid;

	for(int i = 0; i < NUM_PROC; i++)
	{
		pid = fork();
		if(pid <  0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if(pid ==  0)
		{
			printf("PID: %d PPID: %d\n", getpid(), getppid());
		}
		else if(pid >  0)
		{
			printf("Padre %d\n", i);
	        while(wait(NULL) != -1);
            exit(EXIT_SUCCESS);
		}
	}
	
    exit(EXIT_SUCCESS);
}