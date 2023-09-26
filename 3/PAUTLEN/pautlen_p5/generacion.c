#include "generacion.h"

void escribir_cabecera_bss(FILE* fpasm) {

    fprintf(fpasm,"segment .bss\n");
    fprintf(fpasm, "\t__esp resd 1\n");

}

void escribir_subseccion_data(FILE* fpasm) {

    fprintf(fpasm, "segment .data\n");
    fprintf(fpasm, "\t_out_of_range db \"Indice de vector fuera de rango\", 0\n");
    fprintf(fpasm, "\t_div_by_zero_error db \"Division by zero\", 0\n");

}

void declarar_variable(FILE* fpasm, char * nombre,  int tipo,  int tamano){

    if(tipo == ENTERO) {
        fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano);
    } else {
        fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano);
    }

}

void escribir_segmento_codigo(FILE* fpasm) {

    fprintf(fpasm, "segment .text\n");
    fprintf(fpasm, "\tglobal main\n");
    fprintf(fpasm, "\textern scan_int, scan_boolean, print_int, print_boolean, print_blank, print_endofline, print_string\n");
    
}

void escribir_inicio_main(FILE* fpasm){
    
    fprintf(fpasm, "main:\n");
    fprintf(fpasm, "\tmov [__esp], esp\n");
}

void escribir_fin(FILE* fpasm) {

    fprintf(fpasm, "\tjmp near fin\n");

    fprintf(fpasm, "fin_error_division:\n");
    fprintf(fpasm, "\tpush dword _div_by_zero_error\n");
    fprintf(fpasm, "\tcall print_string\n");
    fprintf(fpasm, "\tadd esp, 4\n");
    fprintf(fpasm, "\tcall print_endofline\n");
    fprintf(fpasm, "\tjmp near fin\n");

    fprintf(fpasm, "fin_indice_fuera_rango:\n");
    fprintf(fpasm, "\tpush dword _out_of_range\n");    
    fprintf(fpasm, "\tcall print_string\n");
    fprintf(fpasm, "\tadd esp, 4\n");
    fprintf(fpasm, "\tcall print_endofline\n");

    fprintf(fpasm, "fin:\n");
    fprintf(fpasm, "\tmov esp, [__esp]\n");
    fprintf(fpasm, "\tret\n");

}

void escribir_operando(FILE* fpasm, char* nombre, int es_variable) {

    if(es_variable) {
        fprintf(fpasm, "\tpush dword _%s\n", nombre);
    } else { 
        fprintf(fpasm, "\tpush dword %s\n", nombre); 
    }

}

void asignar(FILE* fpasm, char* nombre, int es_variable) {

    if (es_variable == 0) {
        fprintf(fpasm, "\tpop dword eax\n");
        fprintf(fpasm, "\tmov [_%s], eax\n", nombre);
    } else {
        fprintf(fpasm, "\tpop dword eax\n");
        fprintf(fpasm, "\tmov _%s, [eax]\n", nombre);
    }

}

void asignarElementoVector(FILE* fpasm, char* nombre, int es_variable){
  fprintf(fpasm, "\n\tpop dword eax");
  fprintf(fpasm, "\n\tpop dword edx");

  if (es_variable == 1){
  	fprintf(fpasm, "\n\tmov eax, [eax]");
  }

  fprintf(fpasm, "\n\tmov [edx], eax");

  fprintf(fpasm, "\n");
}

void sumar(FILE* fpasm, int es_variable_1, int es_variable_2) {
    
    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable_2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable_1) fprintf(fpasm, "\tmov eax, [eax]\n");
    
    fprintf(fpasm, "\tadd eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
    
}

