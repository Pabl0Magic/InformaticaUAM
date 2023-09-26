%{
	#include "alfa.h"
	#include "generacion.h"
	#include "hash_table.h"

	void yyerror(char const *cadena);

	extern int yylex();
	extern int yyleng;

	extern FILE *yyin, *yyout, *erroresCompilacion;
	extern int yylin, yycol;

	/* Error handling */
	extern int error;
	int syntaxError=0;

	/* Hash table declaration */
	HASH_TABLE global_table = NULL;
	HASH_TABLE local_table = NULL;

	/* Aux file for the semantical errors */
	FILE *erroresCompilacion;

	int etiqueta = 0; /* Loop handling*/

  	int abiertoAmbLocal=FALSE, en_funcion=FALSE, nretorno=0, llamada_dentro_funcion=0;

	char nombreFuncionActual[100];

	char aux[15];

	int current_type = ENTERO;
	int current_kind = VECTOR;
	int size_vector = 0;
	int pos_variable_local_actual = 0;
	int num_variables_locales_actual = 0;
	int num_param_actual = 0;
	int pos_param_actual = 0;
	int flag = 0;
	int num_parametros_llamada_actual = 0;
%}

%union{
	tipo_atributos atributos;
}

%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_FUNCTION
%token TOK_ARRAY
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN

%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_MAS
%token TOK_MENOS
%token TOK_DIVISION
%token TOK_ASTERISCO
%token TOK_AND
%token TOK_OR
%token TOK_ASIGNACION
%token TOK_DISTINTO
%token TOK_IGUAL
%token TOK_NOT
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR

%token <atributos> TOK_TRUE
%token <atributos> TOK_FALSE
%token <atributos> TOK_IDENTIFICADOR
%token <atributos> TOK_CONSTANTE_ENTERA
%token TOK_ERROR

%type <atributos> clase exp clase_escalar clase_vector constante constante_logica constante_entera comparacion fn_name fn_declaration funcion identificadores identificador asignacion elemento_vector condicional if_exp if_exp_sentencias bucle while while_exp idf_llamada_funcion idpf

%left TOK_MAS TOK_MENOS TOK_OR
%left TOK_DIVISION TOK_ASTERISCO TOK_AND
%right TOK_NOT MENOSR
%start programa
%%

programa: abrir_amb_global TOK_MAIN TOK_LLAVEIZQUIERDA escribir_bss declaraciones escribir_data funciones escribir_main sentencias TOK_LLAVEDERECHA {
	fprintf(erroresCompilacion,";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");
	fclose(erroresCompilacion);
	escribir_fin(yyout);
	free_hash_table(global_table);
}
;

abrir_amb_global: {
	erroresCompilacion=fopen("erroresCompilacion.txt","w");

	if((global_table = create_hash_table())==NULL){
			error=-1;
			syntaxError=0;
			yyerror("Error al abrir ambito global.");
			return -1;
	}
}
;

escribir_bss:{
	escribir_cabecera_bss(yyout);
}
;

escribir_data:{
	current_kind=1;
	escribir_subseccion_data(yyout);
	escribir_segmento_codigo(yyout);
}
;

escribir_main: {
	escribir_inicio_main(yyout);
}
;

declaraciones: declaracion {fprintf(erroresCompilacion,";R2:\t<declaraciones> ::= <declaracion>\n");}
		| declaracion declaraciones {fprintf(erroresCompilacion,";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");}
;

declaracion: clase identificadores TOK_PUNTOYCOMA {
	$2.tipo=$1.tipo;
	fprintf(erroresCompilacion,";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");
}
;

clase: clase_escalar {
	current_kind=ESCALAR;
	fprintf(erroresCompilacion,";R5:\t<clase> ::= <clase_escalar>\n");
}
	| clase_vector {
		current_kind=VECTOR;
		fprintf(erroresCompilacion,";R7:\t<clase> ::= <clase_vector>\n");
	}
;

clase_escalar: tipo {fprintf(erroresCompilacion,";R9:\t<clase_escalar> ::= <tipo>\n");}
;

clase_vector: vector tipo TOK_CORCHETEIZQUIERDO constante_entera TOK_CORCHETEDERECHO {
	size_vector=$4.valor_entero;

	if(size_vector < 1 || size_vector > MAX_TAMANIO_VECTOR){
		error=-1;
	}

	fprintf(erroresCompilacion,";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");
}
;

vector: TOK_ARRAY{
	current_kind = VECTOR;
}

