#include "generacion.h"

int main (int argc, char ** argv)
{
    int etiqueta = 0;
    int getiqueta = 0;
    int etiquetas[MAX_ETIQUETAS];
    int cima_etiquetas=-1;
    FILE * fd_asm;

    fd_asm = fopen(argv[1],"w");
    escribir_subseccion_data(fd_asm);
    escribir_cabecera_bss(fd_asm);

        //int z;
    declarar_variable(fd_asm,"z", 1, 1);
    escribir_segmento_codigo(fd_asm);
    //Declaramos la funcion. Vamos a imprimir su etiqueta y decir que tiene una variable local.
    //function int doble(int arg)
        //{
        //        int auxArg;
    declararFuncion(fd_asm,"doble",1);
    
    //auxArg = arg; Asignacion de parametro a variable local. Solo hay un parametro.
    escribirParametro(fd_asm,0,1);
    escribirVariableLocal(fd_asm,1);
    asignarDestinoEnPila(fd_asm,1);

    //2*arg.
    escribir_operando(fd_asm,"2",0);
    escribirParametro(fd_asm,0,1);
    multiplicar(fd_asm,0,1);
    
    //Retornamos de la funcion con lo que esta encima de la pila.
    retornarFuncion(fd_asm,0);    

    escribir_inicio_main(fd_asm);
    //z=2
    escribir_operando(fd_asm,"2",0);
       asignar(fd_asm,"z",0);

    escribir_operando(fd_asm,"z",1);

    // printf doble(z)

    //Llamamos a la funcion que tiene 1 argumento. Estamos dando un salto a la etiqueta. Primero apilamos el parametro.
    operandoEnPilaAArgumento(fd_asm,1);
    llamarFuncion(fd_asm,"doble",1);

    
    //Imprimimos el resultado de la funcion.
    escribir(fd_asm,0,ENTERO);


    escribir_fin(fd_asm);
    fclose(fd_asm);    

}