void restar(FILE* fpasm, int es_variable_1, int es_variable_2)  {

    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable_2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable_1) fprintf(fpasm, "\tmov eax, [eax]\n");
    
    fprintf(fpasm, "\tsub eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");

}
void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2) {
    
    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable_2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable_1) fprintf(fpasm, "\tmov eax, [eax]\n");
    
    fprintf(fpasm, "\timul ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");

}
void dividir(FILE* fpasm, int es_variable_1, int es_variable_2) {

    
    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable_2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable_1) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp ebx, 0\n");
    fprintf(fpasm, "\tje fin_error_division\n");
    fprintf(fpasm, "\tcmp ebx, 0\n");
    fprintf(fpasm, "\tjl division_negativa\n");

    fprintf(fpasm, "\tmov edx, 0\n");
    fprintf(fpasm, "\tidiv ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
    fprintf(fpasm, "\tjmp fin_division\n");

    fprintf(fpasm, "division_negativa:\n");
    fprintf(fpasm, "\tmov edx, -1\n");
    fprintf(fpasm, "\tidiv ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
    fprintf(fpasm, "\tjmp fin_division\n");

    fprintf(fpasm, "\tfin_division:\n");

}

void o(FILE* fpasm, int es_variable_1, int es_variable_2) {

    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable_2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable_1) fprintf(fpasm, "\tmov eax, [eax]\n");
    
    fprintf(fpasm, "\tor eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}
void y(FILE* fpasm, int es_variable_1, int es_variable_2) {

    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable_2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable_1) fprintf(fpasm, "\tmov eax, [eax]\n");
    
    fprintf(fpasm, "\tand eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");

}

void cambiar_signo(FILE* fpasm, int es_variable) {

    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tneg eax\n");
    fprintf(fpasm, "\tpush dword eax\n");
}

void no(FILE* fpasm, int es_variable, int cuantos_no) {

    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\txor eax, 1\n");
    fprintf(fpasm, "\tpush dword eax\n");

}

void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {
    
    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable1) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tje igual%d\n", etiqueta);

    fprintf(fpasm, "\tmov eax, 0\n");
    fprintf(fpasm, "\tjmp noigual%d\n", etiqueta);

    fprintf(fpasm, "\tigual%d: \n", etiqueta);
    fprintf(fpasm, "\tmov eax, 1\n");

    fprintf(fpasm, "\tnoigual%d:\n", etiqueta);

    fprintf(fpasm, "\tpush dword eax\n");

}
void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {

    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable1) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjne distinto%d\n", etiqueta);

    fprintf(fpasm, "\tmov eax, 0\n");
    fprintf(fpasm, "\tjmp nodistinto%d\n", etiqueta);

    fprintf(fpasm, "\tdistinto%d: \n", etiqueta);
    fprintf(fpasm, "\tmov eax, 1\n");

    fprintf(fpasm, "\tnodistinto%d:\n", etiqueta);

    fprintf(fpasm, "\tpush dword eax\n");

}
void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {

    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable1) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjle menorigual%d\n", etiqueta);

    fprintf(fpasm, "\tmov eax, 0\n");
    fprintf(fpasm, "\tjmp nomenorigual%d\n", etiqueta);

    fprintf(fpasm, "menorigual%d:\n", etiqueta);
    fprintf(fpasm, "\tmov eax, 1\n");

    fprintf(fpasm, "nomenorigual%d:\n", etiqueta);

    fprintf(fpasm, "\tpush dword eax\n");

}
void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {

    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable1) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjge mayorigual%d\n", etiqueta);

    fprintf(fpasm, "\tmov eax, 0\n");
    fprintf(fpasm, "\tjmp nomayorigual%d\n", etiqueta);

    fprintf(fpasm, "\tmayorigual%d:\n", etiqueta);
    fprintf(fpasm, "\tmov eax, 1\n");

    fprintf(fpasm, "\tnomayorigual%d:\n", etiqueta);

    fprintf(fpasm, "\tpush dword eax\n");

}
void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {

    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable1) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjl menor%d\n", etiqueta);

    fprintf(fpasm, "\tmov eax, 0\n");
    fprintf(fpasm, "\tjmp nomenor%d\n", etiqueta);

    fprintf(fpasm, "\tmenor%d: \n", etiqueta);
    fprintf(fpasm, "\tmov eax, 1\n");

    fprintf(fpasm, "\tnomenor%d:\n", etiqueta);

    fprintf(fpasm, "\tpush dword eax\n");

}
void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {

    fprintf(fpasm, "\tpop dword ebx\n");
    if (es_variable2) fprintf(fpasm, "\tmov ebx, [ebx]\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable1) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjg mayor%d\n", etiqueta);

    fprintf(fpasm, "\tmov eax, 0\n");
    fprintf(fpasm, "\tjmp nomayor%d\n", etiqueta);

    fprintf(fpasm, "\tmayor%d: \n", etiqueta);
    fprintf(fpasm, "\tmov eax, 1\n");

    fprintf(fpasm, "\tnomayor%d:\n", etiqueta);

    fprintf(fpasm, "\tpush dword eax\n");

}


void leer(FILE* fpasm, char* nombre, int tipo) {

    fprintf(fpasm, "\tpush dword _%s\n", nombre);
    if (tipo == ENTERO) {
        fprintf(fpasm, "\tcall scan_int\n");
    } else {
        fprintf(fpasm, "\tcall scan_boolean\n");
    }

    fprintf(fpasm, "\tadd esp, 4\n");
}
void escribir(FILE* fpasm, int es_variable, int tipo) {

    fprintf(fpasm, "\tpop dword eax\n");
    if(es_variable)fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tpush dword eax\n");
    if (tipo == ENTERO) {
        fprintf(fpasm, "\tcall print_int\n");
    } else {
        fprintf(fpasm, "\tcall print_boolean\n");
    }

    fprintf(fpasm, "\tadd esp, 4\n");
    fprintf(fpasm, "\tcall print_endofline\n");
}

void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta) {

    fprintf(fpasm, "\tpop dword eax\n");
    if (exp_es_variable) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, 0\n");
    fprintf(fpasm, "\tje fin_thenelse%d\n", etiqueta);

}

