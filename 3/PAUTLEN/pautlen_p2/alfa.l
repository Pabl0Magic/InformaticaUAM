%{
#include <stdio.h>
#include "tokens.h"
#define TOK_NEW_LINE 999
%}

%option noyywrap

%%

main { return TOK_MAIN; } /* Reserved words */
int { return TOK_INT; }
boolean { return TOK_BOOLEAN; }
array { return TOK_ARRAY; }
function { return TOK_FUNCTION; }
if { return TOK_IF; }
else { return TOK_ELSE; }
while { return TOK_WHILE; }
scanf { return TOK_SCANF; }
printf { return TOK_PRINTF; }
return { return TOK_RETURN; }

; { return TOK_PUNTOYCOMA; } /* Symbols */
, { return TOK_COMA; }
[(] { return TOK_PARENTESISIZQUIERDO; }
[)] { return TOK_PARENTESISDERECHO; }
[[] { return TOK_CORCHETEIZQUIERDO; }
[]] { return TOK_CORCHETEDERECHO; }
[{] { return TOK_LLAVEIZQUIERDA; }
[}] { return TOK_LLAVEDERECHA; }
[=] { return TOK_ASIGNACION; }
[+] { return TOK_MAS; }
[-] { return TOK_MENOS; }
[/] { return TOK_DIVISION; }
[*] { return TOK_ASTERISCO; }
&& { return TOK_AND; }
[||] { return TOK_OR; }
[!] { return TOK_NOT; }
"==" { return TOK_IGUAL; }
"!=" { return TOK_DISTINTO; }
"<=" { return TOK_MENORIGUAL; }
">=" { return TOK_MAYORIGUAL; }
[<] { return TOK_MENOR; }
[>] { return TOK_MAYOR; }

[0-9]+ { return TOK_CONSTANTE_ENTERA; } /* Constants */
TRUE { return TOK_TRUE; }
FALSE { return TOK_FALSE; }

[&] { return TOK_ERROR; } /* Error */

[\r\n] { return TOK_NEW_LINE; }/* Skip enter */
[" "\t]+ /* Skip tabs and blank spaces that are concurrent */
"//"[^\n]* /* Skip comments */
[a-zA-Z0-9]{100,} { return TOK_ERROR; } /*Length has more than 100 Characters*/
[a-zA-Z][a-zA-Z0-9]* { return TOK_IDENTIFICADOR; }  /*From the slides, represent the words*/

%%

