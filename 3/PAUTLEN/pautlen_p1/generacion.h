#ifndef GENERACION_H
#define GENERACION_H

#include <stdio.h>


/* Declaraciones de tipos de datos del compilador */
#define ENTERO	0
#define BOOLEANO 	1
#define MAX_ETIQUETAS 100

/* OBSERVACIÓN GENERAL A TODAS LAS FUNCIONES:
   Todas ellas escriben el código NASM a un FILE* proporcionado como primer argumento.
*/

void escribir_cabecera_bss(FILE* fpasm);
/*
   Código para el principio de la sección .bss.
   Con seguridad sabes que deberás reservar una variable entera para guardar el puntero de pila extendido (esp). Se te sugiere el nombre __esp para esta variable.
*/

void escribir_subseccion_data(FILE* fpasm);
/*
   Declaración (con directiva db) de las variables que contienen el texto de los mensajes para la identificación de errores en tiempo de ejecución.
   En este punto, al menos, debes ser capaz de detectar la división por 0.
*/

void declarar_variable(FILE* fpasm, char * nombre,  int tipo,  int tamano);
/*
   Para ser invocada en la sección .bss cada vez que se quiera declarar una variable:
    • El argumento nombre es el de la variable.
    • tipo puede ser ENTERO o BOOLEANO (observa la declaración de las constantes del principio del fichero).
    • Esta misma función se invocará cuando en el compilador se declaren vectores, por eso se adjunta un argumento final (tamano) que para esta primera práctica siempre recibirá el valor 1.
*/

void escribir_segmento_codigo(FILE* fpasm);
/*
   Para escribir el comienzo del segmento .text, básicamente se indica que se exporta la etiqueta main y que se usarán las funciones declaradas en la librería alfalib.o
*/

void escribir_inicio_main(FILE* fpasm);
/* 
   En este punto se debe escribir, al menos, la etiqueta main y la sentencia que guarda el puntero de pila en su variable (se recomienda usar __esp).
*/

void escribir_fin(FILE* fpasm);
/*
   Al final del programa se escribe:
    • El código NASM para salir de manera controlada cuando se detecta un error en tiempo de ejecución (cada error saltará a una etiqueta situada en esta zona en la que se imprimirá el correspondiente mensaje y se saltará a la zona de finalización del programa).
    • En el final del programa se debe:
         ·Restaurar el valor del puntero de pila (a partir de su variable __esp)
         ·Salir del programa (ret).
*/

void escribir_operando(FILE* fpasm, char* nombre, int es_variable);
/*
   Función que debe ser invocada cuando se sabe un operando de una operación aritmético-lógica y se necesita introducirlo en la pila.
    • nombre es la cadena de caracteres del operando tal y como debería aparecer en el fuente NASM
    • es_variable indica si este operando es una variable (como por ejemplo b1) con un 1 u otra cosa (como por ejemplo 34) con un 0. 
    Recuerda que en el primer caso internamente se representará como _b1 y, sin embargo, 
    en el segundo se representará tal y como esté en el argumento (34).
*/

void asignar(FILE* fpasm, char* nombre, int es_variable);
/*
    • Genera el código para asignar valor a la variable de nombre nombre. 
    • Se toma el valor de la cima de la pila.
    • El último argumento es el que indica si lo que hay en la cima de la pila es una referencia (1) o ya un valor explícito (0).
*/


/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */
/*
   En todas ellas se realiza la operación como se ha resumido anteriormente:
    • Se extrae de la pila los operandos
    • Se realiza la operación
    • Se guarda el resultado en la pila
   Los dos últimos argumentos indican respectivamente si lo que hay en la pila es una referencia a un valor o un valor explícito.
   Deben tenerse en cuenta las peculiaridades de cada operación. En este sentido sí hay que mencionar explícitamente que, en el caso de la división, se debe controlar si el divisor es “0” y en ese caso se debe saltar a la rutina de error controlado (restaurando el puntero de pila en ese caso y comprobando en el retorno que no se produce “Segmentation Fault”)
*/
void sumar(FILE* fpasm, int es_variable_1, int es_variable_2);
void restar(FILE* fpasm, int es_variable_1, int es_variable_2);
void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2);
void dividir(FILE* fpasm, int es_variable_1, int es_variable_2);
void o(FILE* fpasm, int es_variable_1, int es_variable_2);
void y(FILE* fpasm, int es_variable_1, int es_variable_2);