void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta) {
    
    fprintf(fpasm, "\tpop dword eax\n");
    if (exp_es_variable) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, 0\n");
    fprintf(fpasm, "\tje fin_thenelse%d\n", etiqueta);

}

void ifthen_fin(FILE * fpasm, int etiqueta) {

    fprintf(fpasm, "fin_thenelse%d:\n", etiqueta);

}

void ifthenelse_fin_then( FILE * fpasm, int etiqueta) {

    fprintf(fpasm, "\tjmp fin_ifthenelse%d\n", etiqueta);
    fprintf(fpasm, "fin_thenelse%d:\n", etiqueta);

}

void ifthenelse_fin( FILE * fpasm, int etiqueta) {

    fprintf(fpasm, "fin_ifthenelse%d:\n", etiqueta);

}


void while_inicio(FILE * fpasm, int etiqueta) {

    fprintf(fpasm, "inicio_while%d:\n", etiqueta);

}

void while_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta) {
    
    fprintf(fpasm, "\tpop dword eax\n");
    if (exp_es_variable) fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, 0\n");
    fprintf(fpasm, "\tje while_fin%d\n", etiqueta);

}

void while_fin( FILE * fpasm, int etiqueta) {

    fprintf(fpasm, "\tjmp inicio_while%d\n", etiqueta);
    fprintf(fpasm, "while_fin%d:\n", etiqueta);
    
}

void escribir_elemento_vector(FILE * fpasm, char * nombre_vector, int tam_max, int exp_es_direccion) {

    fprintf(fpasm, "\tpop dword eax\n");

    if(exp_es_direccion== 1) {
        fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }

    fprintf(fpasm, "\tcmp eax, 0\n");
    fprintf(fpasm, "\tjl near fin_indice_fuera_rango\n");
    fprintf(fpasm, "\tcmp eax, %d\n", tam_max);
    fprintf(fpasm, "\tjge near fin_indice_fuera_rango\n");

    fprintf(fpasm, "\tmov dword edx, _%s\n", nombre_vector);
    fprintf(fpasm, "\tlea eax, [edx+ eax*4]\n");
    fprintf(fpasm, "\tpush dword eax\n");

}

void declararFuncion(FILE * fd_asm, char * nombre_funcion, int num_var_loc) {

    fprintf(fd_asm, "\t%s:\n", nombre_funcion);
    fprintf(fd_asm, "\tpush ebp\n");
    fprintf(fd_asm, "\tmov ebp, esp\n");
    fprintf(fd_asm, "\tsub esp, 4*%d\n", num_var_loc);

}

void retornarFuncion(FILE * fd_asm, int es_variable) {

    fprintf(fd_asm, "\tpop dword eax\n");
    if (es_variable) fprintf(fd_asm, "\tmov eax, [eax]\n");
    fprintf(fd_asm, "\tmov esp, ebp\n");
    fprintf(fd_asm, "\tpop dword ebp\n");
    fprintf(fd_asm, "\tret\n");

}

void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros) {
    
    int d_ebp;
    d_ebp = 4 * (1+ (num_total_parametros - pos_parametro));
    fprintf(fpasm,"\tlea eax, [ebp+ %d]\n", d_ebp);
    fprintf(fpasm, "\tpush dword eax\n");

}

void escribirVariableLocal(FILE* fpasm, int posicion_variable_local) {

    int d_ebp;
    d_ebp= 4 * (posicion_variable_local);
    fprintf(fpasm, "\tlea eax, [ebp-%d]\n", d_ebp);
    fprintf(fpasm, "\tpush dword eax\n");

}

void asignarDestinoEnPila(FILE* fpasm, int es_variable) {

    fprintf(fpasm, "\tpop dword ebx\n");
    fprintf(fpasm, "\tpop dword eax\n");   

    if(es_variable)
        fprintf(fpasm, "\t mov eax, [eax]\n");
    fprintf(fpasm, "\tmov dword [ebx], eax\n"); 

}

void operandoEnPilaAArgumento(FILE * fd_asm, int es_variable) {
    
    fprintf(fd_asm, "\tpop dword eax\n");
    if (es_variable) fprintf(fd_asm, "\tmov eax, [eax]\n");
    fprintf(fd_asm, "\tpush dword eax\n");

}

void llamarFuncion(FILE * fd_asm, char * nombre_funcion, int num_argumentos) {
    
    fprintf(fd_asm, "\tcall %s\n", nombre_funcion);
    fprintf(fd_asm, "\tadd esp, 4*%d\n", num_argumentos);
    fprintf(fd_asm, "\tpush dword eax\n");
}

void limpiarPila(FILE * fd_asm, int num_argumentos) {

    fprintf(fd_asm, "\tsub esp, 4*%d\n", num_argumentos);

}
