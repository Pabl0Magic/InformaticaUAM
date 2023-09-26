#include <stdio.h>
#include <stdlib.h>

#include "generacion.h"

extern int yyparse(void);
extern FILE *yyin;
extern FILE* yyout;

#define ERROR -1

int main(int argc, char const *argv[]) {
    if(argc < 3){
        printf("./alfa  <nombre fichero entrada> <nombre fichero salida>\n");
        return ERROR;
    }
    yyin = fopen(argv[1], "r");
    if(!yyin){
      printf("Error: Unable to open yyin\n");
      return ERROR;
    }
    yyout = fopen(argv[2], "w");
    if(!yyout){
      printf("Error: Unable to open yyoutput file\n");
      return ERROR;
    }
    if(yyparse() != 0) {
      printf("\nError in the compilation\n");
    } else {
      printf("Compilation was succesful\n");
    }
    fclose(yyout);
    fclose(yyin);
    return 0;
}
