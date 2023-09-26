#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{/*5_7VS_9*/

        AFND * p_afnd;
        AFND * afd;

        p_afnd= AFNDNuevo("af5", 4, 2);

        AFNDInsertaSimbolo(p_afnd, "a");
        AFNDInsertaSimbolo(p_afnd, "b");
        
        AFNDInsertaEstado(p_afnd, "q0", INICIAL_Y_FINAL);
        AFNDInsertaEstado(p_afnd, "q1", NORMAL);
        AFNDInsertaEstado(p_afnd, "q2", NORMAL);
        AFNDInsertaEstado(p_afnd, "q3", FINAL);

        AFNDInsertaTransicion(p_afnd, "q0", "a", "q1");
        AFNDInsertaTransicion(p_afnd, "q1", "a", "q0");
        AFNDInsertaTransicion(p_afnd, "q1", "a", "q2");
        AFNDInsertaTransicion(p_afnd, "q1", "a", "q3");
        AFNDInsertaTransicion(p_afnd, "q1", "b", "q0");
        AFNDInsertaTransicion(p_afnd, "q1", "b", "q2");    
        AFNDInsertaTransicion(p_afnd, "q2", "b", "q0");
        AFNDInsertaTransicion(p_afnd, "q2", "b", "q3");
        
        
        AFNDInsertaLTransicion(p_afnd, "q1", "q3");
        AFNDInsertaLTransicion(p_afnd, "q2", "q3");
        AFNDInsertaLTransicion(p_afnd, "q2", "q2");
        AFNDInsertaLTransicion(p_afnd, "q3", "q2");
        AFNDCierraLTransicion(p_afnd);

        afd  = AFNDTransforma(p_afnd);
        AFNDImprime(stdout,afd);
        AFNDADot(afd);

        AFNDElimina(afd);
        AFNDElimina(p_afnd);
        
        return 0;
}