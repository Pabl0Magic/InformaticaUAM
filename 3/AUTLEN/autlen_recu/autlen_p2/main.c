#include <stdio.h>
#include "afnd.h"
#include "minimiza.h"

int main(int argc, char ** argv){

	AFND * p_afnd;
	AFND * p_afnd_min;

	p_afnd = AFNDNuevo("af1",12,2);
	

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");

	AFNDInsertaEstado(p_afnd,"q0",INICIAL_Y_FINAL);
	AFNDInsertaEstado(p_afnd,"q1",NORMAL);
	AFNDInsertaEstado(p_afnd,"q2",NORMAL);
	AFNDInsertaEstado(p_afnd,"q3",NORMAL);
	AFNDInsertaEstado(p_afnd,"q4",FINAL);
	AFNDInsertaEstado(p_afnd,"q5",NORMAL);
	AFNDInsertaEstado(p_afnd,"q6",NORMAL);
	AFNDInsertaEstado(p_afnd,"q7",NORMAL);
	AFNDInsertaEstado(p_afnd,"q8",FINAL);
	AFNDInsertaEstado(p_afnd,"q9",NORMAL);
	AFNDInsertaEstado(p_afnd,"q10",NORMAL);
	AFNDInsertaEstado(p_afnd,"q11",NORMAL);



	AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q2");
	AFNDInsertaTransicion(p_afnd, "q1", "1", "q2");
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
	AFNDInsertaTransicion(p_afnd, "q2", "1", "q3");
	AFNDInsertaTransicion(p_afnd, "q3", "0", "q4");
	AFNDInsertaTransicion(p_afnd, "q3", "1", "q4");
	AFNDInsertaTransicion(p_afnd, "q4", "0", "q5");
	AFNDInsertaTransicion(p_afnd, "q4", "1", "q5");
	AFNDInsertaTransicion(p_afnd, "q5", "0", "q6");
	AFNDInsertaTransicion(p_afnd, "q5", "1", "q6");
	AFNDInsertaTransicion(p_afnd, "q6", "0", "q7");
	AFNDInsertaTransicion(p_afnd, "q6", "1", "q7");
	AFNDInsertaTransicion(p_afnd, "q7", "0", "q8");
	AFNDInsertaTransicion(p_afnd, "q7", "1", "q8");
	AFNDInsertaTransicion(p_afnd, "q8", "0", "q9");
	AFNDInsertaTransicion(p_afnd, "q8", "1", "q9");
	AFNDInsertaTransicion(p_afnd, "q9", "0", "q10");
	AFNDInsertaTransicion(p_afnd, "q9", "1", "q10");
	AFNDInsertaTransicion(p_afnd, "q10", "0", "q11");
	AFNDInsertaTransicion(p_afnd, "q10", "1", "q11");
	AFNDInsertaTransicion(p_afnd, "q11", "0", "q0");
	AFNDInsertaTransicion(p_afnd, "q11", "1", "q0");



	p_afnd_min = AFNDMinimiza(p_afnd);

	AFNDImprime(stdout,p_afnd_min);
	AFNDADot(p_afnd_min);

	AFNDElimina(p_afnd);
	AFNDElimina(p_afnd_min);

	return 0;
}
