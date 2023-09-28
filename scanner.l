%{
#include "parser.tab.h"
extern int line_count;
int line_count = 1;
%}

%option reentrant bison-bridge noyywrap

id     [a-zA-Z][a-zA-Z_0-9]*
float  [0-9]+\.[0-9]+
int    [0-9]+
string \"[^\"\n]*\"

%%  

\}	 {return (LLAVEDER);}
\{ {return (LLAVEIZQ);}
\,   {return (COMA);}


\=	 {return (ASIGNACION);}

\+   {yylval->OP_ARIT = yytext; return (OP_ARIT);}
\-   {yylval->OP_ARIT = yytext; return (OP_ARIT);}
\/   {yylval->OP_ARIT = yytext; return (OP_ARIT);}
\*   {yylval->OP_ARIT = yytext; return (OP_ARIT);}
\^   {yylval->OP_ARIT = yytext; return (OP_ARIT);}
\%	 {yylval->OP_ARIT = yytext; return (OP_ARIT);}

\={2} {yylval->OP_REL = yytext; return (OP_REL);}
\!\= {yylval->OP_REL = yytext; return (OP_REL);}
\< {yylval->OP_REL = yytext; return (OP_REL);}
\> {yylval->OP_REL = yytext; return (OP_REL);}
\| {yylval->OP_REL = yytext; return (OP_REL);}
\<\= {yylval->OP_REL = yytext; return (OP_REL);}
\>\= {yylval->OP_REL = yytext; return (OP_REL);}
\<\>	 {yylval->OP_REL = yytext; return (OP_REL);}

[1-9][0-9]*  {return (NUM);}
while	 {return (CICLOWHILE);}
write	 {return (DESPLEGAR_CARACTERES);}
read	 {return (ENTRADA);}
if	 {return (IF_CONDICIONAL);}

string  {yylval->TIPO = yytext; return (TIPO);}
int     {yylval->TIPO = yytext; return (TIPO);}
float	 {yylval->TIPO = yytext; return (TIPO);}



"("        return LPAR;
")"        return RPAR;

{int}      { yylval->NUMBER = atol(yytext); return NUMBER; }

{id}       { yylval->IDENTIFIER = yytext; return IDENTIFIER; }
{string}   { yylval->STRING = yytext; return STRING; }
{float}     {yylval-> FLOAT = yytext; return FLOAT;}

\n {line_count++;}
[ \t]+ {}
<<EOF>>    return EOF;