void cambiar_signo(FILE* fpasm, int es_variable);
/*
   Función aritmética de cambio de signo. 
   Es análoga a las binarias, excepto que sólo requiere de un acceso a la pila ya que sólo usa un operando.
*/

void no(FILE* fpasm, int es_variable, int cuantos_no);
/*
   Función monádica lógica de negación. No hay un código de operación de la ALU que realice esta operación por lo que se debe codificar un algoritmo que, si encuentra en la cima de la pila un 0 deja en la cima un 1 y al contrario.
   El último argumento es el valor de etiqueta que corresponde (sin lugar a dudas, la implementación del algoritmo requerirá etiquetas). Véase en los ejemplos de programa principal como puede gestionarse el número de etiquetas cuantos_no.
*/

/* FUNCIONES COMPARATIVAS */
/* 
   Todas estas funciones reciben como argumento si los elementos a comparar son o no variables.
   El resultado de las operaciones, que siempre será un booleano (“1” si se cumple la comparación y “0” si no se cumple),
   se deja en la pila como en el resto de operaciones. 
   Se deben usar etiquetas para poder gestionar los saltos necesarios para implementar las comparaciones.
*/
void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta);
void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta);
void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta);
void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta);
void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta);
void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta);

/* FUNCIONES DE ESCRITURA Y LECTURA */
/*
   Se necesita saber el tipo de datos que se va a procesar (ENTERO o BOOLEANO) ya que hay diferentes funciones de librería para la lectura (idem. escritura) de cada tipo.
   Se deben insertar en la pila los argumentos necesarios, realizar la llamada (call) a la función de librería correspondiente y limpiar la pila.
*/
void leer(FILE* fpasm, char* nombre, int tipo);
void escribir(FILE* fpasm, int es_variable, int tipo);


/*VECTORS, FUNCTIONS, LOOPS AND CONDITIONALS*/
/*
    • Generación de código para el inicio de una estructura if-then-else
    • Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
    • exp_es_variable 
        ◦ Es 1 si la expresión de la condición es algo asimilable a una variable (identificador, elemento de vector)
        ◦ Es 0 en caso contrario (constante u otro tipo de expresión)
*/
void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta); 
   /*
    • Generación de código para el inicio de una estructura if-then
    • Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
    • exp_es_variable 
        ◦ Es 1 si la expresión de la condición es algo asimilable a una variable (identificador, elemento de vector)
        ◦ Es 0 en caso contrario (constante u otro tipo de expresión)
*/
void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta);

/**
 * @brief • Generación de código para el fin de una estructura if-then
    • Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca según se ha explicado
    • Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas puesto que se ha liberado la última de ellas.
 * 
 */
void ifthen_fin(FILE * fpasm, int etiqueta);

/**
 *  • Generación de código para el fin de la rama then de una estructura if-then-else
    • Sólo necesita usar la etiqueta adecuada, aunque es el final de una rama, luego debe venir otra (la rama else) antes de que se termine la estructura 
    y se tenga que ajustar las etiquetas por lo que sólo se necesita que se utilice la etiqueta que corresponde al momento actual.
 * 
 */

void ifthenelse_fin_then( FILE * fpasm, int etiqueta);

/**
 *  • Generación de código para el fin de una estructura if-then-else
    • Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca según se ha explicado
    • Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas puesto que se ha liberado la última de ellas.
 * 
 */
void ifthenelse_fin( FILE * fpasm, int etiqueta);

/**
 *  • Generación de código para el inicio de una estructura while
    • Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
    • exp_es_variable 
    ◦ Es 1 si la expresión de la condición es algo asimilable a una variable (identificador, elemento de vector)
    ◦ Es 0 en caso contrario (constante u otro tipo de expresión)
 * 
 */
void while_inicio(FILE * fpasm, int etiqueta);

/**
 *  • Generación de código para el momento en el que se ha generado el código de la expresión de control del bucle
    • Sólo necesita usar la etiqueta adecuada, por lo que sólo se necesita que se recupere el valor de la etiqueta que corresponde al momento actual.
    • exp_es_variable 
    ◦ Es 1 si la expresión de la condición es algo asimilable a una variable (identificador, o elemento de vector)
    ◦ Es 0 en caso contrario (constante u otro tipo de expresión)
 * 
 */
