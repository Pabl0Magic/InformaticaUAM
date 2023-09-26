#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols_table.h"  

#define BUF_SIZE 1024
#define ALFA_VAL_THRESH -1
#define ALFA_CLOSE_ID "cierre"
#define ALFA_CLOSE_VAL -999
#define ALFA_HELP "Modo de empleo: %s ENTRADA SALIDA"

void help(char * argv0) {
    printf(ALFA_HELP "\n", argv0);
}

void alfa_parse(char *buf, FILE *out) {
    INFO *info = NULL;
    char *id = NULL;
    int scan, value;
    scan = sscanf(buf, "%ms\t%i", &id, &value);
    
    if(scan == 2) {
        if(value < ALFA_VAL_THRESH) {
            if(!strcmp(id, ALFA_CLOSE_ID) && value == ALFA_CLOSE_VAL) {
                fprintf(out, ALFA_CLOSE_ID "\n");
                free(id);
                close();
            } else {
                info = create_symbol_info(id, FUNCION, INT, ESCALAR, 1, value, 0);
                if(info == NULL) {
                    free(id);
                    return;
                }
                if (declare_function(id, info) == OK){
                    fprintf(out, "%s\n", id);
                }else {
                    fprintf(out, "-1\t%s\n", id);
                }
                free_info(info);
                free(id);
            }
        } else if(value > ALFA_VAL_THRESH) {
            info = create_symbol_info(id, VARIABLE, INT, ESCALAR, 1, value, 0);
            if(info == NULL) {
                free(id);
                return;
            }
            printf("%s, %d\n",info->key, info->aux1);
            if (declare(id, info) == OK){
                fprintf(out, "%s\n", id);
            }else {
                fprintf(out, "-1\t%s\n", id);
            }
            free_info(info);
            free(id);
        }
    } else if(scan == 1) {
        info = local_search(id);
        fprintf(out, "%s\t%d\n", id, info == NULL? -1 : info->aux1);
        free(id);
    }
}

int main(int argc, char **argv) {
    FILE *in = NULL, *out = NULL;
    char buf[BUF_SIZE];
    if(argc != 3) {
        help(argv[0]);
        return 0;
    }
    in = fopen(argv[1], "r");
    if(in == NULL) {
        perror(argv[1]);
        return 1;
    }
    out = fopen(argv[2], "w");
    if(out == NULL) {
        perror(argv[2]);
        return 1;
    }
    while(fgets(buf, BUF_SIZE, in) != NULL) {
        alfa_parse(buf, out);
    }
    free_tables();
    fclose(in);
    fclose(out);
}