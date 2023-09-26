#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{
        /**
         * 4: BIEN
         * 6: añade transiciones ni idea por que
         * 8: Lo hace "bien" pero q1 deberia ser q1q2q3*
         * 10: Lo hace bien pero crea estados de mas (y transiciones de mas)
         * 12: BIEN
         * 14: BIEN
         * 
         */

        AFND * p_afnd;
        AFND * afd;

        p_afnd= AFNDNuevo("af5", 6, 3);

        AFNDInsertaSimbolo(p_afnd, "0");
        AFNDInsertaSimbolo(p_afnd, "+");
        AFNDInsertaSimbolo(p_afnd, ".");
        
        AFNDInsertaEstado(p_afnd, "q0", INICIAL);
        AFNDInsertaEstado(p_afnd, "q1", NORMAL);
        AFNDInsertaEstado(p_afnd, "q2", NORMAL);
        AFNDInsertaEstado(p_afnd, "q3", NORMAL);
        AFNDInsertaEstado(p_afnd, "q4", NORMAL);
        AFNDInsertaEstado(p_afnd, "q5", FINAL);

        AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");
        AFNDInsertaTransicion(p_afnd, "q1", "0", "q1");
        AFNDInsertaTransicion(p_afnd, "q1", "0", "q4");
        AFNDInsertaTransicion(p_afnd, "q1", ".", "q2");
        AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
        AFNDInsertaTransicion(p_afnd, "q3", "0", "q3");
        AFNDInsertaTransicion(p_afnd, "q4", ".", "q3");
        

        AFNDInsertaLTransicion(p_afnd, "q1", "q4");
        AFNDInsertaLTransicion(p_afnd, "q5", "q0");
        AFNDInsertaLTransicion(p_afnd, "q3", "q5");
        AFNDCierraLTransicion(p_afnd); 

        afd  = AFNDTransforma(p_afnd);
        AFNDImprime(stdout,afd);
        AFNDADot(afd);

        AFNDElimina(afd);
        AFNDElimina(p_afnd);
        
        return 0;
}