#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generacion.h"

int main (int argc, char ** argv)
{

        if (argc != 2) {fprintf (stdout, "ERROR POCOS ARGUMENTOS\n"); return -1;}

        int etiqueta = 0;
        int getiqueta = 0;
        int etiquetas[MAX_ETIQUETAS];
        int cima_etiquetas=-1;
        FILE * fd_asm;
        fd_asm = fopen(argv[1],"w");
        escribir_subseccion_data(fd_asm);
        escribir_cabecera_bss(fd_asm);

        //int m;
        declarar_variable(fd_asm,"m", 1, 1);

        escribir_segmento_codigo(fd_asm);
        escribir_inicio_main(fd_asm);

        //m=0;
        escribir_operando(fd_asm,"0",0);
        asignar(fd_asm,"m",0);

        //Gestion de etiquetas para abrir el ambito del if. Esta sera la etiqueta que tenga.
        getiqueta++;
        cima_etiquetas++;
        etiquetas[cima_etiquetas]=getiqueta;
        etiqueta = getiqueta;

//Condición del if. Salto a fin si, si la condicion se da.
        escribir_operando(fd_asm,"m",1);
        escribir_operando(fd_asm,"5",0);
        mayor(fd_asm,1,0,etiqueta);
        ifthenelse_inicio(fd_asm, 0, etiqueta);

        //printf 2
        escribir_operando(fd_asm,"2",0);
        escribir(fd_asm,0,ENTERO);

        //Salto a fin sino al terminar el if, impresion de la etiqueta fin_si. Recogemos la etiqueta.
        etiqueta = etiquetas[cima_etiquetas];
        ifthenelse_fin_then(fd_asm, etiqueta);

        //printf 3
        escribir_operando(fd_asm,"3",0);
        escribir(fd_asm,0,ENTERO);

        //Fin del condicional if. Imprimimos la etiqueta de ambito del fin del condicional y restamos el contador.
        etiqueta = etiquetas[cima_etiquetas];
        ifthenelse_fin(fd_asm, etiqueta);
        cima_etiquetas--;

        escribir_fin(fd_asm);
        fclose(fd_asm);
}