void while_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta);

/**
 *  • Generación de código para el final de una estructura while
    • Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca según se ha explicado
    • Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas puesto que se ha liberado la última de ellas.
 * 
 */
void while_fin( FILE * fpasm, int etiqueta);

/**
 * • Generación de código para indexar un vector
   ◦ Cuyo nombre es nombre_vector
   ◦ Declarado con un tamaño tam_max
   ◦ La expresión que lo indexa está en la cima de la pila
   ◦ Puede ser una variable (o algo equivalente) en cuyo caso exp_es_direccion vale 1
   ◦ Puede ser un valor concreto (en ese caso exp_es_direccion vale 0)
   • Según se especifica en el material, es suficiente con utilizar dos registros para realizar esta tarea. 
 * 
 */
void escribir_elemento_vector(FILE * fpasm,char * nombre_vector, int tam_max, int exp_es_direccion);

/**
 * • Generación de código para iniciar la declaración de una función.
   • Es necesario proporcionar 
   ◦ Su nombre
   ◦ Su número de variables locales
 * 
 */
void declararFuncion(FILE * fd_asm, char * nombre_funcion, int num_var_loc);

/**
 * • Generación de código para el retorno de una función.
   ◦ La expresión que se retorna está en la cima de la pila.
   ◦ Puede ser una variable (o algo equivalente) en cuyo caso exp_es_direccion vale 1
   ◦ Puede ser un valor concreto (en ese caso exp_es_direccion vale 0)
 * 
 */
void retornarFuncion(FILE * fd_asm, int es_variable);

/**
 * Función para dejar en la cima de la pila la dirección efectiva del parámetro que ocupa la posición pos_parametro 
 * (recuerda que los parámetros se ordenan con origen 0) de un total de num_total_parametros 
 * 
 */
void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros);

/**
 * Función para dejar en la cima de la pila la dirección efectiva de la variable local 
 * que ocupa la posición posicion_variable_local (recuerda que ordenadas con origen 1) 
 * 
 */
void escribirVariableLocal(FILE* fpasm, int posicion_variable_local);

/**
 *  • Función para poder asignar a un destino que no es una variable “global” (tipo _x) por ejemplo parámetros o variables locales (ya que en ese caso su nombre real de alto nivel, no se tiene en cuenta pues es realmente un desplazamiento a partir de ebp: ebp+4 o ebp-8 por ejemplo).
    • Se debe asumir que en la pila estará
        ◦ Primero (en la cima)  la dirección donde hay que asignar
        ◦ Debajo (se ha introducido en la pila antes) lo que hay que asignar
    • es_variable 
        ◦ Es 1 si la expresión que se va a asignar es algo asimilable a una variable (identificador, o elemento de vector)
        ◦ Es 0 en caso contrario (constante u otro tipo de expresión)
 * 
 */
void asignarDestinoEnPila(FILE* fpasm, int es_variable);

/**
 * @brief     • Como habrás visto en el material, nuestro convenio de llamadas a las funciones asume que los argumentos se pasan por valor, 
 * esto significa que siempre se dejan en la pila “valores” y no “variables”
    • Esta función realiza la tarea de dado un operando escrito en la pila y sabiendo si es variable o no (es_variable) se deja en la pila el valor correspondiente
 * 
 */
void operandoEnPilaAArgumento(FILE * fd_asm, int es_variable);

/**
 *  • Esta función genera código para llamar a la función nombre_funcion asumiendo que los argumentos 
 * están en la pila en el orden fijado en el material de la asignatura.
    • Debe dejar en la cima de la pila el retorno de la función tras haberla limpiado de sus argumentos
    • Para limpiar la pila puede utilizar la función de nombre limpiarPila
 * 
 */
void llamarFuncion(FILE * fd_asm, char * nombre_funcion, int num_argumentos);

/**
 *  • Genera código para limpiar la pila tras invocar una función
    • Esta función es necesaria para completar la llamada a métodos, su gestión 
    dificulta el conocimiento por parte de la función de llamada del número de argumentos que hay en la pila

 * 
 */
void limpiarPila(FILE * fd_asm, int num_argumentos);


#endif