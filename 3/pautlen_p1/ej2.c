#include <stdio.h>
#include "generacion.h"

int main (int argc, char** argv)
{
    FILE * salida;
    int cuantos_no = 0;

    if (argc != 2) {fprintf (stdout, "ERROR POCOS ARGUMENTOS\n"); return -1;}

    salida = fopen(argv[1],"w");

    escribir_subseccion_data(salida);
    escribir_cabecera_bss(salida);
    declarar_variable(salida, "b1", BOOLEANO, 1);

    escribir_segmento_codigo(salida);
    escribir_inicio_main(salida);

    /* scanf b1; */
    leer(salida,"b1",BOOLEANO);
/* printf !b1; */
    escribir_operando(salida,"b1",1);
    no(salida,1,cuantos_no++);
    escribir(salida,0,BOOLEANO);

    /* printf !!b1; */
    escribir_operando(salida,"b1",1);
    no(salida,1,cuantos_no++);
    no(salida,0,cuantos_no++);
    escribir(salida,0,BOOLEANO);

    escribir_fin(salida);

    fclose(salida);
    return 0;
}