tipo: TOK_INT{
	current_type=ENTERO;
	fprintf(erroresCompilacion,";R10:\t<tipo> ::= int\n");
}
	|TOK_BOOLEAN{
		current_type=BOOLEAN;
		fprintf(erroresCompilacion,";R11:\t<tipo> ::= boolean\n");
	}
;

identificadores: identificador{
	$1.tipo=$$.tipo;
	fprintf(erroresCompilacion,";R18:\t<identificadores> ::= <identificador>\n");
}| identificador TOK_COMA identificadores{
	$1.tipo=$$.tipo;$3.tipo=$$.tipo;
	fprintf(erroresCompilacion,";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");
}
;

funciones: funcion funciones{
	fprintf(erroresCompilacion,";R20:\t<funciones> ::= <funcion> <funciones>\n");
}
	| {
		fprintf(erroresCompilacion,";R21:\t<funciones> ::=\n");
	}
;

funcion : fn_declaration sentencias TOK_LLAVEDERECHA {
	free_hash_table(local_table);
	abiertoAmbLocal=FALSE;

	if (updateParam(global_table, $1.lexema, num_param_actual) == FALSE){
		error=-1;
		syntaxError=0;
		yyerror("Error al actualizar parametros de funcion");
		return -1;
	}

	if(nretorno == 0){
		error=-1;
		syntaxError=3;
		yyerror($1.lexema);
		return -1;
	}

	nretorno=0;
	en_funcion=FALSE;
	fprintf(erroresCompilacion,";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");
}
;

fn_name : TOK_FUNCTION tipo TOK_IDENTIFICADOR {
		if(abiertoAmbLocal==TRUE){
			error=-1;
			syntaxError=0;
			yyerror("No se puede crear una funcion dentro de otra funcion");
			return -1;
		}

		if(insert_symbol(global_table, $3.lexema, FUNCION, current_kind,current_type, size_vector, num_variables_locales_actual, pos_variable_local_actual,num_param_actual ,pos_param_actual) == FALSE){
			error=-1;
			syntaxError=0;
			yyerror("Declaracion duplicada.");
			return -1;
		}

		if((local_table = create_hash_table()) == NULL){
			error=-1;
			syntaxError=0;
			yyerror("Error al abrir el ambito local");
			return -1;
		}

		insert_symbol(local_table, $3.lexema, FUNCION, current_kind, current_type, size_vector, num_variables_locales_actual, pos_variable_local_actual,num_param_actual ,pos_param_actual);
		abiertoAmbLocal=TRUE;
		num_variables_locales_actual = 0;
		pos_variable_local_actual = 1;
		num_param_actual = 0;
		pos_param_actual = 0;
		strcpy($$.lexema,$3.lexema);
}
;

fn_declaration : fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion{
	if (updateParam(local_table, $1.lexema, num_param_actual) == FALSE){
		error=-1;
		syntaxError=0;
		yyerror("No se pueden actualizar los parametros de la funcion en el ambito local.");
		return -1;
	}

	en_funcion=TRUE;
	strcpy($$.lexema,$1.lexema);
	strcpy(nombreFuncionActual,$1.lexema);
	declararFuncion(yyout, $1.lexema,num_variables_locales_actual);
}
;

