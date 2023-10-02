%define api.pure full
%lex-param {void *scanner}
%parse-param {void *scanner}{module *mod}

%define parse.trace
%define parse.error verbose

%{
#include <stdio.h>
#include "module.h"
#include "ast.h"
#include "parser.tab.h"
#include "scanner.h"

void yyerror (yyscan_t *locp, module *mod, char const *msg);
%}

%code requires
{
#include "module.h"
#include "ast.h"
}


%token ASSIGN "="

%union{
  long ival;
  float fval;
  char * sval;
  enum op_arit OP_ARIT;
  enum type TYPE;
  ast_node_atom* atom;
  ast_node_list* list;
  ast_cond_node* cond;
  ast_node_if* node_if;
  ast_node_decl* node_decl;
  ast_node_assign* node_assign;
  enum op_rel OP_REL;
  ast_node_while* node_while;
  ast_node_sexp* sexp;
}

%token <ival>    INTEGER_LITERAL "integer"
%token <fval>    FLOAT_LITERAL  "float"
%token <sval>   STRING_LITERAL "string"
%token <sval>   IDENTIFIER    "identifier"

%token <OP_ARIT> OP_ARIT
%token <TYPE>  TYPE
%token TOK_BOF 1 "begin of file"
%token TOK_EOF 0 "end of file"
%token <OP_REL> OP_REL

%token COMMA ","
%token SEMICOLON ";"

%token LPAR "("
%token RPAR ")"
%token LBRACK "{"
%token RBRACK "}"

%token WHILE "while"
%token IF "if"
%token WRITE "write"
%token READ "read"

%type <sexp> sexp
%type <atom> atom
%type <list> list

%type <node_while> BODYWHILE
%type <node_if> BODYIF
%type <cond> COND
%type <node_decl> DECL
%type <node_assign> ASSIGNSTRUCT
%right ASSIGN
%%
%start sexps;

sexps:
  sexp  {mod->root = $1;}

sexp:
  atom SEMICOLON    { $$ = new_sexp_node(ST_ATOM, $1); }
| DECL SEMICOLON {$$ = new_sexp_node(ST_DECL, $1);}
| LPAR list RPAR { $$ = new_sexp_node(ST_LIST, $2); }
| WHILE BODYWHILE RBRACK { $$ = new_sexp_node(ST_WHILE, $2);}
| IF BODYIF RBRACK {$$ = new_sexp_node(ST_IF, $2);}
| ASSIGNSTRUCT SEMICOLON {$$ = new_sexp_node(ST_ASSIGN, $1);};

ASSIGNSTRUCT:
  IDENTIFIER ASSIGN atom {$$ = new_assign_node($1, $3);};

BODYWHILE:
  COND LBRACK  {$$ = new_while_node($1);}
  |COND LBRACK BODYWHILE sexp {$$ = $3; add_node_to_while($$, $4);};

BODYIF:
  COND LBRACK  {$$ = new_if_node($1);}
  |COND LBRACK BODYIF sexp {$$ = $3; add_node_to_if($$, $4);};


COND:
  atom OP_REL atom  {$$ = new_cond_node($1, $2, $3);};

list:
  %empty        { $$ = new_list_node(); }
| list sexp    { $$ = $1; add_node_to_list($$, $2); };

DECL:
  TYPE IDENTIFIER {$$ = new_decl_node($1, $2);};

atom:
  "integer"      { $$ = new_atom_node(AT_NUMBER, (void *)(&$1)); }
| "identifier"  { $$ = new_atom_node(AT_IDENTIFIER, (void *)($1)); }
| "string"      { $$ = new_atom_node(AT_STRING, (void *)($1)); };
| "float"       { $$ = new_atom_node(AT_FLOAT, (void *)(&$1)); };

%%

void yyerror (yyscan_t *locp, module *mod, char const *msg) {
	fprintf(stderr, "--> %s\n", msg);
}