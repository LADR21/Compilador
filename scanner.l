%{
#include "parser.tab.h"

%}

%option reentrant bison-bridge noyywrap

id     [a-zA-Z][a-zA-Z_0-9]*
float  [0-9]+\.[0-9]+
int    [0-9]+
string \"[^\"\n]*\"

%%  



"}"	 {return (RBRACK);}
"{" {return (LBRACK);}
","   {return (COMMA);}
";"  {return (SEMICOLON);}
"+"   { yylval->OP_ARIT = yytext;return (OP_ARIT);}
"-"   {yylval->OP_ARIT = yytext; return (OP_ARIT);}
"*"   {yylval->OP_ARIT = yytext; return (OP_ARIT);}
"/"   {yylval->OP_ARIT = yytext; return (OP_ARIT);}
"^"   {yylval->OP_ARIT = yytext; return (OP_ARIT);}
"%"	 {yylval->OP_ARIT = yytext; return (OP_ARIT);}

"==" {yylval->OP_REL = yytext; return (OP_REL);}
"!=" {yylval->OP_REL = yytext; return (OP_REL);}
"<" {yylval->OP_REL = yytext; return (OP_REL);}
">" {yylval->OP_REL = yytext; return (OP_REL);}
"<=" {yylval->OP_REL = yytext; return (OP_REL);}
">=" {yylval->OP_REL = yytext; return (OP_REL);}

"="	 {return (ASSIGN);}

"while"	 {return (WHILE);}
"write"	 {return (WRITE);}
"read"	 {return (READ);}
"if"	    {return (IF);}

"string"  {yylval->TYPE = yytext; return (TYPE);}
"int"     {yylval->TYPE = yytext;return (TYPE);}
"float"	 {yylval->TYPE = yytext;return (TYPE);}

"("        return LPAR;
")"        return RPAR;

{int}      { yylval->ival = atol(yytext); return INTEGER_LITERAL; }

{id}       { yylval->sval = yytext; return IDENTIFIER; }
{string}   { yylval->sval = yytext; return STRING_LITERAL; }
{float}     {yylval-> fval = atof(yytext); return FLOAT_LITERAL;}

\s+ {}
\n+ {}
[\t]+ {/*ignore*/}
<<EOF>>    return TOK_EOF;