parametros_funcion: parametro_funcion resto_parametros_funcion {fprintf(erroresCompilacion,";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
			| {fprintf(erroresCompilacion,";R24:\t<parametros_funcion> :=\n");}
;

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {fprintf(erroresCompilacion,";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");}
			| {fprintf(erroresCompilacion,";R26:\t<resto_parametros_funcion> ::=\n");}
;

parametro_funcion: tipo idpf {fprintf(erroresCompilacion,";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n");}
;

declaraciones_funcion: declaraciones {fprintf(erroresCompilacion,";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");}
			| {fprintf(erroresCompilacion,";R29:\t<declaraciones_funcion> ::=\n");}
;

sentencias: sentencia {fprintf(erroresCompilacion,";R30:\t<sentencias> ::= <sentencia>\n");}
	| sentencia sentencias {fprintf(erroresCompilacion,";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");}
;

sentencia: sentencia_simple TOK_PUNTOYCOMA {fprintf(erroresCompilacion,";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
	| bloque {fprintf(erroresCompilacion,";R33:\t<sentencia> ::= <bloque>\n");}
;

sentencia_simple: asignacion {fprintf(erroresCompilacion,";R34:\t<sentencia_simple> ::= <asignacion>\n");}
		| lectura {fprintf(erroresCompilacion,";R35:\t<sentencia_simple> ::= <lectura>\n");}
		| escritura {fprintf(erroresCompilacion,";R36:\t<sentencia_simple> ::= <escritura>\n");}
		| retorno_funcion {fprintf(erroresCompilacion,";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");}
;

bloque: condicional {fprintf(erroresCompilacion,";R40:\t<bloque> ::= <condicional>\n");}
	| bucle {fprintf(erroresCompilacion,";R41:\t<bloque> ::= <bucle>\n");}
;

asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp {
	if(abiertoAmbLocal==FALSE){
		if(!search_symbol(global_table, $1.lexema)){
			error=-1;
			syntaxError=1;
			yyerror($1.lexema);
			return -1;
		}

		if(getCategory (global_table, $1.lexema) == FUNCION){
			error=-1;
			syntaxError=0;
			yyerror("Asignacion incompatible.");
			return -1;
		}

		if(getKind (global_table, $1.lexema) != ESCALAR){
			error=-1;
			syntaxError=0;
			yyerror("Asignacion incompatible.");
			return -1;
		}

		if(getType (global_table, $1.lexema) != $3.tipo){
			error=-1;
			syntaxError=0;
			yyerror("Asignacion incompatible.");
			return -1;
		}

		asignar(yyout, $1.lexema, $3.es_direccion);
	} else{
		if(!search_symbol(local_table, $1.lexema)){
			if(!search_symbol(global_table, $1.lexema)){
				error=-1;
				syntaxError=1;
				yyerror($1.lexema);
				return -1;
			}

			if(getCategory (global_table, $1.lexema) == FUNCION){
				error=-1;
				syntaxError=0;
				yyerror("Asignacion incompatible.");
				return -1;
			}

			if(getKind (global_table, $1.lexema) != ESCALAR){
				error=-1;
				syntaxError=0;
				yyerror("Asignacion incompatible.");
				return -1;
			}

			if(getType (global_table, $1.lexema) != $3.tipo){
				error=-1;
				syntaxError=0;
				yyerror("Asignacion incompatible.");
				return -1;
			}

			asignar(yyout, $1.lexema, $3.es_direccion);
		} else{
			if(getCategory (local_table, $1.lexema) == FUNCION){
				error=-1;
				syntaxError=0;
				yyerror("Asignacion incompatible.");
				return -1;
			}

			if(getKind (local_table, $1.lexema) != ESCALAR){
				error=-1;
				syntaxError=0;
				yyerror("Asignacion incompatible.");
				return -1;
			}

			if(getType (local_table, $1.lexema) != $3.tipo){
				error=-1;
				syntaxError=0;
				yyerror("Asignacion incompatible.");
				return -1;
			}

			escribirVariableLocal(yyout, getIndexVar(local_table, $1.lexema));
			asignarDestinoEnPila(yyout, $3.es_direccion);
		}
	}

	fprintf(erroresCompilacion,";R43:\t<asignacion> ::= <identificador> = <exp>\n");
}
	| elemento_vector TOK_ASIGNACION exp {
		if($3.tipo!=$1.tipo){
			error=-1;
			syntaxError=0;
			yyerror("Asignacion incompatible.");
			return -1;
		}

		asignarElementoVector(yyout, $3.lexema, $3.es_direccion);

		fprintf(erroresCompilacion,";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");
}
;

elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {
	if(abiertoAmbLocal==FALSE){
		if(!search_symbol(global_table, $1.lexema)){
			error=-1;
			syntaxError=1;
			yyerror($1.lexema);
			return -1;
		}

		if(getCategory (global_table, $1.lexema) == FUNCION || getKind (global_table, $1.lexema) != VECTOR){
			error=-1;
			syntaxError=0;
			yyerror("Intento de indexacion de una variable que no es de tipo vector.");
			return -1;
		}

		if($3.tipo != ENTERO){
			error=-1;
			syntaxError=0;
			yyerror("El indice en una operacion de indexacion tiene que ser de tipo entero.");
			return -1;
		}

		$$.tipo=getType (global_table, $1.lexema);
		$$.es_direccion=1;
		escribir_elemento_vector(yyout, $1.lexema, getSize(global_table, $1.lexema), $3.es_direccion);

	} else{
			if(!search_symbol(local_table, $1.lexema)){
				if(!search_symbol(global_table, $1.lexema)){
					error=-1;
					syntaxError=1;
					yyerror($1.lexema);
					return -1;
				}

				if(getCategory (global_table, $1.lexema) == FUNCION || getKind (global_table, $1.lexema) != VECTOR){
					error=-1;
					syntaxError=1;
					yyerror("Intento de indexacion de una variable que no es de tipo vector.");
					return -1;
				}

				if($3.tipo != ENTERO){
					error=-1;
					syntaxError=0;
					yyerror("El indice en una operacion de indexacion tiene que ser de tipo entero.");
					return -1;
				}

				$$.tipo=getType (global_table, $1.lexema);
				$$.es_direccion=1;
				escribir_elemento_vector(yyout, $1.lexema, getSize(global_table, $1.lexema), $3.es_direccion);
			 } else{
				if(getCategory (local_table, $1.lexema) == FUNCION || getKind (local_table, $1.lexema) != VECTOR){
					error=-1;
					syntaxError=0;
					yyerror("Intento de indexacion de una variable que no es de tipo vector.");
					return -1;
				}

				if($3.tipo != ENTERO){
					error=-1;
					syntaxError=0;
					yyerror("El indice en una operacion de indexacion tiene que ser de tipo entero.");
					return -1;
				}

				$$.tipo=getType (local_table, $1.lexema);
				$$.es_direccion=1;
				escribir_elemento_vector(yyout, $1.lexema, getSize(local_table, $1.lexema), $3.es_direccion);
			}
	}

	fprintf(erroresCompilacion,";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");
}
;

condicional: if_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
	ifthen_fin(yyout, $1.etiqueta);
	fprintf(erroresCompilacion,";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");
}
	| if_exp_sentencias TOK_ELSE TOK_LLAVEIZQUIERDA sentencias  TOK_LLAVEDERECHA {
		ifthenelse_fin(yyout, $1.etiqueta);
		fprintf(erroresCompilacion,";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");
	}
;

if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp {
	if($3.tipo!=BOOLEAN){
		error=-1;
		syntaxError=0;
		yyerror("Condicional con condicion de tipo int.");
		return -1;
	}

	etiqueta++;
	$$.etiqueta=etiqueta;
	ifthen_inicio(yyout,$3.es_direccion,$$.etiqueta);
}
;

if_exp_sentencias : if_exp  TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
	$$.etiqueta=$1.etiqueta;
	ifthenelse_fin_then(yyout, $1.etiqueta);
}
;

bucle: while_exp sentencias TOK_LLAVEDERECHA {
	while_fin(yyout, $1.etiqueta);
	fprintf(erroresCompilacion,";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");
}
;

while: TOK_WHILE TOK_PARENTESISIZQUIERDO  {
	etiqueta++;
	$$.etiqueta=etiqueta; 
	while_inicio(yyout, $$.etiqueta);
}
;

while_exp: while exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
	if($2.tipo!=BOOLEAN){
		error=-1;
		syntaxError=0;
		yyerror("Bucle con condicion de tipo int.");
		return -1;
	}

	$$.etiqueta=$1.etiqueta;
	while_exp_pila(yyout, $2.es_direccion, $1.etiqueta);
}
;

lectura: TOK_SCANF TOK_IDENTIFICADOR {
	if(abiertoAmbLocal==FALSE){
		if(!search_symbol(global_table, $2.lexema)){
			error=-1;
			syntaxError=1;
			yyerror($2.lexema);
			return -1;
		}

		if(getCategory (global_table, $2.lexema) == FUNCION){
			error=-1;
			syntaxError=0;
			yyerror("La lectura no se puede guardar en una funcion.");
			return -1;
		}

		if(getKind (global_table, $2.lexema) != ESCALAR){
			error=-1;
			syntaxError=0;
			yyerror("La lectura no se puede guardar en un vector.");
			return -1;
		}

		leer(yyout, $2.lexema, getType(global_table, $2.lexema));
	} else {
			if(!search_symbol(local_table, $2.lexema)){
				if(!search_symbol(global_table, $2.lexema)){
					error=-1;
					syntaxError=1;
					yyerror($2.lexema);
					return -1;
				}

				if(getCategory (global_table, $2.lexema) == FUNCION){
					error=-1;
					syntaxError=0;
					yyerror("La lectura no se puede guardar en una funcion.");
					return -1;
				}

				if(getKind (global_table, $2.lexema) != ESCALAR){
					error=-1;
					syntaxError=0;
					yyerror("La lectura no se puede guardar en un vector.");
					return -1;
				}

				leer(yyout, $2.lexema, getType (global_table, $2.lexema));
			}else{
				if(getCategory (local_table, $2.lexema) == FUNCION){
					error=-1;
					syntaxError=0;
					yyerror("La lectura no se puede guardar en una funcion.");
					return -1;
				}

				if(getKind (local_table, $2.lexema) != ESCALAR){
					error=-1;
					syntaxError=0;
					yyerror("La lectura no se puede guardar en un vector.");
					return -1;
				}

				leer(yyout, $2.lexema, getType(local_table, $2.lexema));
		}
	}

	fprintf(erroresCompilacion,";R54:\t<lectura> ::= scanf <identificador>\n");
}
;

escritura: TOK_PRINTF exp {
	escribir(yyout,$2.es_direccion,$2.tipo);
	fprintf(erroresCompilacion,";yylin %d\n",yylin);
	fprintf(erroresCompilacion,";R56:\t<escritura> ::= printf <exp>\n");
}
;

retorno_funcion: TOK_RETURN exp {
	if(en_funcion==FALSE){
		error=-1;
		syntaxError=0;
		yyerror("Sentencia de retorno fuera del cuerpo de una función.");
		return -1;
	}if(getType (global_table, nombreFuncionActual) != $2.tipo){
		error=-1;
		syntaxError=0;
		yyerror("Asignacion incompatible, la expresion de retorno tiene que tener el mismo tipo que la funcion.");
		return -1;
	}
	nretorno++;
	retornarFuncion(yyout, $2.es_direccion);
	fprintf(erroresCompilacion,";R61:\t<retorno_funcion> ::= return <exp>\n");
}
;

exp: exp TOK_MAS exp {
	if($1.tipo == $3.tipo && $1.tipo == ENTERO){
		$$.tipo=$1.tipo;
		$$.es_direccion=0;
		sumar(yyout, $1.es_direccion,$3.es_direccion);
	}else{
		error=-1;
		syntaxError=0;
		yyerror("Operacion aritmetica con operandos boolean");
		return -1;
	}

	fprintf(erroresCompilacion,";R72:\t<exp> ::= <exp> + <exp>\n");
}
	| exp TOK_MENOS exp {
		if($1.tipo == $3.tipo && $1.tipo == ENTERO){
			$$.tipo=$1.tipo;
			$$.es_direccion=0;
			restar(yyout, $1.es_direccion,$3.es_direccion);
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Operacion aritmetica con operandos boolean");
			return -1;
		}

		fprintf(erroresCompilacion,";R73:\t<exp> ::= <exp> - <exp>\n");
	}
	| exp TOK_DIVISION exp {
		if($1.tipo == $3.tipo && $1.tipo == ENTERO){
			$$.tipo=$1.tipo;
			$$.es_direccion=0;
			dividir(yyout, $1.es_direccion,$3.es_direccion);
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Operacion aritmetica con operandos boolean");
			return -1;
		}

		fprintf(erroresCompilacion,";R74:\t<exp> ::= <exp> / <exp>\n");
	}
	| exp TOK_ASTERISCO exp {
		if($1.tipo == $3.tipo && $1.tipo == ENTERO){
			$$.tipo=$1.tipo;
			$$.es_direccion=0;
			multiplicar(yyout, $1.es_direccion,$3.es_direccion);
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Operacion aritmetica con operandos boolean");
			return -1;
		}

		fprintf(erroresCompilacion,";R75:\t<exp> ::= <exp> * <exp>\n");
	}
	| TOK_MENOS exp %prec MENOSR {
		if($2.tipo == ENTERO){
			$$.tipo=$2.tipo;
			$$.es_direccion=0;
			cambiar_signo(yyout,$2.es_direccion);
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Operacion aritmetica con operandos boolean");
			return -1;
		}

		fprintf(erroresCompilacion,";R76:\t<exp> ::= - <exp>\n");
	}
	| exp TOK_AND exp {
		if($1.tipo==$3.tipo&&$1.tipo==BOOLEAN){
			$$.tipo=$1.tipo;
			$$.es_direccion=0;
			y(yyout,$1.es_direccion,$3.es_direccion);
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Operacion logica con operandos int.");
			return -1;
		}

		fprintf(erroresCompilacion,";R77:\t<exp> ::= <exp> && <exp>\n");
	}
	| exp TOK_OR exp {
		if($1.tipo == $3.tipo && $1.tipo == BOOLEAN){
			$$.tipo=$1.tipo;
			$$.es_direccion=0;
			o(yyout,$1.es_direccion,$3.es_direccion);
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Operacion logica con operandos int.");
			return -1;
		}

		fprintf(erroresCompilacion,";R78:\t<exp> ::= <exp> || <exp>\n");
	}
	| TOK_NOT exp {
		if($2.tipo == BOOLEAN){
			$$.tipo=$2.tipo;
			$$.es_direccion=0;
			etiqueta++;
			$$.etiqueta = etiqueta;
			no(yyout,$2.es_direccion, etiqueta);
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Operacion logica con operandos int.");
			return -1;
		}

		fprintf(erroresCompilacion,";R79:\t<exp> ::= ! <exp>\n");
	}
	| TOK_IDENTIFICADOR {
		if(abiertoAmbLocal==FALSE){
			if(!search_symbol(global_table, $1.lexema)){
				error=-1;
				syntaxError=1;
				yyerror($1.lexema);
				return -1;
			}

			if(getCategory (global_table, $1.lexema) == FUNCION){
				error=-1;
				syntaxError=0;
				yyerror("Expresion identificador de categoria funcion.");
				return -1;
			}

			if(getKind (global_table, $1.lexema) != ESCALAR){
				error=-1;
				syntaxError=0;

				if(flag==0){
					yyerror("Expresion identificador de clase vector.");
				}	else{
					yyerror("Parametro de funcion de tipo no escalar.");
				}

				return -1;
			}

			$$.tipo=getType (global_table, $1.lexema);
			$$.es_direccion=1;
			escribir_operando(yyout, $1.lexema, 1);

			if (flag == 1){
				operandoEnPilaAArgumento(yyout, 1);
			}
		} else{
				if(!search_symbol(local_table, $1.lexema)){
					if(!search_symbol(global_table, $1.lexema)){
						error=-1;
						syntaxError=1;
						yyerror($1.lexema);
						return -1;
					}

					if(getCategory (global_table, $1.lexema) == FUNCION){
						error=-1;
						syntaxError=0;
						yyerror("Expresion identificador de categoria funcion.");
						return -1;
					}

					if(getKind (global_table, $1.lexema) != ESCALAR){
						error=-1;
						syntaxError=0;
						if(flag==0)
							yyerror("Expresion identificador de clase vector.");
						else
							yyerror("Parametro de funcion de tipo no escalar.");
						return -1;
					}

					$$.tipo=getType (global_table, $1.lexema);
					$$.es_direccion=1;
					escribir_operando(yyout, $1.lexema, $1.es_direccion);

					if (flag == 1){
						operandoEnPilaAArgumento(yyout, 1);
					}
			 } else{
					if(getCategory (local_table, $1.lexema) == FUNCION){
						error=-1;
						syntaxError=0;
						yyerror("Expresion identificador de categoria funcion.");
						return -1;
					}

					if(getKind (local_table, $1.lexema) != ESCALAR){
						error=-1;
						syntaxError=0;
						yyerror("Expresion identificador de clase vector.");
						return -1;
					}

					$$.es_direccion=1;

					if (getCategory(local_table, $1.lexema) == PARAMETRO){
						escribirParametro(yyout, getIndexParam(local_table, $1.lexema), num_param_actual);

					} else {
						escribirVariableLocal(yyout, getIndexVar(local_table, $1.lexema));
					}

					$$.tipo=getType (local_table, $1.lexema);
			}
		}

		fprintf(erroresCompilacion,";R80:\t<exp> ::= <identificador>\n");}
	| constante {
		$$.tipo=$1.tipo;
		$$.es_direccion=$1.es_direccion;
		$$.valor_entero=$1.valor_entero;
		fprintf(erroresCompilacion,";R81:\t<exp> ::= <constante>\n");
	}
	| TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {
		$$.tipo=$2.tipo;
		$$.es_direccion=$2.es_direccion;
		$$.valor_entero=$2.valor_entero;
		fprintf(erroresCompilacion,";R82:\t<exp> ::= ( <exp> )\n");
	}
	| TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {
		$$.tipo=$2.tipo;
		$$.es_direccion=$2.es_direccion;
		$$.valor_entero=$2.valor_entero;
		fprintf(erroresCompilacion,";R83:\t<exp> ::= ( <comparacion> )\n");
	}
	| elemento_vector {
		$$.tipo=$1.tipo;
		$$.es_direccion=$1.es_direccion;
		$$.valor_entero=$1.valor_entero;
		fprintf(erroresCompilacion,";R85:\t<exp> ::= <elemento_vector>\n");
	}
	| idf_llamada_funcion TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO {
		llamada_dentro_funcion=0;

		if(abiertoAmbLocal==FALSE){
			if(getNumParam (global_table, $1.lexema) != num_parametros_llamada_actual){
				error=-1;
				syntaxError=0;
				yyerror("Numero incorrecto de parametros en llamada a funcion.");
				return -1;
			}
		}	else{
			if(strcmp(nombreFuncionActual,$1.lexema)==0){
				if(getNumParam (local_table, $1.lexema) != num_parametros_llamada_actual){
					error=-1;
					syntaxError=0;
					yyerror("Numero incorrecto de parametros en llamada a funcion.");
					return -1;
				}
			} else{
				if(getNumParam (global_table, $1.lexema) != num_parametros_llamada_actual){
					error=-1;
					syntaxError=0;
					yyerror("Numero incorrecto de parametros en llamada a funcion.");
					return -1;
				}
			}
		}

		flag=0;
		$$.tipo=getType (global_table, $1.lexema);
		$$.es_direccion=0;
		llamarFuncion(yyout, $1.lexema, num_param_actual);

		fprintf(erroresCompilacion,";R88:\t<exp> ::= <identificador> ( <lista_expresiones> )\n");
}
;

idf_llamada_funcion: TOK_IDENTIFICADOR{
		llamada_dentro_funcion=0;

		if(!search_symbol(global_table, $1.lexema)){
			error=-1;
			syntaxError=1;
			yyerror($1.lexema);
			return -1;
		}

		if(getCategory(global_table, $1.lexema) != FUNCION){
			error=-1;
			syntaxError=0;
			yyerror("El identificador de llamada de funcion no es de categoria funcion.");
			return -1;
		}

		if(flag==1){
			error=-1;
			syntaxError=0;
			yyerror("No esta permitido el uso de llamadas a funciones como parametros de otras funciones.");
			return -1;
		}

		if(strcmp(nombreFuncionActual,$1.lexema)!=0){
			llamada_dentro_funcion=1;
			printf("\nLlamada dentro de funcion activada");
		}

		flag=1;
		num_parametros_llamada_actual=0;
		strcpy($$.lexema,$1.lexema);
 }
;

lista_expresiones: exp resto_lista_expresiones {
	num_parametros_llamada_actual++;
	fprintf(erroresCompilacion,";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");
}
		| {fprintf(erroresCompilacion,";R90:\t<lista_expresiones> ::=\n");}
;

resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones {
	num_parametros_llamada_actual++;
	fprintf(erroresCompilacion,";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");
}
			| {fprintf(erroresCompilacion,";R92:\t<resto_lista_expresiones> ::=\n");}
;

comparacion: exp TOK_IGUAL exp {
	if($1.tipo == $3.tipo && $1.tipo == ENTERO){
		$$.tipo=BOOLEAN;
		$$.es_direccion=0;
		igual(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
		etiqueta++;
	}else{
		error=-1;
		syntaxError=0;
		yyerror("Comparacion con operandos boolean.");
		return -1;
	}
	fprintf(erroresCompilacion,";R93:\t<comparacion> ::= <exp> == <exp>\n");
}
	| exp TOK_DISTINTO exp {
		if($1.tipo == $3.tipo && $1.tipo == ENTERO){
			$$.tipo=BOOLEAN;
			$$.es_direccion=0;
			distinto(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
			etiqueta++;
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Comparacion con operandos boolean.");
			return -1;
		}
		fprintf(erroresCompilacion,";R94:\t<comparacion> ::= <exp> != <exp>\n");
	}
	| exp TOK_MENORIGUAL exp {
		if($1.tipo == $3.tipo && $1.tipo == ENTERO){
			$$.tipo=BOOLEAN;
			$$.es_direccion=0;
			menor_igual(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
			etiqueta++;
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Comparacion con operandos boolean.");
			return -1;
		}
		fprintf(erroresCompilacion,";R95:\t<comparacion> ::= <exp> <= <exp>\n");
	}
	| exp TOK_MAYORIGUAL exp {
		if($1.tipo == $3.tipo && $1.tipo == ENTERO){
			$$.tipo=BOOLEAN;
			$$.es_direccion=0;
			mayor_igual(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
			etiqueta++;
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Comparacion con operandos boolean.");
			return -1;
		}
		fprintf(erroresCompilacion,";R96:\t<comparacion> ::= <exp> >= <exp>\n");
	}
	| exp TOK_MENOR exp {
		if($1.tipo == $3.tipo && $1.tipo == ENTERO){
			$$.tipo=BOOLEAN;
			$$.es_direccion=0;
			menor(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
			etiqueta++;
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Comparacion con operandos boolean.");return -1;
		}
		fprintf(erroresCompilacion,";R97:\t<comparacion> ::= <exp> < <exp>\n");
	}
	| exp TOK_MAYOR exp {
		if($1.tipo == $3.tipo && $1.tipo == ENTERO){
			$$.tipo=BOOLEAN;
			$$.es_direccion=0;
			mayor(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
			etiqueta++;
		}else{
			error=-1;
			syntaxError=0;
			yyerror("Comparacion con operandos boolean.");
			return -1;
		}
		fprintf(erroresCompilacion,";R98:\t<comparacion> ::= <exp> > <exp>\n");
	}
;

constante: constante_logica {
	$$.es_direccion=$1.es_direccion;
	$$.tipo=$1.tipo;
	fprintf(erroresCompilacion,";R99:\t<constante> ::= <constante_logica>\n");
}
	| constante_entera {
		$$.tipo=$1.tipo;
		$$.es_direccion=$1.es_direccion;
		$$.valor_entero=$1.valor_entero;
		fprintf(erroresCompilacion,";R100:\t<constante> ::= <constante_entera>\n");
	}
;

constante_logica: TOK_TRUE {
	$$.es_direccion=0;
	$$.tipo=BOOLEAN;
	escribir_operando(yyout, "1", 0);
	fprintf(erroresCompilacion,";R102:\t<constante_logica> ::= true\n");
}
		| TOK_FALSE {
			$$.es_direccion=0;
			$$.tipo=BOOLEAN;
			escribir_operando(yyout, "0", 0);
			fprintf(erroresCompilacion,";R103:\t<constante_logica> ::= false\n");
		}
;

constante_entera: TOK_CONSTANTE_ENTERA {
	$$.tipo=ENTERO;
	$$.es_direccion=0;
	sprintf(aux, "%d", $1.valor_entero);

	if (current_kind != VECTOR){
		escribir_operando(yyout, aux, 0);
	}

	fprintf(erroresCompilacion,";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA\n");
}
;

idpf: TOK_IDENTIFICADOR {
	if(insert_symbol(local_table, $1.lexema, PARAMETRO, current_kind, current_type, size_vector, num_variables_locales_actual, pos_variable_local_actual,num_param_actual ,pos_param_actual) == FALSE){
		error=-1;
		syntaxError=1;
		yyerror($1.lexema);
		return -1;
	}

	strcpy($$.lexema,$1.lexema);
	fprintf(erroresCompilacion,";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
	num_param_actual++;
	pos_param_actual++;
}
;

identificador: TOK_IDENTIFICADOR {
	if(error==-1){
		syntaxError=2;
		yyerror($1.lexema);
		return -1;
	}

	if(abiertoAmbLocal==FALSE){
		if(insert_symbol(global_table, $1.lexema, VARIABLE, current_kind, current_type, size_vector, num_variables_locales_actual, pos_variable_local_actual,num_param_actual ,pos_param_actual) == FALSE){
				error=-1;
				syntaxError=0;
				yyerror("Declaracion duplicada.");
				return -1;
		}

		if (current_kind == VECTOR){
			declarar_variable(yyout, $1.lexema, current_type, size_vector);
		} else {
			declarar_variable(yyout, $1.lexema, current_type, 1);
		}

  } else{
		if (!search_symbol(local_table, $1.lexema)){
			if(current_kind == ESCALAR){
				insert_symbol(local_table, $1.lexema,VARIABLE,current_kind,current_type, size_vector, num_variables_locales_actual, pos_variable_local_actual,num_param_actual ,pos_param_actual);
				pos_variable_local_actual++;
				num_variables_locales_actual++;
			} else{
				error=-1;
				syntaxError=0;
				yyerror("Variable local de tipo no escalar.");
				return -1;
			}
		} else{
				error=-1;
				syntaxError=0;
				yyerror("Declaracion duplicada.");
				return -1;
		}
 }
  strcpy($$.lexema,$1.lexema);
	fprintf(erroresCompilacion,";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
 }
;
%%

void yyerror(char const *cadena){
	if(error == -1){
		switch (syntaxError){
			case 0:
				fprintf(stderr, "****Error semantico en lin %d: %s\n", yylin, cadena);
				break;

			case 1:
				fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", yylin, cadena);
				break;

			case 2:
				fprintf(stderr, "****Error semantico en lin %d: El tamanyo del vector <%s> excede los limites permitidos (1,64).\n", yylin, cadena);
				break;

			default:
				fprintf(stderr, "****Error semantico en lin %d: Funcion <%s> sin sentencia de retorno.\n", yylin, cadena);
				break;
		}
	}	else if(error == 0){
			fprintf(stderr, "**** Error sintactico en [lin %d, col %d]\n", yylin, yycol-yyleng);
	}

	error = 0;

	free_hash_table(global_table);

	if(erroresCompilacion!=NULL)
		fclose(erroresCompilacion);

	if(abiertoAmbLocal==TRUE)
		free_hash_table(local_table);
}