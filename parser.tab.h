/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 19 "parser.y"

#include "module.h"
#include "ast.h"

#line 53 "parser.tab.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_EOF = 0,
    ASSIGN = 258,
    INTEGER_LITERAL = 259,
    FLOAT_LITERAL = 260,
    STRING_LITERAL = 261,
    IDENTIFIER = 262,
    OP_ARIT = 263,
    TYPE = 264,
    TOK_BOF = 1,
    OP_REL = 265,
    COMMA = 266,
    SEMICOLON = 267,
    LPAR = 268,
    RPAR = 269,
    LBRACK = 270,
    RBRACK = 271,
    WHILE = 272,
    IF = 273,
    WRITE = 274,
    READ = 275
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "parser.y"

  long ival;
  float fval;
  char * sval;
  enum op_arit OP_ARIT;
  enum type TYPE;
  enum op_rel OP_REL;
  ast_node_atom* atom;
  ast_node_list* list;
  ast_cond_node* cond;
  ast_node_if* node_if;
  ast_node_decl* node_decl;
  ast_node_assign* node_assign;
  ast_node_while* node_while;
  ast_node_sexp* sexp;

#line 104 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner, module *mod);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
