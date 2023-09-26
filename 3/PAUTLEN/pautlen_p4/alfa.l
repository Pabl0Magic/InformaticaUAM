%{
#include <stdio.h>
#include "y.tab.h"
#define _ERROR_HEAD "****Error in [lin %ld, col %ld]: "
#define _ERROR_SYM  "symbol not allowed (%s)\n"
#define _ERROR_ID   "too large identifier (%s)\n"
void _print_token(FILE * out) {
    fprintf(out, ";D:\t%s\n", yytext);
}
extern FILE * out;
long yylin = 1;
long yycol = 1;
int yymorph = 0;
%}
%option noyywrap
whitespace              [ \t]+
newline                 \n|\n\r|\r
comentario              "//".*
main                	"main"
int                 	"int"
boolean             	"boolean"
array               	"array"
function            	"function"
if                  	"if"
else                	"else"
while               	"while"
scanf               	"scanf"
printf              	"printf"
return              	"return"
puntoycoma          	";"
coma                	","
parentesisizquierdo 	"("
parentesisderecho   	")"
corcheteizquierdo   	"["
corchetederecho     	"]"
llaveizquierda      	"{"
llavederecha        	"}"
asignacion          	"="
mas                 	"+"
menos               	"-"
division            	"/"
asterisco           	"*"
and                 	"&&"
or                  	"||"
not                 	"!"
igual               	"=="
distinto            	"!="
menorigual          	"<="
mayorigual          	">="
menor               	"<"
mayor               	">"
constante_entera    	[0-9]+
true                	"true"
false               	"false"
identificador       	[a-zA-Z][a-zA-Z0-9]{0,99}
erroridentificador      [a-zA-Z][a-zA-Z0-9]*
error               	.
%%
{comentario}          	{/* COMENTARIO */}
{whitespace}            {yycol += yyleng;}
{newline}               {yylin++; yycol = 0;}
{main}                	{yycol += yyleng; _print_token(out); return  TOK_MAIN;}
{int}                 	{yycol += yyleng; _print_token(out); return  TOK_INT;}
{boolean}             	{yycol += yyleng; _print_token(out); return  TOK_BOOLEAN;}
{array}               	{yycol += yyleng; _print_token(out); return  TOK_ARRAY;}
{function}            	{yycol += yyleng; _print_token(out); return  TOK_FUNCTION;}
{if}                  	{yycol += yyleng; _print_token(out); return  TOK_IF;}
{else}                	{yycol += yyleng; _print_token(out); return  TOK_ELSE;}
{while}               	{yycol += yyleng; _print_token(out); return  TOK_WHILE;}
{scanf}               	{yycol += yyleng; _print_token(out); return  TOK_SCANF;}
{printf}              	{yycol += yyleng; _print_token(out); return  TOK_PRINTF;}
{return}              	{yycol += yyleng; _print_token(out); return  TOK_RETURN;}
{puntoycoma}          	{yycol += yyleng; _print_token(out); return  TOK_PUNTOYCOMA;}
{coma}                	{yycol += yyleng; _print_token(out); return  TOK_COMA;}
{parentesisizquierdo} 	{yycol += yyleng; _print_token(out); return  TOK_PARENTESISIZQUIERDO;}
{parentesisderecho}   	{yycol += yyleng; _print_token(out); return  TOK_PARENTESISDERECHO;}
{corcheteizquierdo}   	{yycol += yyleng; _print_token(out); return  TOK_CORCHETEIZQUIERDO;}
{corchetederecho}     	{yycol += yyleng; _print_token(out); return  TOK_CORCHETEDERECHO;}
{llaveizquierda}      	{yycol += yyleng; _print_token(out); return  TOK_LLAVEIZQUIERDA;}
{llavederecha}        	{yycol += yyleng; _print_token(out); return  TOK_LLAVEDERECHA;}
{asignacion}          	{yycol += yyleng; _print_token(out); return  TOK_ASIGNACION;}
{mas}                 	{yycol += yyleng; _print_token(out); return  TOK_MAS;}
{menos}               	{yycol += yyleng; _print_token(out); return  TOK_MENOS;}
{division}            	{yycol += yyleng; _print_token(out); return  TOK_DIVISION;}
{asterisco}           	{yycol += yyleng; _print_token(out); return  TOK_ASTERISCO;}
{and}                 	{yycol += yyleng; _print_token(out); return  TOK_AND;}
{or}                  	{yycol += yyleng; _print_token(out); return  TOK_OR;}
{not}                 	{yycol += yyleng; _print_token(out); return  TOK_NOT;}
{igual}               	{yycol += yyleng; _print_token(out); return  TOK_IGUAL;}
{distinto}            	{yycol += yyleng; _print_token(out); return  TOK_DISTINTO;}
{menorigual}          	{yycol += yyleng; _print_token(out); return  TOK_MENORIGUAL;}
{mayorigual}          	{yycol += yyleng; _print_token(out); return  TOK_MAYORIGUAL;}
{menor}               	{yycol += yyleng; _print_token(out); return  TOK_MENOR;}
{mayor}               	{yycol += yyleng; _print_token(out); return  TOK_MAYOR;}
{constante_entera}    	{yycol += yyleng; _print_token(out); return  TOK_CONSTANTE_ENTERA;}
{true}                	{yycol += yyleng; _print_token(out); return  TOK_TRUE;}
{false}               	{yycol += yyleng; _print_token(out); return  TOK_FALSE;}
{identificador}       	{yycol += yyleng; _print_token(out); return  TOK_IDENTIFICADOR;}
{erroridentificador}    {fprintf(stderr, "****Error en [lin %ld, col %ld]: too large identifier (%s)\n", yylin, yycol+1, yytext); yycol += yyleng; yymorph = 2; return  TOK_ERROR;}
{error}                 {fprintf(stderr, "****Error en [lin %ld, col %ld]: symbol not allowed (%s)\n", yylin, yycol+1, yytext); yycol += yyleng; yymorph = 1; return  TOK_ERROR;}
%%