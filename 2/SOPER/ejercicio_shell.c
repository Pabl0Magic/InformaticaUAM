/**
 * @file ejercicio_shell.c
 * @author Pablo Almarza (pablo.almarza@estudiante.uam.es)
 * @author Jorge Gonzalez (jorge.gonzalezgomez01@estudiante.uam.es)
 * @brief Ejecuta una shell que implementa los comandos básicos de la
 * shell del propio sistema donde está siendo ejecutado.
 * Al mandar comandos como ls -l, se ejecutará lo que se ejecutaría
 * en una shell normal, creando un nuevo hijo del proceso y 
 * esperando hasta que este finalice
 * @version 1.3
 * @date 2020-02-24
 * 
 * 
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <wordexp.h>

#define BUFFER_SIZE 255

int main(void)
{
	int pid;
	char *buf = (char *) malloc(BUFFER_SIZE * sizeof(char));
	char **cmd = NULL;
	wordexp_t result;
	/* Ponemos un $ como las shells tradicionales y leemos un buffer, si este buffer es EOF salimos del bucle*/
	while (printf("$ ") && fgets(buf, BUFFER_SIZE, stdin) != NULL && buf[0] != EOF)
	{
		/* Borramos el caracter \n con el que finaliza el buffer */
		buf[strlen(buf) - 1] = '\0';
		/* Miramos que wordexp no devuelva un error */
		if (wordexp(buf, &result, 0) != 0) {
			exit(EXIT_FAILURE);
		}
		/* Asignamos el puntero del array a una variable temporal */
		cmd = result.we_wordv;
		/* Si es un comando para salirse, salimos del programa */
		if(!strcmp(cmd[0], "exit") || !strcmp(cmd[0], "quit")) break;

		/* Hacemos un fork para lanzar el comando, si retorna error nos salimos con EXIT_FAILURE */
		pid = fork();
		if(pid < 0) {
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) {
			/* Ejecutamos el comando con sus argumentos y hacemos free's ya que es otro proceso */
			execvp(cmd[0], cmd);
			wordfree(&result);
			free(buf);

			exit(EXIT_SUCCESS);
		} else {
			/* Esperamos al hijo antes de continuar */
			wait(NULL);
		}

		wordfree(&result);
	}

	printf("\nExiting!\n");
	free(buf);
	exit(EXIT_SUCCESS);
}