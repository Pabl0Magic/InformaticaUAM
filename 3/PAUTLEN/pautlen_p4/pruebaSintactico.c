  
#include <stdio.h>
#include <string.h>

int yylex();
int yyparse();
FILE * out = NULL;

int main(int argc, char ** argv) {
    extern FILE * yyin;
    yyin = fopen(argv[1], "r");
    if(yyin == NULL) {
        return 1;
    }
    out = fopen(argv[2], "w");
    if(out == NULL) {
        fclose(yyin);
        return 1;
    }

    if(yyparse()!=0){

    } else {
    
    }

    fclose(yyin);
    fclose(out);
    return 0;
}