%{
	#include "alfa.h"
	#include "y.tab.h"

	int yylin=1,yycol=1;
	int error=0;

	extern FILE *erroresCompilacion;
%}

%option noyywrap

%%

main	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_MAIN;}
int	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_INT;}
boolean	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_BOOLEAN;}
function	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_FUNCTION;}
array	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_ARRAY;}
if	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_IF;}
else	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_ELSE;}
while	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_WHILE;}
scanf	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_SCANF;}
printf	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_PRINTF;}
return	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_RETURN;}

;	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_PUNTOYCOMA;}
,	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_COMA;}
[{]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_LLAVEIZQUIERDA;}
[}]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_LLAVEDERECHA;}
[(]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_PARENTESISIZQUIERDO;}
[)]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_PARENTESISDERECHO;}
[[]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_CORCHETEIZQUIERDO;}
[]]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_CORCHETEDERECHO;}
[+]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_MAS;}
[-]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_MENOS;}
[/]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_DIVISION;}
[*]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_ASTERISCO;}
&&	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_AND;}
"||"	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_OR;}
[=]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_ASIGNACION;}
"!="	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_DISTINTO;}
"=="	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_IGUAL;}
[!]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_NOT;}
"<="	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_MENORIGUAL;}
">="	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_MAYORIGUAL;}
[>]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_MAYOR;}
[<]	{yycol+=yyleng; fprintf(erroresCompilacion,";D:\t%s\n",yytext); return TOK_MENOR;}

true	{yycol+=yyleng; fprintf(erroresCompilacion, ";D:\t%s\n", yytext); return TOK_TRUE;}
false	{yycol+=yyleng; fprintf(erroresCompilacion, ";D:\t%s\n", yytext); return TOK_FALSE;}

[\r\n]	{yylin++; yycol=1;}

"//"[^\n]*	{yycol+=yyleng;}

[" "\t]+	{yycol+=yyleng;}

[a-zA-Z][a-zA-Z0-9]*	{
	yycol+=yyleng;
	strcpy(yylval.atributos.lexema, yytext);

	if(yyleng<=100){
		fprintf(erroresCompilacion, ";D:\t%s\n", yytext);
	} else{
		fprintf(stderr, "****Error en [lin %d, col %d]: identificador demasiado largo (%s)\n", yylin, yycol-yyleng, yytext);
		error=1;
		return TOK_ERROR;
	};

	return TOK_IDENTIFICADOR;
}

[0-9]+	{yycol+=yyleng; yylval.atributos.valor_entero=atoi(yytext); fprintf(erroresCompilacion, ";D:\t%s\n", yytext); return TOK_CONSTANTE_ENTERA;}

.	{
	error=1;
	yycol+=yyleng;
	fprintf(stderr, "****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", yylin, yycol-yyleng, yytext);
	return TOK_ERROR;
}
%%
