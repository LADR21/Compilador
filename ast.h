#ifndef __AST_H
#define __AST_H

enum op_rel{ EQEQ, NEQ, GT, LT, GTEQ, LTEQ };
enum atom_types { AT_NUMBER, AT_STRING, AT_IDENTIFIER, AT_FLOAT };
enum type {STRING, INT, FLOAT};
enum sexp_types { ST_ATOM, ST_LIST, ST_WHILE, ST_IF, ST_DECL, ST_ASSIGN };
enum op_arit {PLUS, MINUS, MULT, DIV, EXP, MOD};
typedef struct {
	enum atom_types type;
	union {
		long number;
		char *string;
		float flt;
	} value;
} ast_node_atom;

ast_node_atom *new_atom_node(enum atom_types type, void *v);
void delete_atom_node(ast_node_atom *node);
void print_node_atom(ast_node_atom *node);

struct _ast_node_sexp;
typedef struct _ast_node_sexp ast_node_sexp;
typedef struct {
	ast_node_sexp **list;
	unsigned int length;
	unsigned int capacity;
} ast_node_list;

ast_node_list *new_list_node();
void delete_list_node(ast_node_list *node);
void print_node_list(ast_node_list *node);
void add_node_to_list(ast_node_list *list, ast_node_sexp *node);


// CONDICIONALES

typedef struct{
	ast_node_atom *left;
	ast_node_atom *right;
	enum op_rel *op_rel;
} ast_cond_node;

ast_cond_node *new_cond_node(ast_node_atom *left, enum op_rel *op, ast_node_atom *right);
void print_node_cond(ast_cond_node *node);
void delete_cond_node(ast_cond_node *node);
// FIN CONDICIONALES

// WHILE

typedef struct {
	ast_node_sexp **wlist;
	ast_cond_node * cond;
	unsigned int length;
	unsigned int capacity;
} ast_node_while;

ast_node_while *new_while_node(ast_cond_node *cond);
void delete_while_node(ast_node_while *node);
void print_node_while(ast_node_while *node);
void add_list_to_while(ast_node_while *wlist, ast_node_list *list);

// FIN WHILE
// IF
typedef struct {
	ast_node_sexp **iflist;
	ast_cond_node * cond;
	unsigned int length;
	unsigned int capacity;
} ast_node_if;

	ast_node_if *new_if_node(ast_cond_node *cond);
	void delete_if_node(ast_node_if *node);
	void print_node_if(ast_node_if *node);
	void add_list_to_if(ast_node_if *iflist, ast_node_list *list);
// FIN IF


// DECL
typedef struct {
	enum type *type;
	char *name;
	ast_node_atom *value;
} ast_node_decl;

	ast_node_decl *new_decl_node(enum type *type, char *name);
	void delete_decl_node(ast_node_decl *node);
	void print_node_decl(ast_node_decl *node);
	// void add_node_to_decl(ast_node_sexp *decllist, ast_node_sexp *node);
// FIN DECL

// ASSIGN
typedef struct {
	enum type *type;
	char *name;
	ast_node_atom *value;
} ast_node_assign;

	ast_node_assign *new_assign_node(const char *name, ast_node_atom *value);
	void delete_assign_node(ast_node_assign *node);
	void print_node_assign(ast_node_assign *node);
// FIN ASSIGN

// SEXP
struct _ast_node_sexp {
	enum sexp_types type;
	union {
		ast_node_atom * atom;
		ast_node_list * list;
		ast_node_while * wlist;
		ast_node_if * iflist;
		ast_node_decl * decl;
		ast_node_assign * assign;
	} value;
};
void print_node_sexp(ast_node_sexp *node);
ast_node_sexp *new_sexp_node(enum sexp_types type, void *v);
void delete_sexp_node(ast_node_sexp *node);
void add_cond(ast_cond_node *cond, ast_node_sexp *node);
// FIN SEXP

#endif // __AST_H
